CXX := g++
CXXFLAGS := -g -Wall -std=c++17

BUILD_DIR := build/make

# Define targets explicitly
TARGETS := hello_world algorithm

.PHONY: all clean

all: $(TARGETS)

# Rule for hello_world
hello_world: base/hello_world/src/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $(BUILD_DIR)/$@

# Rule for algorithm
algorithm: base/algorithm/src/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf *.dSYM
