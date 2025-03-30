# Compiler & linker
CXX = g++
CXXFLAGS = -g

# Path
SRC = src
OUT = bin

# Targets
run: 
	@$(OUT)/main
all: build run
build: clean
	@$(CXX) $(CXXFLAGS) 		   \
			$(SRC)/main.cpp 	   \
			$(SRC)/interface.cpp   \
			$(SRC)/processing.cpp  \
			$(SRC)/utility.cpp     \
			-o $(OUT)/main

clean:
	rm -rf $(OUT)/*

clean-i: 
	rm -rf io/input/*
clean-o:
	rm -rf io/output/*
clean-io: clean-i clean-o
