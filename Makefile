CXX = g++
CXXFLAGS = -std=c++23 -municode -Iinclude
LDFLAGS = -Llib
CREATE_DIR = mkdir

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = win32_platform

all: $(TARGET)

# Rule to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CREATE_DIR) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile the main file
main.o: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c win32_platform.cpp -o main.o

# Rule to link everything into the final executable
$(TARGET): $(OBJECTS) main.o
	$(CXX) -std=c++23 -municode $(OBJECTS) main.o -o $(TARGET) -lgdi32

# Clean build artifacts
clean:
	rmdir /q /s obj
	del /q /s obj main.o win32_platform.exe