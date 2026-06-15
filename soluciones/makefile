CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2

S1 = solucion1
S2 = solucion2
S3 = solucion3

BINS = $(S1) $(S2) $(S3)

.PHONY: all build clean run-S1 run-S2 run-S3

all: build

build: $(BINS)

$(S1): solucion1.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(S2): solucion2.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(S3): solucion3.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run-S1: $(S1)
	./$(S1)

run-S2: $(S2)
	./$(S2)

run-S3: $(S3)
	./$(S3)

clean:
	@echo "[CLN] Eliminando ejecutables..."
	@rm -f $(BINS)
