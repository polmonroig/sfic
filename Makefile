STD = -std=c++2a
# OPT = -Ofast -march=native -frename-registers
OPT = -O3
WARN = -Wall -Wextra
GCC = g++ $(OPT) $(STD) $(WARN)
PROGRAM = sfic

ARGPARSER = arg_parser argument
UTILS = exception_handler
DATA_STRUCTURES = huffman_tree match_table matrix
CONTAINERS = format image raw_data
ALGORITHMS = lz77_compression  huffman_compression
FORMATS = ppm_format jpeg_format png_format
FILES = $(UTILS) $(ALGORITHMS) $(DATA_STRUCTURES) $(CONTAINERS) $(FORMATS)
INCLUDE = $(addprefix include/,$(addsuffix .h,$(FILES))) \
		  $(addprefix ../arg_parser/include/,$(addsuffix .h,$(ARGPARSER)))
MAIN = src/sfic.cpp
SRC = $(addprefix src/,$(addsuffix .cpp,$(FILES))) $(MAIN) \
	  $(addprefix ../arg_parser/src/,$(addsuffix .cpp,$(ARGPARSER)))
OBJECT = $(addprefix build/,$(addsuffix .o,$(FILES)))

all: sfic

install: sfic
	mv sfic /usr/local/bin/


sfic: $(INCLUDE) $(SRC)
	$(GCC) -o $(PROGRAM) $(SRC)


clean:
	rm *.o *.s
