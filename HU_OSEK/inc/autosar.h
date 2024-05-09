
#ifndef AUTOSAR_H_
#define AUTOSAR_H_

#define NONE
#define FUNC(returnType, memType) memType returnType
#define VAR(dataType, memType) memType dataType
#define TASK(name) void OSEK_TASK_ ## name(void) __attribute__ ((weak))

#endif //AUTOSAR_H_