/*
 * Release_Res.c
 *
 *  Created on: May 6, 2023
 *      Author: Ziad - Aliaa
 */
#include "AlarmsHeader.h"

#if (ALARMS_COUNT != 0)
AlarmIncrementType IncrementAlarm(AlarmType AlarmID, AlarmIncrementType Increment)
{
	AlarmIncrementType RestIncrements;
	AlarmIncrementType AlarmCount;
	CounterIncrementType CounterIncrement;

	/* init alarms count */
	AlarmCount = 0;

	/* check if the increment is smaller than the expiration time */
	if ( alrm_time[AlarmID] > Increment )	//the time is more than increment then the alarm isn't expired
	{
		/* decrement the alarm*/
		alrm_time[AlarmID]-= Increment;	//decrement the time until they reach a value - the time

		/* alarm doesn't expires now */
		RestIncrements = alrm_time[AlarmID];	//the rest of the incrementes are now the alarm time
	}
	else
	{
		/* increment is greater or equal than the alarm time, the alarm may
			expire one or more times */

		//when the value of increment is more than the alarm time
		//then the alarm will expire and check if it is cyclic or non cyclic

		/* check if new alarm time has to be set or not if not cyclic alarm */
		if(alrm_cycTime[AlarmID]== 0)
		{
			/* in case of a non cyclic alarm */

			/* alarm has expires 1 time */
			AlarmCount = 1;

			/* set alarm to 0 */
			alrm_time[AlarmID] = 0;//as the time will start from 0 and it's already expired

			/* disable alarm */
			alrm_state[AlarmID] = 0; //as it is expired

			/* set rest increments to zero */
			RestIncrements = 0; //nothing left
		}
		else
		{
			/* the alarm is cyclic */

			/* decrement alarm */
			while ( alrm_time[AlarmID] <= Increment )
			{
				/* add cycle time */
				alrm_time[AlarmID] += alrm_cycTime[AlarmID];

				/* increment Alarms expiration times */
				AlarmCount++;
			}

			/* decrement the increments of this alarm */
			alrm_time[AlarmID] -= Increment;

			/* store the rest increments */
			RestIncrements = alrm_time[AlarmID];
		}

		if (alrmini_act[AlarmID] == INCREMENT)				//TODO if this is the increment that must be done after ISR
		{
			/* call counter function */
			CounterIncrement = Increment_HW_Counter(alrmini_actInfo[AlarmID].Counter, AlarmCount);

			/* re-calculate the rest of the increments */
			RestIncrements += alrm_cycTime[AlarmID] * ( CounterIncrement-1 );
		}
		else
		{
			/* execute the alarm so many times as needed */
			for ( ;AlarmCount > 0; AlarmCount--)
			{
				/* check alarm actions different to INCREMENT */
				switch(alrmini_act[AlarmID])
				{
					case CALLBACK:
							/* callback */
						if(alrmini_actInfo[AlarmID].CallbackFunction != NULL)
						{
							alrmini_actInfo[AlarmID].CallbackFunction();
						}
						break;

					case SETEVENT:
						/* set event */
						SetEvent(alrmini_actInfo[AlarmID].Ev.TaskID, alrmini_actInfo[AlarmID].Ev.Event);
						break;

					case ACTIVATETASK:
						/* activate task */
						ActivateTask(alrmini_actInfo[AlarmID].TaskID);
						break;
					default:
						/* some error */
						/* possibly TODO, report an error */
						break;
				}
			}
		}
	}

	return RestIncrements;
}

CounterIncrementType Increment_HW_Counter(CounterType CounterID, CounterIncrementType Increment)
{
	UINT8 loopi;
	AlarmType AlarmID;
	AlarmIncrementType MinimalCount = -1;
	AlarmIncrementType TmpCount;

	/* increment counter */
	cnt_time[CounterID]+=Increment;

	/* check if the timer has an overflow */
	while ( cnt_time[CounterID] >= cntini_maxVal[CounterID] )
	{
		/* reset counter */
		cnt_time[CounterID] -= cntini_maxVal[CounterID];
	}

	/* for alarms on this counter */
	for(loopi = 0; loopi < cntini_AlrmNum[CounterID]; loopi++)
	{
		/* get alarm id */
		AlarmID = cntini_AlrmRef[CounterID][loopi];

		/* check if the alarm is enable */
		if (alrm_state[AlarmID] == 1)
		{
			/* increment alarm and get the next alarm time */
			TmpCount = IncrementAlarm(AlarmID, Increment);

			/* if the actual count is smaller */
			if (MinimalCount > TmpCount)
			{
				/* set it as minimal count */
				MinimalCount = TmpCount;				//TODO: is this the specific value on which the incremented value in ISR depends
			}
		}
	}

	/* return the minimal increment */
	return (CounterIncrementType)MinimalCount;
}

#endif /* #if (ALARMS_COUNT != 0) */
