all : CombinationTest

%.class : %.java
	javac $<

CombinationTest : CombinationTest.class
	java org.junit.runner.JUnitCore CombinationTest

clean:
	rm -rf *.class
