CC = gcc
CFLAGS = -Wall -O2

SRC = src/main.c src/scanner.c
OBJ = $(SRC:.c=.o)

OUT = bin/nsc

all: $(OUT)

$(OUT): $(OBJ)
	mkdir -p bin
	$(CC) $(OBJ) -o $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)
