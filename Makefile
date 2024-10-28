SRC=main.cpp files.cpp huffman.cpp
OBJS=main.o files.o huffman.o
TARGET=huf

CXX=g++
CFLAGS=-Wall -Wextra -funroll-loops -O3 

all: $(OBJS)
	$(CXX) $^ -o $(TARGET) $(CFLAGS)

$(OBJS): $(SRC)
	$(CXX) $^ -c $(CFLAGS)

clean:
	rm $(OBJS)

