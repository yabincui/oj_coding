# TODO: support writing c++ code.

UnitTestList := FourSumTest NextPermutationTest

all: $(lastword $(UnitTestList))

test_all: $(UnitTestList)

JUNIT_MAIN = org.junit.runner.JUnitCore

%.class : %.java
	javac $<

%Test : %Test.class
	java $(JUNIT_MAIN) $@

%Test: %Test.py
	python $<

clean:
	rm -rf *.class
