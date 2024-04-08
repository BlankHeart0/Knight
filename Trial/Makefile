objects = 	Driver.o FileManager.o Scanner.o Parser.o ASTPrinter.o	\
			Type.o DataTypeChecker.o Register.o SymbolTable.o		\
			Instruction.o CodeGenerator.o Diagnostor.o

trial: $(objects)
	g++ -o trial $(objects)



Driver.o: System.h FileManager.h Scanner.h Parser.h CodeGenerator.h
FileManager.o: FileManager.h
Scanner.o: Scanner.h
Parser.o: Parser.h
ASTPrinter.o: AbstractSyntaxTree.h
Type.o: Type.h
DataTypeChecker.o: DataTypeChecker.h
Register.o: Register.h
SymbolTable.o: SymbolTable.h
Instruction.o: CodeGenerator.h
CodeGenerator.o: CodeGenerator.h
Diagnostor.o: Diagnostor.h


.PHONY: clean
clean:
	-rm trial $(objects)