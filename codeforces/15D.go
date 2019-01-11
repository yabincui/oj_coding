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

type MinHeap struct {
	a []int
	size int
	count_map map[int]int
}

func NewMinHeap() *MinHeap {
	return &MinHeap{count_map: make(map[int]int)}
}

func (h *MinHeap) Push(value int) {
	h.count_map[value]++
	if h.count_map[value] > 1 {
		return
	}
	if h.size == len(h.a) {
		h.a = append(h.a, value)
	} else {
		h.a[h.size] = value
	}
	h.size++
	k := h.size - 1
	for k > 0 {
		p := (k - 1) / 2
		if h.a[p] <= h.a[k] {
			break
		}
		h.a[k], h.a[p] = h.a[p], h.a[k]
		k = p
	}
}

func (h *MinHeap) Remove(value int) {
	h.count_map[value]--
	if h.count_map[value] > 0 {
		return
	}
}

func (h *MinHeap) GetMin() int {
	for true {
		if h.count_map[h.a[0]] > 0 {
			return h.a[0]
		}
		h.a[0] = h.a[h.size - 1]
		h.size--
		k := 0
		for k * 2 + 1 < h.size {
			child := k * 2 + 1
			if child + 1 < h.size && h.a[child + 1] < h.a[child] {
				child++
			}
			if h.a[k] <= h.a[child] {
				break
			}
			h.a[k], h.a[child] = h.a[child], h.a[k]
			k = child
		}
	}
	return -1
}


var n, m, a, b int
// original map
var s [1000][1000]int32
// rangeSum map, rangeSum[i][j] is the sum of s[0..i][0..j]
var rangeSum [1000][1000]int64

// rangeMin map, rangeMin[i][j] is the min of s[0..i][0..j]
var rangeMin [1000][1000]int32
// help structures for rangeMin
// rangeMinPerC[c][jr][ir] is the min of s[ir..(ir + (1<<jr) - 1)][c]
var rangeMinPerC [1000][10][1000]int32

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

func initRangeMinPerC() {
	for c := 0; c < m; c++ {
		for r := 0; r < n; r++ {
			rangeMinPerC[c][0][r] = s[r][c]
		}
		maxJr := log2(n)
		for jr := uint(1); jr <= maxJr; jr++ {
			for r := 0; r < n; r++ {
				t := int(rangeMinPerC[c][jr-1][r])
				if r + (1 << (jr - 1)) < n {
					t = MinInt(t, int(rangeMinPerC[c][jr-1][r + (1 << (jr - 1))]))
				}
				rangeMinPerC[c][jr][r] = int32(t)
			}
		}
	}
}

func getRangeMinPerC(c, r1, r2 int) int {
	length := r2 - r1 + 1
	level := log2(length)
	return MinInt(int(rangeMinPerC[c][level][r1]), int(rangeMinPerC[c][level][r2 - (1<<level) + 1]))
}

func preprocessRangeMin() {
	initRangeMinPerC()
	var row [10000]int
	for i := 0; i <= n - a; i++ {
		for j := 0; j < m; j++ {
			row[j] = getRangeMinPerC(j, i, i + a - 1)
		}
		h := NewMinHeap()
		for j := 0; j < b; j++ {
			h.Push(row[j])
		}
		for j := 0; j <= m - b; j++ {
			rangeMin[i][j] = int32(h.GetMin())
			if j < m - b {
				h.Push(row[j + b])
				h.Remove(row[j])
			}
		}
	}
}

func getRangeMin(r1, r2, c1, c2 int) int {
	return int(rangeMin[r1][c1])
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