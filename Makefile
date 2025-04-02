CXX = g++
CPPFLAGS = -O0 -I$(INC_DIR) -I/usr/include/SFML  # Add SFML header path
CXXFLAGS = -fPIC -Wall -Wextra -std=c++17
COVFLAGS = -fprofile-arcs -ftest-coverage


# Update to the correct library path (usually /usr/lib or /usr/local/lib)
LDFLAGS = -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio --coverage

EXEC = game



# ATTENZIONE: Rinominare questa directory a quella in cui è avete scaricato la repository
MAIN_DIR = /home/elchapa/Desktop/Space_invaders
SRC_DIR = $(MAIN_DIR)/src
RES_DIR = $(MAIN_DIR)/res
INC_DIR = $(MAIN_DIR)/include
OBJ_DIR = $(MAIN_DIR)/build


SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))


.Phony = coverage clean

# Rule for the coverage
coverage: $(EXEC)
	lcov --directory ./build --zerocounters
	./$(EXEC)
	
	cd $(OBJ_DIR) && gcov -o $(OBJ_DIR) $(SRC_FILES)
	lcov --directory $(OBJ_DIR) --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage

# Rule to link all object files into the final executable
$(EXEC): $(OBJ_FILES)
	$(CXX) $(COVFLAGS) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)

# Rule to compile each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(COVFLAGS) $(CXXFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.gcno $(EXEC)
	rm -rf $(MAIN_DIR)/*.gcov $(MAIN_DIR)/coverage.info $(MAIN_DIR)/coverage
	rm -rf $(MAIN_DIR)/coverage