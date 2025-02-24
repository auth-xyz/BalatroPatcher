BIN=patchy
FLAGS=-std=c++20
LDFLAGS=-Wl,-Bstatic -lclicky -Wl,-Bdynamic -lzip

all:
	g++ $(FLAGS) src/main.cpp -o $(BIN) $(LDFLAGS)

clean:
	rm -f $(BIN)

install:
	cp $(BIN) /usr/local/bin/

remove:
	rm -f /usr/local/bin/$(BIN)

.PHONY: all clean install remove

