CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = -lssl -lcrypto
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

miniGit: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f src/*.o minigit