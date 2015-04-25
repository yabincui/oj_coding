all : CombinationTest EditDistanceTest EditDistanceOperationTest

%.class : %.java
	javac $<

CombinationTest : CombinationTest.class
	java org.junit.runner.JUnitCore CombinationTest

EditDistanceTest : EditDistanceTest.class
	java org.junit.runner.JUnitCore EditDistanceTest

EditDistanceOperationTest : EditDistanceOperationTest.class
	java org.junit.runner.JUnitCore EditDistanceOperationTest

clean:
	rm -rf *.class
