objects = Driver.o VM.o FileManager.o Diagnostor.o

steed: $(objects)
	g++ -o steed $(objects)


Driver.o: System.h VM.h

VM.o: VM.h
FileManager.o: FileManager.h
Diagnostor.o: Diagnostor.h


.PHONY: clean
clean:
	-rm steed $(objects)