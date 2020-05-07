STD = -std=c++2a
OPT = -O3
WARN = -Wall -Wextra
GCC = g++ $(OPT) $(STD) $(WARN)
PROGRAM = sfic

FILES = format image jpeg_format matrix raw_data
INCLUDE = $(addprefix include/,$(addsuffix .h,$(FILES)))
MAIN = src/sfic.cpp
SRC = $(addprefix src/,$(addsuffix .cpp,$(FILES))) $(MAIN)
OBJECT = $(addprefix build/,$(addsuffix .o,$(FILES)))

all: sfic


sfic: $(INCLUDE) $(SRC)
	$(GCC) -o $(PROGRAM) $(SRC)


clean:
	rm *.o *.s
