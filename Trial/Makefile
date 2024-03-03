objects = 	Driver.o Scanner.o Parser.o 				\
			Register.o CodeGenerator.o Instruction.o	\
			FileManager.o ASTPrinter.o Diagnostor.o 

trial: $(objects)
	g++ -o trial $(objects)



Driver.o: System.h FileManager.h Scanner.h Parser.h CodeGenerator.h

Scanner.o: Scanner.h
Parser.o: Parser.h
Register.o: Register.h
CodeGenerator.o: CodeGenerator.h
Instruction.o: CodeGenerator.h

FileManager.o: FileManager.h
ASTPrinter.o: AbstractSyntaxTree.h
Diagnostor.o: Diagnostor.h



.PHONY: clean
clean:
	-rm trial $(objects)