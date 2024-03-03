objects = 	Driver.o Scanner.o Parser.o Register.o \
			ASTPrinter.o Diagnostor.o 

trial: $(objects)
	g++ -o trial $(objects)



Driver.o: System.h Scanner.h Parser.h

Scanner.o: Scanner.h
Parser.o: Parser.h
Register.o: Register.h

ASTPrinter.o: AbstractSyntaxTree.h
Diagnostor.o: Diagnostor.h



.PHONY: clean
clean:
	-rm trial $(objects)