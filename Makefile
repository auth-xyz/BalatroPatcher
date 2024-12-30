BIN=patchy
FLAGS= -std=c++20 -lclicky -lzip

all:
	g++ $(FLAGS) src/main.cpp -o $(BIN)

clean:
	rm -f $(BIN)

install:
	cp $(BIN) /usr/local/bin/

remove:
	rm -f /usr/local/bin/$(BIN)

.PHONY: all clean
