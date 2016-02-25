UnitTestList := MaxSubArraySumTest CalculateProbabilityTest StringCompressionTest \
                ReadSumOfDigitsTest MakePairsTest PowerOfTwoTest MaximizeNumberWithSwapTest \
                ConnectedGraphTest CoverTheMagicBoardTest MakeSequenceInAscendingOrderTest \
                PalindromicSubstringsTest \

all: $(lastword $(UnitTestList))

test_all: $(UnitTestList)


JUNIT_MAIN = org.junit.runner.JUnitCore

%.class : %.java
	javac $<

%Test: %.class %Test.class
	java $(JUNIT_MAIN) $@

clean:
	rm -rf *.class
