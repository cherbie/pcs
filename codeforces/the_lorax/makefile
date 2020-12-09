CXX = g++
CPPFLAGS = -std=c++17 -Wall -Werror -pedantic -g3
SRC_DIRS ?= ./src
BUILD_DIR ?= ./build

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:$(SRC_DIRS)/%=$(BUILD_DIR)/%.o)
HEADERS := $(shell find $(SRC_DIRS) -name *.hpp)

$(BUILD_DIR)/run : $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^

$(BUILD_DIR)/%.cpp.o : $(SRC_DIRS)/%.cpp $(HEADERS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -rfv $(BUILD_DIR)/*

MKDIR_P ?= mkdir -p
