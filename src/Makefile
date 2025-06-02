CXX = g++
CXXFLAGS = -I../include
LDFLAGS = -L../lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

# se windows, senao
ifeq ($(OS),Windows_NT)
    EXE = main.exe
    RM = del /Q
else
    EXE = main
    RM = rm -f
endif


all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(EXE)

.PHONY: all clean
