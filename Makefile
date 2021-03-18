STD = -std=c++2a
OPT = -O3
WARN = -Wall -Wextra
GCC = g++ $(OPT) $(STD) $(WARN)
PROGRAM = sfic

ARGPARSER = arg_parser argument
UTILS = exception_handler
ALGORITHMS = lz77_compression huffman_tree huffman_compression
FORMATS = ppm_format jpeg_format png_format
FILES = $(UTILS) $(ALGORITHMS) format image $(FORMATS) matrix raw_data
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
