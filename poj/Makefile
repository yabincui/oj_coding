
UnitTestList := LakeCounting BestCowLine SarumansArmy FenceRepair Expedition FoodLink \
                Roadblocks Conscription  Layout RedAndBlack Curling2_0 MeteorShower \
                SmallestDifference BackwardDigitSums Hopscotch CleaningShifts \
                RadarInstallation StallReservations YogurtFactory Packets Allowance \
                Stripies ProtectingTheFlowers CowBowling Sumsets AppleCatching \
                MilkingTime CheapestPalindrome Coins AntCounting DollarDayz WoodenSticks \
                BridgingSignals MakingTheGrade SpaceElevator CowExhibition Sunscreen \
                MooUniversityFinancialAid

LastUnitTest := $(lastword $(UnitTestList))

all: buildLast runLast

buildLast : $(LastUnitTest)_exe

runLast : buildLast
	./$(LastUnitTest)_exe

CFLAGS := -std=c++11

%_exe : %.cpp
	g++ $(CFLAGS) -o $@ $<

clean:
	rm -rf *_exe *_exe.dSYM
