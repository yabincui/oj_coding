package main

import (
	"bufio"
	"fmt"
	"os"
	"runtime"
	"runtime/pprof"
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
	for t := 1; t*2 <= n; t *= 2 {
		i++
	}
	return i
}

const MOD = int64(1000000007)

var n, m, q int
var s [200000]int

type Tree struct {
	leftPart  [][]int64
	rightPart [][]int64
	left      *Tree
	right     *Tree
}

var helpCount [20]int64
var int64Count int64

func init() {
	helpCount[0] = 1
}

func NewTree(l, r int) *Tree {
	t := new(Tree)
	mid := (l + r) / 2
	if l <= mid-1 {
		count := helpCount[:m]
		leftLen := mid - l
		t.leftPart = make([][]int64, leftLen)
		int64Count += int64(leftLen * m)
		for i := 0; i < leftLen; i++ {
			p := mid - 1 - i
			add := s[p]
			t.leftPart[i] = make([]int64, m)
			for j := 0; j < m; j++ {
				next := (j + add) % m
				t.leftPart[i][j] = (t.leftPart[i][j] + count[j]) % MOD
				t.leftPart[i][next] = (t.leftPart[i][next] + count[j]) % MOD
			}
			count = t.leftPart[i]
		}
	}
	if mid+1 <= r {
		count := helpCount[:m]
		rightLen := r - mid
		t.rightPart = make([][]int64, rightLen)
		int64Count += int64(rightLen * m)
		for i := 0; i < rightLen; i++ {
			p := mid + 1 + i
			add := s[p]
			t.rightPart[i] = make([]int64, m)
			for j := 0; j < m; j++ {
				next := (j + add) % m
				t.rightPart[i][j] = (t.rightPart[i][j] + count[j]) % MOD
				t.rightPart[i][next] = (t.rightPart[i][next] + count[j]) % MOD
			}
			count = t.rightPart[i]
		}
	}
	if l <= mid-1 {
		t.left = NewTree(l, mid-1)
	}
	if mid+1 <= r {
		t.right = NewTree(mid+1, r)
	}
	return t
}

func (t *Tree) GetZeroCountForRange(l, r, start, end int) int64 {
	mid := (l + r) / 2
	if end < mid {
		return t.left.GetZeroCountForRange(l, mid-1, start, end)
	}
	if start > mid {
		return t.right.GetZeroCountForRange(mid+1, r, start, end)
	}
	if start == mid && mid == end {
		if s[start] == 0 {
			return 2
		}
		return 1
	}
	if start == mid {
		// only right part
		count := t.rightPart[end-mid-1]
		i := (m - s[mid]) % m
		return (count[0] + count[i]) % MOD
	}
	if end == mid {
		// only left part
		count := t.leftPart[mid-start-1]
		i := (m - s[mid]) % m
		return (count[0] + count[i]) % MOD
	}
	count := t.leftPart[mid-start-1]
	count2 := t.rightPart[end-mid-1]
	//printf("l = %d, r = %d, mid %d, start %d, end %d, len(c1) %d, len(c2) %d\n",
	//		l, r, mid, start, end, len(count), len(count2))
	res := int64(0)
	for i := 0; i < m; i++ {
		j1 := (m - i) % m
		j2 := (m - i + m - s[mid]) % m
		//printf("i = %d, j1 = %d j2 %d, s[mid] = %d\n", i, j1, j2, s[mid])
		res += count[i] * (count2[j1] + count2[j2]) % MOD
	}
	return res % MOD
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
		var mem runtime.MemStats
		if _, err := scan(&n, &m); err != nil {
			break
		}
		for i := 0; i < n; i++ {
			scan(&s[i])
			s[i] %= m
		}
		runtime.ReadMemStats(&mem)
		printf("mem: before tree, total m = %fKB", float64(mem.Alloc)/1024.0)
		t := NewTree(0, n-1)
		scan(&q)
		for i := 0; i < q; i++ {
			var l, r int
			scan(&l, &r)
			count := t.GetZeroCountForRange(0, n-1, l-1, r-1)
			printf("%d\n", count)
		}
		runtime.ReadMemStats(&mem)
		printf("mem: total m = %fKB\n", float64(mem.Alloc)/1024.0)
		printf("mem, int64count = %d\n", int64Count)
	}
}
