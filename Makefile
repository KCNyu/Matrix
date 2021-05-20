src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))

inc_path = ./inc

myArgs = -Wall -g


ALL: Matrix

Matrix: $(obj)
	g++ $^ -o $@ $(myArgs)
$(obj): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)

clean:
	rm -rf $(obj) Matrix

.PHONY: ALL clean
