objects = Driver.o VM.o Parser.o				\
	      Register.o Function.o Instruction.o	\
		  FileManager.o Diagnostor.o			\

steed: $(objects)
	g++ -o steed $(objects)


Driver.o: System.h VM.h

VM.o: VM.h
Parser.o: Parser.h

Register.o: Register.h
Function.o: Function.h
Instruction.o: Instruction.h

FileManager.o: FileManager.h
Diagnostor.o: Diagnostor.h


.PHONY: clean
clean:
	-rm steed $(objects)