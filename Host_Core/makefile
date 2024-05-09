files_c := *.c
files_o := *.obj
comp := C:\Tools\tasking-tricore\tasking-tricore-6.3r1\ctc\bin\cctc.exe
lk := C:\Tools\tasking-tricore\tasking-tricore-6.3r1\ctc\bin\ltc.exe
PROJECT_FLAGS = --tradeoff=0 
PROJECT_LDFLAGS = --map-file-format=2 
UNUSED_FLAG = --long-branch-veneers
build: 
	@${comp} ${files_c} -o run
	@echo "build success"

compile:
	@${comp}  -c -O0 ${PROJECT_FLAGS} ${files_c} hsm_startup.asm -g3
	@echo "COMPILE SUCCESS!!!"

link:compile
	@${lk} ${files_o} -d OZEKAA.lsl -O0  --user-provided-initialization-code --map-file=HSM.map ${PROJECT_LDFLAGS} --output=./Debug/OZEKAA.elf 
	@echo "LINK SUCCESS!!!!"

run:build
	./run



clean:
	@rm  *.obj
	@rm *.map
	@rm *.elf
