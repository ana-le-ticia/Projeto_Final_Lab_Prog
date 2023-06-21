CC=gcc
CFLAGS=-Wno-unused-result

BIN_PATH=./bin
INC_PATH=./include

CALC_LIB_PATH=./libs/calc_lib
IMG_LIB_PATH=./libs/img_lib
DIR_LIB_PATH=./libs/dir_lib

SEARCH_ALG_PATH=./search

all: search

search: $(SEARCH_ALG_PATH)/main.c search_fn.o calc_lib.o img_lib.o dir_lib.o
	$(CC) $(CFLAGS) $< -o $(BIN_PATH)/$@ $(INC_PATH)/search_fn.o $(INC_PATH)/calc_lib.o $(INC_PATH)/img_lib.o $(INC_PATH)/dir_lib.o -lm

search_fn.o: $(SEARCH_ALG_PATH)/search_functions.c img_lib.o dir_lib.o
	$(CC) $(CFLAGS) -c $< -o $(INC_PATH)/$@
	
calc_lib.o: $(CALC_LIB_PATH)/calc.c img_lib.o
	$(CC) $(CFLAGS) -c $< -o $(INC_PATH)/$@

img_lib.o: $(IMG_LIB_PATH)/img_lib.c
	$(CC) $(CFLAGS) -c $< -o $(INC_PATH)/$@

dir_lib.o: $(DIR_LIB_PATH)/dir.c
	$(CC) $(CFLAGS) -c $< -o $(INC_PATH)/$@

clean:
	rm -rf ./bin/* ./include/*