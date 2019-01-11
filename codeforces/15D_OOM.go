package main

import (
	"bufio"
	"fmt"
	"os"
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
// rangeMin map, rangeMin[jr][ir][jc][ic] = minValue of
// s[ir..(ir + (1<<jr) - 1)][ic..(ic + (1<<jc) - 1)].
var rangeMin [10][1000][10][1000]int
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

func preprocessRangeMin() {
	for ir := 0; ir < n; ir++ {
		for ic := 0; ic < m; ic++ {
			rangeMin[0][ir][0][ic] = s[ir][ic]
		}
	}
	maxJr := log2(n)
	maxJc := log2(m)
	for ir := 0; ir < n; ir++ {
		for jc := uint(1); jc <= maxJc; jc++ {
			for ic := 0; ic < m; ic++ {
				t := rangeMin[0][ir][jc-1][ic]
				if ic + (1 << (jc-1)) < m {
					t = MinInt(t, rangeMin[0][ir][jc-1][ic + (1 << (jc-1))])
				}
				rangeMin[0][ir][jc][ic] = t
			}
		}
	}
	for jr := uint(1); jr <= maxJr; jr++ {
		for ir := 0; ir < n; ir++ {
			for jc := uint(0); jc <= maxJc; jc++ {
				for ic := 0; ic < m; ic++ {
					t := rangeMin[jr-1][ir][jc][ic]
					if ir + (1 << (jr-1)) < n {
						t = MinInt(t, rangeMin[jr-1][ir + (1<<(jr-1))][jc][ic])
					}
					rangeMin[jr][ir][jc][ic] = t
				}
			}
		}
	}
}

func getRangeMin(x1, x2, y1, y2 int) int {
	lenX := x2 - x1 + 1
	lenY := y2 - y1 + 1
	levelX := log2(lenX)
	levelY := log2(lenY)
	return MinInt(rangeMin[levelX][x1][levelY][y1],
				  rangeMin[levelX][x2-(1<<levelX)+1][levelY][y1],
				  rangeMin[levelX][x1][levelY][y2-(1<<levelY)+1],
				  rangeMin[levelX][x2-(1<<levelX)+1][levelY][y2-(1<<levelY)+1])
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