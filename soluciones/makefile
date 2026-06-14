CXX=g++
CXXFLAGS=-Wall -std=c++17 -O2
S1=solucion1
S2=solucion2
S3=solucion3

BINS=$(S1) $(S2) $(S3)

.PHONY: all build clean run-S1 run-S2 run-S3

all: build

build: $(BINS)

$(S1): solucion1.cpp
    $(CXX) $(CXXFLAGS) solucion1.cpp -o $(S1)

$(S2): solucion2.cpp
    $(CXX) $(CXXFLAGS) solucion2.cpp -o $(S2)

$(S3): solucion3.cpp
    $(CXX) $(CXXFLAGS) solucion3.cpp -o $(S3)
    
run-S1: $(S1)
    ./$(S1)

run-S2: $(S2)
    ./$(S2)

run-S3: $(S3)
    ./$(S3)
clean:
    @echo "[CLN] Removing binary files"
    @rm -f $(BINS)
