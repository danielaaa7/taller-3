CXX=g++
CXXFLAGS=-Wall -std=c++17

BINS = solucion1 solucion2 solucion3
all: clean solucion1 solucion2 solucion3

solucion1: 
    $(CXX) $(CXXFLAGS) -o solucion1 solucion1.cpp

solucion2: 
    $(CXX) $(CXXFLAGS) -o solucion2 solucion2.cpp

solucion3:
    $(CXX) $(CXXFLAGS) -o solucion3 solucion3.cpp

clean:
    @echo "[CLN] Removing binary files"
	@rm -f $(BINS) 