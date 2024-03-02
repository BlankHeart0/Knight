objects = Driver.o Scanner.o Diagnostor.o

trial: $(objects)
	g++ -o trial $(objects)



Driver.o: System.h Scanner.h

Scanner.o: Scanner.h
Diagnostor.o: Diagnostor.h



.PHONY: clean
clean:
	-rm trial $(objects)