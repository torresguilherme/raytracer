CC = g++
CFLAGS = -O3 -std=c++17
SRC = main.cpp components.cpp scene.cpp raytracing.cpp thread_pool.cpp

all:
	$(CC) $(CFLAGS) $(SRC)
run: all
	./a.out ../tst/1.txt out.ppm
