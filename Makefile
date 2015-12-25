## Makefile for reac_calc
## author: Ulrike Hager

CXXFLAGS += -std=c++11 -I.
OBJS = resonance.o reaction.o nonresonant.o reac_calc.o 

all: $(OBJS) reac_calc

reac_calc: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ 

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *.o reac_calc

