all:
		g++ SMJ.cpp -std=c++11 -O3 -o SMJ -pthread
		./SMJ < sampleinput


