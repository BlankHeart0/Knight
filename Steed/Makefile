objects = Driver.o VM.o Parser.o Instruction.o	\
		  Variable.o Function.o	Register.o		\
		  FileManager.o Diagnostor.o			\

steed: $(objects)
	g++ -o steed $(objects)


Driver.o: System.h VM.h
VM.o: VM.h
Parser.o: Parser.h
Instruction.o: Instruction.h VM.h

Variable.o: Variable.h
Function.o: Function.h VM.h
Register.o: Register.h

FileManager.o: FileManager.h
Diagnostor.o: Diagnostor.h


.PHONY: clean
clean:
	-rm steed $(objects)