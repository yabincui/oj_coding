package main

import (
	"bufio"
	"fmt"
	"os"
	"runtime/pprof"
	"sort"
)

var stdin *bufio.Reader
var stdout *bufio.Writer

func init() {
	stdin = bufio.NewReader(os.Stdin)
	stdout = bufio.NewWriter(os.Stdout)
}

func scan(args ...interface{}) (int, error) {
	return fmt.Fscan(stdin, args...)
}

func printf(format string, args ...interface{}) {
	fmt.Fprintf(stdout, format, args...)
}

func MinInt(args ...int) int {
	res := 0
	for i, v := range args {
		if i == 0 {
			res = v
		} else if res > v {
			res = v
		}
	}
	return res
}

func MaxInt(args ...int) int {
	res := 0
	for i, v := range args {
		if i == 0 {
			res = v
		} else if res < v {
			res = v
		}
	}
	return res
}

func log2(n int) uint {
	i := uint(0)
	for t := 1; t * 2 <= n; t *= 2 {
		i++
	}
	return i
}

type Student struct {
	id, value int
}

type StudentArray []Student

func (a StudentArray) Len() int { return len(a) }
func (a StudentArray) Less(i, j int) bool {
	return a[i].value > a[j].value
}
func (a StudentArray) Swap(i, j int) {
	a[i], a[j] = a[j], a[i]
}

// Wrong answer1: last diffCD
// Wrong answer2: isAllowed(, maxC)
// Wrong answer3: a <= 2 * min(b, c).
// Wrong answer4: maxA.

var n int
var s [3000]Student
// diff[i] = s[i].value - s[i+1].value
var diff [3000]int
// rangeMin[j][i] = pos of max(diff[i]..diff[i+(1<<j) - 1])
var rangeMax [12][3000]int
var res[3000]int

func preprocessRangeMax() {
	for i := 0; i < n; i++ {
		rangeMax[0][i] = i
	}
	maxJ := log2(n)
	for j := uint(1); j <= maxJ; j++ {
		for i := 0; i < n; i++ {
			t := rangeMax[j-1][i]
			if i + (1<<(j-1)) < n {
				t2 := rangeMax[j-1][i + (1<<(j-1))]
				if diff[t2] > diff[t] {
					t = t2
				}
			}
			rangeMax[j][i] = t
		}
	}
}

func getRangeMaxPos(start, end int) int {
	level := log2(end - start + 1)
	t1 := rangeMax[level][start]
	t2 := rangeMax[level][end - (1<<level)+1]
	if diff[t1] > diff[t2] {
		return t1
	}
	return t2
}

func isAllowed(a, b, maxC int) bool {
	maxVal := MinInt(a, b, maxC) * 2
	return a <= maxVal && b <= maxVal
}

func getMaxB(a int) int {
	low := ceilDiv(a, 2)
	high := MinInt(a * 2, 2 * (n - a) / 3)
	for low + 1 < high {
		mid := (low + high) / 2
		if isAllowed(a, mid, n - a - mid) {
			low = mid
		} else {
			high = mid - 1
		}
	}
	if low + 1 == high && isAllowed(a, high, n - a - high) {
		return high
	}
	return low
}

func isAllowedA(a int) bool {
	left := n - a
	half := left / 2
	return half * 2 >= a
}

func getMaxA() int {
	low := 1
	high := n / 2
	for low + 1 < high {
		mid := (low + high) / 2
		if isAllowedA(mid) {
			low = mid
		} else {
			high = mid - 1
		}
	}
	if low + 1 == high && isAllowedA(high) {
		return high
	}
	return low
}

func ceilDiv(a, b int) int {
	res := a / b
	if res * b < a {
		res++
	}
	return res
}

func main() {
	defer stdout.Flush()
	if false {
		f, _ := os.Create("profile")
		defer f.Close()
		pprof.StartCPUProfile(f)
		defer pprof.StopCPUProfile()
	}

	for true {
		if _, err := scan(&n); err != nil {
			break
		}
		for i := 0; i < n; i++ {
			s[i].id = i
			scan(&s[i].value)
		}
		sort.Sort(StudentArray(s[0:n]))
		for i := 0; i < n - 1; i++ {
			diff[i] = s[i].value - s[i+1].value
		}
		diff[n-1] = s[n-1].value
		preprocessRangeMax()
		// a is length of level 1
		// b is length of level 2
		// c is length of level 3
		bestA := -1
		bestB := -1
		bestC := -1
		bestDiffAB := -1
		bestDiffBC := -1
		bestDiffCD := -1
		maxA := getMaxA() 
		bestDiffAB = diff[getRangeMaxPos(0, maxA - 1)]
		for a := 1; a <= maxA; a++ {
			diffAB := diff[a-1]
			if diffAB < bestDiffAB {
				continue
			}
			minB := ceilDiv(a, 2)
			maxB := getMaxB(a)
			//printf("a = %d, n = %d, maxB = %d\n", a, n, maxB)
			tmpBestDiffBC := diff[getRangeMaxPos(a + minB - 1, a + maxB - 1)]
			/*
			printf("a = %d, tmpBestDiffBC = %d, bestDiffBC = %d\n", a, tmpBestDiffBC,
				bestDiffBC)
			printf("minB %d, maxB %d, pos = %d\n", minB, maxB,
				getRangeMaxPos(a + minB - 1, a + maxB - 1))
			*/
			if bestDiffBC > tmpBestDiffBC {
				continue
			}
			for b := minB; b <= maxB; b++ {
				diffBC := diff[a + b - 1]
				if diffBC < tmpBestDiffBC {
					continue
				}
				minC := MaxInt(ceilDiv(a, 2), ceilDiv(b, 2))
				maxC := MinInt(a * 2, b * 2, n - a - b)
				//printf("minC %d, maxC %d\n", minC, maxC)
				pos := getRangeMaxPos(a + b + minC - 1, a + b + maxC - 1)
				c := pos + 1 - a - b
				diffCD := diff[pos]
				if diffBC > bestDiffBC || diffCD > bestDiffCD {
					bestA = a
					bestB = b
					bestC = c
					bestDiffBC = diffBC
					bestDiffCD = diffCD
				}
			}
		}
		/*
		printf("diff: ")
		for i := 0; i < n; i++ {
			printf("%d ", diff[i])
		}
		printf("\n")
		printf("bestA %d, b %d c %d, diffAB %d BC %d CD %d\n",
			bestA, bestB, bestC, bestDiffAB, bestDiffBC, bestDiffCD)
		*/

		for i := 0; i < n; i++ {
			id := s[i].id
			level := -1
			if i < bestA {
				level = 1
			} else if i < bestA + bestB {
				level = 2
			} else if i < bestA + bestB + bestC {
				level = 3
			}
			res[id] = level
		}
		for i := 0; i < n; i++ {
			if i > 0 {
				printf(" ")
			}
			printf("%d", res[i])
		}
		printf("\n")
	}
}