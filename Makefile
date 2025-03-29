CXX = g++
CPPFLAGS = -I$(INC_DIR) -I/usr/include/SFML  # Add SFML header path
CXXFLAGS = -fPIC -Wall -Wextra -std=c++17 -g

# Update to the correct library path (usually /usr/lib or /usr/local/lib)
LDFLAGS = -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

EXEC = game



# ATTENZIONE: Rinominare questa directory a quella in cui è avete scaricato la repository
MAIN_DIR = /home/elchapa/shared_folder/Space_invaders
SRC_DIR = $(MAIN_DIR)/src
RES_DIR = $(MAIN_DIR)/res
INC_DIR = $(MAIN_DIR)/include
OBJ_DIR = $(MAIN_DIR)/build

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Rule to link all object files into the final executable
$(EXEC): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)

# Rule to compile each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)
