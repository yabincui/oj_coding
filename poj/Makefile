
UnitTestList := LakeCounting BestCowLine SarumansArmy

LastUnitTest := $(lastword $(UnitTestList))

all: buildLast runLast

buildLast : $(LastUnitTest)_exe

runLast : buildLast
	./$(LastUnitTest)_exe

CFLAGS := -std=c++11

%_exe : %.cpp
	g++ $(CFLAGS) -o $@ $<

clean:
	rm -rf *_exe
