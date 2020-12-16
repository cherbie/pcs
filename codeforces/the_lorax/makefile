CXX = g++
CPPFLAGS = -std=c++17 -Wall -Werror -pedantic -g3 -pthread
SRC_DIRS ?= ./src
BUILD_DIR ?= ./build

LINK = -L./dep/googletest/build/lib -lgtest -lpthread
INC = -I./dep/googletest/googletest/include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:$(SRC_DIRS)/%=$(BUILD_DIR)/%.o)
HEADERS := $(shell find $(SRC_DIRS) -name *.hpp)

$(BUILD_DIR)/run : $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(BUILD_DIR)/main.cpp.o

test: $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/tests.cpp.o $(LINK)

$(BUILD_DIR)/%.cpp.o : $(SRC_DIRS)/%.cpp $(HEADERS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC) -o $@ -c $<

.PHONY: clean

clean:
	rm -rfv $(BUILD_DIR)/*

MKDIR_P ?= mkdir -p
