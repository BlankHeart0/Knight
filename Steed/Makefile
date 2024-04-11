objects = Driver.o FileManager.o VM.o Parser.o		\
		  Type.o Variable.o Function.o Register.o	\
		  Instruction.o	 Diagnostor.o				\

steed: $(objects)
	g++ -o steed $(objects)



Driver.o: System.h VM.h
FileManager.o: FileManager.h
VM.o: VM.h
Parser.o: Parser.h
Type.o: Type.h
Variable.o: Variable.h
Function.o: Function.h VM.h
Register.o: Register.h
Instruction.o: Instruction.h VM.h
Diagnostor.o: Diagnostor.h



.PHONY: clean
clean:
	-rm steed $(objects)