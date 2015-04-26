all : CombinationTest EditDistanceTest EditDistanceOperationTest BestEditDistanceTest

%.class : %.java
	javac $<

CombinationTest : CombinationTest.class
	java org.junit.runner.JUnitCore CombinationTest

EditDistanceTest : EditDistanceTest.class
	java org.junit.runner.JUnitCore EditDistanceTest

EditDistanceOperationTest : EditDistanceOperationTest.class
	java org.junit.runner.JUnitCore EditDistanceOperationTest

BestEditDistanceTest : BestEditDistanceTest.class
	java org.junit.runner.JUnitCore BestEditDistanceTest

clean:
	rm -rf *.class
