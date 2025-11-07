.SILENT:

CXX = g++
CXXFLAGS = -Wall -g -std=c++17

SRC = dijkstra.cpp

help:
	echo "Provide a file path when running an algorithm: 'make run ARGS=file_path'"

run: build
	./a.out $(ARGS)

build:
	$(CXX) $(CXXFLAGS) $(SRC)

clean:
	rm ./a.out
