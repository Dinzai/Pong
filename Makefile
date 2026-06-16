# ===== Project settings =====
CXX := g++
TARGET := game
BUILD_DIR := build

# Find all .cpp files in the current directory
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Compiler flags
CXXFLAGS := -Wall -Wextra -O2 -std=c++17
LIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# ===== Build rules =====

all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compile step
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game
run: all
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all run clean