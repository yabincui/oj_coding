
UnitTestList := LakeCounting BestCowLine SarumansArmy FenceRepair Expedition FoodLink \
                Roadblocks Conscription  Layout RedAndBlack Curling2_0 MeteorShower \
                SmallestDifference BackwardDigitSums Hopscotch CleaningShifts \
                RadarInstallation StallReservations YogurtFactory Packets Allowance \
                Stripies ProtectingTheFlowers CowBowling Sumsets AppleCatching \
                MilkingTime CheapestPalindrome Coins AntCounting DollarDayz WoodenSticks \
                BridgingSignals MakingTheGrade SpaceElevator CowExhibition Sunscreen \
                MooUniversityFinancialAid WirelessNetwork FindThemCatchThem SixDegreesOfCowvinBacon \
                Wormholes SilverCowParty AgriNet BadCowtractors OutOfHay GcdLcmInverse \
                DeadFraction PrimePath X-factorChains SemiPrimeHNumbers PseudoprimeNumbers \
                RaisingModuloNumbers CableMaster AggressiveCows RiverHopscotch MonthlyExpense \
                Drying CowAcrobats DroppingTests KBest Median Matrix TelephoneLines Garland \
                Showstopper Subsequence JessicasReadingProblem BoundFound SumOfConsecutivePrimeNumbers \
                GraveyardDesign FaceTheRightWay Fliptile TheWaterBowls ExtendedLightsOut \
                PhysicsExperiment LinearWorld 4ValuesWhoseSumIs0 Subset Sumsets_2549 Crane \
                ASimpleProblemWithIntegers MooFest InnerVertices Matrix_2155 WhoGetsTheMostCandies \
								K-thNumber BalancedLineup FrequentValues Walls Intervals

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
