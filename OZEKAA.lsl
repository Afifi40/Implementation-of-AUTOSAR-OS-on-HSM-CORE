

#include "hsm.lsl"

		




section_layout ::linear
{
	//run_addr=
   group ivt_Group(ordered, contiguous, align=32,  run_addr=mem:Flash[0]){
		section "vector_table" (blocksize = 32, attributes=rx, fill=0)
       {
           select ".text.vector_handlers";
       }
   }
   
   group Code_Group (ordered, contiguous, align=32,  run_addr=mem:Flash)
   {
       section "Os_TEXT" (blocksize = 32, attributes=rx, fill=0)
       {
           select ".text";
		   select ".text.*";
		   
       }
   }
   "OS_TEXT_START" := addressof( group: Code_Group );
   "OS_TEXT_END" := addressof( group: Code_Group ) + sizeof( group: Code_Group );
   

   group Const_Group (ordered, contiguous, align=32,  run_addr=mem:Flash)
   {
       section "Os_CONST" (blocksize = 32, attributes=rx, fill=0)
       {
            select ".rodata";
       }       

   }
   "OS_CONST_START" := addressof( group: Const_Group );
   "OS_CONST_END" := addressof( group: Const_Group ) + sizeof( group: Const_Group );
   
   group Data_Group_ROM (ordered, contiguous, align=32,  fill=0, run_addr=mem:Flash )
   {
       section "Os_DATA_Init" (blocksize = 32, attributes=r)
       {
           select ".data";
       }
   }    
    "OS_DATA_START" := addressof( group: Data_Group_ROM );
    "OS_DATA_END" := addressof( group: Data_Group_ROM ) + sizeof( group: Data_Group_ROM );
	
	
   group Data_Group_RAM (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
       section "Os_DATA_Init" (blocksize = 32, attributes=rw)
       {
           select ".data";
       }
   }   
    "OS_DATA_RAM_START" := addressof( group: Data_Group_RAM );
    "OS_DATA_RAM_END" := addressof( group: Data_Group_RAM ) + sizeof( group: Data_Group_RAM );
	
   
   group Bss_Group (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "Os_BSS" (blocksize = 32, attributes=rw)
        {
		    select ".bss" (attributes=+b-s);
		}
   }
    "OS_BSS_START" := addressof( group: Bss_Group );
    "OS_BSS_END" := addressof( group: Bss_Group ) + sizeof( group: Bss_Group );
   
   group STACK_T0 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T0" (blocksize = 32, attributes=rw)
        {
			select ".bss.T0_STACK" (attributes=+b-s);
		}
   }
   
   group STACK_T1 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T1" (blocksize = 32, attributes=rw)
        {
			select ".bss.T1_STACK" (attributes=+b-s);
		}
   }
   
   group STACK_T2 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T2" (blocksize = 32, attributes=rw)
        {
			select ".bss.T2_STACK" (attributes=+b-s);
		}
   }
   
   group STACK_T3 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T3" (blocksize = 32, attributes=rw)
        {
			select ".bss.T3_STACK" (attributes=+b-s);
		}
   }
   
	group STACK_T4 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T4" (blocksize = 32, attributes=rw)
        {
			select ".bss.T4_STACK" (attributes=+b-s);
		}
   }
   
   group STACK_T5 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T5" (blocksize = 32, attributes=rw)
        {
			select ".bss.T5_STACK" (attributes=+b-s);
		}
   }
   
   group STACK_T6 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T6" (blocksize = 32, attributes=rw)
        {
			select ".bss.T6_STACK" (attributes=+b-s);
		}
   }
   
   group STACK_T7 (ordered, contiguous, align=32,  fill=0, run_addr=mem:SRAM )
   {
        section "OS_BSS_T7" (blocksize = 32, attributes=rw)
        {
			select ".bss.T7_STACK" (attributes=+b-s);
		}
   }
   
	
	group MainStackGroup(run_addr = mem:SRAM){
		stack "stack" ( size = 2k
		
							//id=0,
							//fixed,
							//entry_points = hsm_startup.asm
							//align = 4,
							//min_size = __STACK,
							//grows = high_to_low
		); 
	}
   

   
   
   
	
}
   
   
   
   
   