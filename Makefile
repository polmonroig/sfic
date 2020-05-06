STD = -std=c++2a
OPT = -O3
GCC = g++ $(OPT) $(STD)


INCLUDE = include/*
SRC = src/*
PROGRAM = sfic

sfic: $(INCLUDE) $(SRC)
	$(GCC) -o $(PROGRAM) $(SRC)
