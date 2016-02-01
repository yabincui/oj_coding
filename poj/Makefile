
UnitTestList := LakeCounting

LastUnitTest := $(lastword $(UnitTestList))

all: buildLast runLast

buildLast : $(LastUnitTest)

runLast : buildLast
	./$(LastUnitTest)

CFLAGS := -std=c++11

% : %.cpp
	g++ $(CFLAGS) -o $@ $<
