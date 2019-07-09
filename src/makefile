CC = clang++
CFLAGS = -O3 -std=c++11 -g3
SRC = components.cpp scene.cpp raytracing.cpp thread_pool.cpp octree.cpp main.cpp
LINKS = -lpthread

all:
	$(CC) $(CFLAGS) $(SRC) $(LINKS)
run: all
	./a.out ../tst/1.txt out.ppm
