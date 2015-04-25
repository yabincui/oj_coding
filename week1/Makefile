all : CombinationTest EditDistanceTest

%.class : %.java
	javac $<

CombinationTest : CombinationTest.class
	java org.junit.runner.JUnitCore CombinationTest

EditDistanceTest : EditDistanceTest.class
	java org.junit.runner.JUnitCore EditDistanceTest

clean:
	rm -rf *.class
