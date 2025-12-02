CXX := g++
CXXFLAGS := -g -Wall -std=c++17

BUILD_DIR := build/make

SRCS := $(wildcard base/hello_world/src/*.cpp)
# Only build executables for .cpp files that contain a main() function
MAIN_SRCS := $(shell grep -l "int main" $(SRCS) 2>/dev/null || true)
# Targets should be the base name (no directory) of main-containing sources
TARGETS := $(patsubst %.cpp,%,$(notdir $(MAIN_SRCS)))

# sources without main (libraries/modules)
NON_MAIN_SRCS := $(filter-out $(MAIN_SRCS),$(SRCS))

.PHONY: all clean

all: $(TARGETS)

# Rule: build executable from matching .cpp

# Or try to build target from a source under hello_world/
%: base/hello_world/src/%.cpp $(NON_MAIN_SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< $(NON_MAIN_SRCS) -o $(BUILD_DIR)/$@

clean:
	rm -f $(patsubst %, $(BUILD_DIR)/%, $(TARGETS))
	rm -rf *.dSYM
	rm -rf $(BUILD_DIR)
