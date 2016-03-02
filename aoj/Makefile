
UnitTestList := PropertyDistribution Ball Cheese SevenPuzzle Osenbei MarkedAncestor \
                ConvenientLocation RoadConstruction MrRitoPostOffice SaveYourCats \
                GcdAndLcm SumOf4Integers 

LastUnitTest := $(lastword $(UnitTestList))

all: buildLast runLast

buildLast : $(LastUnitTest)_exe

runLast : buildLast
	./$(LastUnitTest)_exe

CFLAGS := -std=c++11

%_exe : %.cpp
	g++ $(CFLAGS) -o $@ $<

clean:
	rm -rf *_exe *_exe.dSYM
