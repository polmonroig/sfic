STD = -std=c++2a
OPT = -O3
WARN = -Wall -Wextra
GCC = g++ $(OPT) $(STD) $(WARN)


INCLUDE = include/*
SRC = src/*
PROGRAM = sfic

sfic: $(INCLUDE) $(SRC)
	$(GCC) -o $(PROGRAM) $(SRC)
