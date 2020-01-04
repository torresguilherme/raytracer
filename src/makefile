CC = clang++
CFLAGS = -O3 -std=c++11
SRC = components.cpp scene.cpp raytracing.cpp thread_pool.cpp octree.cpp main.cpp
LINKS = -lpthread

all:
	$(CC) $(CFLAGS) $(SRC) $(LINKS)
run:
	./a.out out.ppm 640 480
fullhd:
	./a.out hd.ppm 1920 1080
