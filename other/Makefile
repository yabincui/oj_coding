UnitTestList := CombinationTest EditDistanceTest EditDistanceOperationTest BestEditDistanceTest \
               FourSumTest NextPermutationTest \

all: $(lastword $(UnitTestList))

test_all: $(UnitTestList)

%.class : %.java
	javac $<

%Test : %Test.class
	java org.junit.runner.JUnitCore $@

clean:
	rm -rf *.class
