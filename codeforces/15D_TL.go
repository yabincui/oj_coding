package main

import (
	"bufio"
	"fmt"
	"math"
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

type Candidate struct {
	r, c int
	cost int64
}

type CandidateArray []Candidate

func (s CandidateArray) Len() int {
	return len(s)
}

func (s CandidateArray) Less(i, j int) bool {
	if s[i].cost != s[j].cost {
		return s[i].cost < s[j].cost
	}
	if s[i].r != s[j].r {
		return s[i].r < s[j].r
	}
	return s[i].c < s[j].c
}

func (s CandidateArray) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}


var n, m, a, b int
// original map
var s [1000][1000]int
// rangeSum map, rangeSum[i][j] is the sum of s[0..i][0..j]
var rangeSum [1000][1000]int64

var segTree2DMaxC int
// rangeMin[ir][ic]
var segTree2D [2048][2048]int

// sort candidates
var candidates [1000000]Candidate
// visited map
var visited [1000][1000]bool

func log2(n int) uint {
	i := uint(0)
	for t := 1; t * 2 <= n; t *= 2 {
		i++
	}
	return i
}

func initSegTree1D(kr, r, k, c1, c2 int) {
	if c1 == c2 {
		segTree2D[kr][k] = s[r][c1]
		return
	}
	mid := (c1 + c2) / 2
	initSegTree1D(kr, r, 2 * k + 1, c1, mid)
	initSegTree1D(kr, r, 2 * k + 2, mid + 1, c2)
	segTree2D[kr][k] = MinInt(segTree2D[kr][2 * k + 1], segTree2D[kr][2 * k + 2])
	//printf("segTree2D, r = %d, c %d-%d, min = %d, k = %d\n", r, c1, c2, segTree2D[r][k], k)
}


func initSegTree2D(k, r1, r2 int) {
	if r1 == r2 {
		initSegTree1D(k, r1, 0, 0, m-1)
		return
	}
	mid := (r1 + r2) / 2
	initSegTree2D(2 * k + 1, r1, mid)
	initSegTree2D(2 * k + 2, mid + 1, r2)
	for i := 0; i < segTree2DMaxC; i++ {
		segTree2D[k][i] = MinInt(segTree2D[2 * k + 1][i], segTree2D[2 * k + 2][i])
	}
}

func preprocessRangeMin() {
	for segTree2DMaxC = 1; segTree2DMaxC < m; segTree2DMaxC *= 2 {
	}
	segTree2DMaxC *= 2
	initSegTree2D(0, 0, n-1)
}

func getSegTree1DRangeMin(segTree1D []int, k, minC, maxC, c1, c2 int) int {
	if minC > c2 || maxC < c1 {
		return math.MaxInt32
	}
	if minC >= c1 && maxC <= c2 {
		//printf("\tc %d-%d = %d, k = %d\n", minC, maxC, segTree1D[k], k)
		return segTree1D[k]
	}
	mid := (minC + maxC) / 2
	return MinInt(getSegTree1DRangeMin(segTree1D, 2 * k + 1, minC, mid, c1, c2),
		getSegTree1DRangeMin(segTree1D, 2 * k + 2, mid + 1, maxC, c1, c2))
}

func getSegTree2DRangeMin(k, minR, maxR, r1, r2, c1, c2 int) int {
	if minR > r2 || maxR < r1 {
		return math.MaxInt32
	}
	if minR >= r1 && maxR <= r2 {
		t := getSegTree1DRangeMin(segTree2D[k][:], 0, 0, m - 1, c1, c2)
		//printf("segTree minR %d, maxR %d, c: %d - %d, t %d, k = %d\n", minR, maxR, c1, c2, t, k)
		return t
	}
	mid := (minR + maxR) / 2
	return MinInt(getSegTree2DRangeMin(2 * k + 1, minR, mid, r1, r2, c1, c2),
		getSegTree2DRangeMin(2 * k + 2, mid + 1, maxR, r1, r2, c1, c2))
}

func getRangeMin(r1, r2, c1, c2 int) int {
	return getSegTree2DRangeMin(0, 0, n-1, r1, r2, c1, c2)
}


func getRangeSum(x1, x2, y1, y2 int) int64 {
	t := rangeSum[x2][y2]
	if x1 > 0 {
		t -= rangeSum[x1 - 1][y2]
	}
	if y1 > 0 {
		t -= rangeSum[x2][y1 - 1]
	}
	if x1 > 0 && y1 > 0 {
		t += rangeSum[x1-1][y1-1]
	}
	return t
}

func isVisited(c Candidate) bool {
	return visited[c.r][c.c] || visited[c.r][c.c + b - 1] ||
		visited[c.r + a - 1][c.c] || visited[c.r + a - 1][c.c + b - 1]
}

func main() {
	if true {
		f, _ := os.Create("profile")
		defer f.Close()
		pprof.StartCPUProfile(f)
		defer pprof.StopCPUProfile()
	}

	for true {
		if _, err := scan(&n, &m, &a, &b); err != nil {
			break
		}
		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				scan(&s[i][j])
			}
		}
		for i := 0; i < n; i++ {
			prevInLine := int64(0)
			for j := 0; j < m; j++ {
				rangeSum[i][j] = int64(s[i][j]) + prevInLine
				prevInLine += int64(s[i][j])
				if i > 0 {
					rangeSum[i][j] += rangeSum[i-1][j]
				}
			}
		}
		preprocessRangeMin()
		k := 0
		for i := 0; i <= n - a; i++ {
			for j := 0; j <= m - b; j++ {
				sum := getRangeSum(i, i + a - 1, j, j + b - 1)
				min := getRangeMin(i, i + a - 1, j, j + b - 1)				
				//printf("i %d, j %d, sum %d, min %d\n", i, j, sum, min)
				candidates[k].cost = sum - int64(min) * int64(a * b)
				candidates[k].r = i
				candidates[k].c = j
				k++
			}
		}
		sort.Sort(CandidateArray(candidates[0:k]))
		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				visited[i][j] = false
			}
		}
		var res []Candidate
		for t := 0; t < k; t++ {
			if isVisited(candidates[t]) {
				continue
			}
			for i := 0; i < a; i++ {
				for j := 0; j < b; j++ {
					visited[i+candidates[t].r][j+candidates[t].c] = true
				}
			}
			res = append(res, candidates[t])
		}
		printf("%d\n", len(res))
		for i := 0; i < len(res); i++ {
			printf("%d %d %d\n", res[i].r + 1, res[i].c + 1, res[i].cost)
		}

		stdout.Flush()
	}
}