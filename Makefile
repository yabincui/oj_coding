# TODO: support writing c++ code, and python code.

UnitTestList := FourSum.java

all: $(patsubst %.java,%.class,$(UnitTestList))


JUNIT_MAIN = org.junit.runner.JUnitCore

%.class : %.java
	javac $<

% : %.class
	java $(JUNIT_MAIN) $@

%Test: %.class %Test.class
	java $(JUNIT_MAIN) $@

%Test: %Test.py
	python $<

clean:
	rm -rf *.class
