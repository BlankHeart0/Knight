objects = 	Driver.o FileManager.o Scanner.o Parser.o 				\
			Register.o SymbolTable.o CodeGenerator.o Instruction.o	\
			ASTPrinter.o Diagnostor.o 

trial: $(objects)
	g++ -o trial $(objects)



Driver.o: System.h FileManager.h Scanner.h Parser.h CodeGenerator.h

Scanner.o: Scanner.h
FileManager.o: FileManager.h
Parser.o: Parser.h

Register.o: Register.h
SymbolTable.o: SymbolTable.h
CodeGenerator.o: CodeGenerator.h
Instruction.o: CodeGenerator.h

ASTPrinter.o: AbstractSyntaxTree.h
Diagnostor.o: Diagnostor.h



.PHONY: clean
clean:
	-rm trial $(objects)