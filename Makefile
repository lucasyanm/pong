CXX = g++
CXX_FLAGS = -std=c++23 -municode -Iinclude
EXE_FLAGS = -lgdi32
CREATE_DIR = mkdir

SRC_DIR = src
OBJ_DIR = obj

MAIN = $(wildcard *.cpp)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = win32_platform.exe

all: $(TARGET)

# Rule to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(OBJ_DIR):
	$(CREATE_DIR) $(OBJ_DIR)

# Rule to compile the main file
$(OBJ_DIR)/main.o: $(MAIN)
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

# Rule to link everything into the final executable
$(TARGET): $(OBJECTS) $(OBJ_DIR)/main.o
	$(CXX) $(CXX_FLAGS) $^ -o $(TARGET) $(EXE_FLAGS)

# Clean build artifacts
clean:
	rmdir /q /s $(OBJ_DIR)
	del /q /s obj *.o $(TARGET)