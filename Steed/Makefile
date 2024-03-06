objects = Driver.o VM.o Parser.o SymbolTable.o	\
	      Register.o Instruction.o Function.o 	\
		  FileManager.o Diagnostor.o			\

steed: $(objects)
	g++ -o steed $(objects)


Driver.o: System.h VM.h

VM.o: VM.h
Parser.o: Parser.h
SymbolTable.o: SymbolTable.h

Register.o: Register.h
Function.o: Function.h
Instruction.o: Instruction.h VM.h

FileManager.o: FileManager.h
Diagnostor.o: Diagnostor.h


.PHONY: clean
clean:
	-rm steed $(objects)