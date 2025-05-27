CXX = g++
CXXFLAGS = -I../include
LDFLAGS = -L../lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
EXE = main.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o *.exe

.PHONY: all clean