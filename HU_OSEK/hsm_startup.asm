
.global	Default_Handler
.global	Reset_Handler

.EXTERN PendSV_Handler
.EXTERN SVC_Handler

;.global Timer0_Handler
;.global Timer1_Handler

; start address for the initialization values of the .data SECTION. defined in linker script
.EXTERN	OS_DATA_RAM_START
; start address for the .data SECTION. defined in linker script
.EXTERN	OS_DATA_START
; end address for the .data SECTION. defined in linker script
.EXTERN	OS_DATA_END
; start address for the .bss SECTION. defined in linker script
.EXTERN	OS_BSS_START
; end address for the .bss SECTION. defined in linker script
.EXTERN	OS_BSS_END

; start address for the stack sections. defined in linker script
.EXTERN _lc_gb_STACK_T0
.EXTERN _lc_gb_STACK_T1
.EXTERN _lc_gb_STACK_T2
.EXTERN _lc_gb_STACK_T3
.EXTERN _lc_gb_STACK_T4
.EXTERN _lc_gb_STACK_T5
.EXTERN _lc_gb_STACK_T6
.EXTERN _lc_gb_STACK_T7

.EXTERN _lc_ub_stack
; start address for the stack sections. defined in linker script
.EXTERN _lc_ge_STACK_T0
.EXTERN _lc_ge_STACK_T1
.EXTERN _lc_ge_STACK_T2
.EXTERN _lc_ge_STACK_T3
.EXTERN _lc_ge_STACK_T4
.EXTERN _lc_ge_STACK_T5
.EXTERN _lc_ge_STACK_T6
.EXTERN _lc_ge_STACK_T7

;Extern functions here
.EXTERN main


; INIT_BSS macro is used to fill the specified region [start : end] with zeros
INIT_BSS .macro start, end
  ldr R0, =\start
  ldr R1, =\end
  movs R3, #0
  bl LoopFillZerobss
.endm

; INIT_DATA macro is used to copy data in the region [start : end] starting from 'src'
INIT_DATA .macro start, end, dest
  ldr R0, =\start
  ldr R1, =\end
  ldr R2, =\dest
  movs R3, #0
  bl LoopCopyDataInit
.endm

.SECTION  .text.startupMacros
CopyDataInit:
  ldr R4, [R0, R3]
  str R4, [R2, R3]
  adds R3, R3, #4

LoopCopyDataInit:
  adds R4, R0, R3
  cmp R4, R1
  bcc  CopyDataInit
  bx lr

FillZerobss:
  str  R3, [R0]
  adds R0, R0, #4

LoopFillZerobss:
  cmp R0, R1
  bcc FillZerobss
  bx lr
  
.ENDSEC


.SECTION .text.Reset_Handler
  .weak Reset_Handler
  Reset_Handler: .type func
  
  ldr   R0, =_lc_ub_stack

  MSR MSP, R0          ; set stack pointer
;Call the clock system intitialization function.
  ;bl  SystemInit

;Copy the data segment initializers from flash to SRAM
  INIT_DATA OS_DATA_START, OS_DATA_END, OS_DATA_RAM_START

;Zero fill the bss segments.
  INIT_BSS OS_BSS_START, OS_BSS_END

;Zero fill task_stacks
  INIT_BSS _lc_gb_STACK_T0, _lc_ge_STACK_T0
  INIT_BSS _lc_gb_STACK_T1, _lc_ge_STACK_T1
  INIT_BSS _lc_gb_STACK_T2, _lc_ge_STACK_T2
  INIT_BSS _lc_gb_STACK_T3, _lc_ge_STACK_T3
  INIT_BSS _lc_gb_STACK_T4, _lc_ge_STACK_T4
  INIT_BSS _lc_gb_STACK_T5, _lc_ge_STACK_T5
  INIT_BSS _lc_gb_STACK_T6, _lc_ge_STACK_T6
  INIT_BSS _lc_gb_STACK_T7, _lc_ge_STACK_T7

; Call the application entry point.
  bl main

;if code returns from main, loop forever
LoopForever:
  b LoopForever
.size	Reset_Handler, $-Reset_Handler

.ENDSEC

	.SECTION .text.vector_handlers

	.DW _lc_ub_stack ;Stack Entry Point ? Reset_Handler??
	.DW Reset_Handler
	.DW NMI_Handler
	.DW HardFault_Handler
	.DW MemManage_Handler
	.DW BusFault_Handler
	.DW UsageFault_Handler
	.DW 0
	.DW 0
	.DW 0
	.DW 0
	.DW SVC_Handler
	.DW DebugMon_Handler
	.DW 0 
	.DW PendSV_Handler
	.DW SysTick_Handler
	.DW Default_Handler ;Timer0_Handler
	.DW Default_Handler ;Timer1_Handler
	.DW Default_Handler ;TRNG_Handler
	.DW Default_Handler ;Bridge_Service
	.DW	Default_Handler ;Bridge_Error
	.DW	Default_Handler ;Sensor_Interrupt_Handler
	.DW	Default_Handler ;External_Interrupt_Handler
	.DW 0               
	.DW	Default_Handler ;PKC_Ready_Interrupt_Handler
	.DW	Default_Handler ;PKC_Error_Interrupt_Handler
	.ENDSEC




;
;
; The minimal vector table for a Cortex-M3.  Note that the proper constructs
; must be placed on this to ensure that it ends up at physical address
; 0x000C.8000.




		
;@brief  This is the code that gets called when the processor receives an
;        unexpected interrupt.  This simply enters an infinite loop, preserving
;        the system state for examination by a debugger.

  .SECTION .text.Default_Handler
	Default_Handler:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	;Infinite_Loop:
	;b			Infinite_Loop
	.size		Default_Handler, $-Default_Handler
  .ENDSEC  

		
;Provide weak aliases for each Exception handler to the Default_Handler.
;As they are weak aliases, any function with the same name will override
;this definition.
  .weak	 NMI_Handler,Default_Handler
  
  .weak  HardFault_Handler,Default_Handler

  .weak  MemManage_Handler,Default_Handler

  .weak  BusFault_Handler,Default_Handler

  .weak  UsageFault_Handler, Default_Handler

  .weak  SVC_Handler, Default_Handler

  .weak  DebugMon_Handler,Default_Handler

  .weak  PendSV_Handler,Default_Handler

  .weak  SysTick_Handler,Default_Handler
