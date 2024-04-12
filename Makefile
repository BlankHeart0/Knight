all: bin/trial bin/steed

$(shell mkdir -p build/trial build/steed bin)

# Trial
-include $(objects_trial:.o=.d)
path_trial = src/Trial
objects_trial = build/trial/Driver.o build/trial/FileManager.o build/trial/Scanner.o build/trial/Parser.o \
          		build/trial/ASTPrinter.o build/trial/Type.o build/trial/DataTypeChecker.o \
          		build/trial/Register.o build/trial/SymbolTable.o build/trial/Instruction.o \
          		build/trial/CodeGenerator.o build/trial/Diagnostor.o

bin/trial: $(objects_trial)
	g++ -o bin/trial $(objects_trial)

build/trial/%.o: $(path_trial)/%.cpp
	g++ -c $< -o $@

build/trial/%.d: $(path_trial)/%.cpp
	g++ -M $< -MT "build/trial/$*.o" -MF $@

# Steed
-include $(objects_steed:.o=.d)
path_steed = src/Steed
objects_steed = build/steed/Driver.o build/steed/FileManager.o build/steed/Diagnostor.o build/steed/VM.o \
				build/steed/Parser.o build/steed/Type.o build/steed/Variable.o \
				build/steed/Function.o build/steed/Register.o build/steed/Instruction.o

bin/steed: $(objects_steed)
	g++ -o bin/steed $(objects_steed)

build/steed/%.o: $(path_steed)/%.cpp
	g++ -c $< -o $@

build/steed/%.d: $(path_steed)/%.cpp
	g++ -M $< -MT "build/steed/$*.o" -MF $@

clean:
	-rm -rf bin/ build/
