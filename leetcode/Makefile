UnitTestList := BestTimeToBuyAndSellStockIVTest WildcardMatchingTest \
                TheSkylineProblemTest ShortestPalindromeTest \
                WordSearchII.class ImplementStackUsingQueues.class InvertBinaryTree.class \
                BasicCalculator.class RectangleArea.class CountCompleteTreeNodes.class \
                MaximalSquareTest ContainsDuplicate.class ContainsDuplicateII.class \
                ContainsDuplicateIII.class MaximalProductSubarrayTest \
                FindMinimumInRotatedSortedArray.class FindMinimumInRotatedSortedArrayII.class \
                MinStack.class IntersectionOfTwoLinkedLists.class FindPeakElement.class \
                MaximumGapTest CompareVersionNumbers.class FractionToRecurringDecimal.class \
                ExcelSheetColumnTitle.class MajorityElement.class ExcelSheetColumnNumber.class \
                FactorialTrailingZeroes.class BSTIterator.class DungeonGame.class \
                CreateMaximumNumber.class RangeSumQueryMutable.class \
                CountOfSmallerNumbersAfterSelf.class \

all: $(lastword ,$(UnitTestList))


JUNIT_MAIN = org.junit.runner.JUnitCore

%.class : %.java
	javac $<

%Test: %.class %Test.class
	java $(JUNIT_MAIN) $@

clean:
	rm -rf *.class
