# Compiler & linker
CXX            = g++

# Path
SRC = src
OUT = bin
OBJ = $(patsubst %/%.cpp, $(OUT)/%.o, $(wildcard $(addsuffix /*.cpp, $(SRC))))

# Targets
run-clean: clean run
run: all
	@$(OUT)/main
all: build
build: $(OBJ)
	@$(CXX)  $^ -o $(OUT)/main

$(OUT)/%.o: %/%.cpp | $(OUT)
	@$(CXX) -c $< -o $@	

$(OUT):
	@mkdir -p $(OUT)

clean:
	rm -rf $(OUT)/*