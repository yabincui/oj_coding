package main

import (
	"bufio"
	"fmt"
	"os"
	//	"runtime"
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

type Query struct {
	start, end int
	count      int64
}

var queries [200000]Query

type Tree struct {
	queryIds []int
	left     *Tree
	right    *Tree
}

func (t *Tree) AssignQuery(l, r, start, end, queryId int) {
	mid := (l + r) / 2
	if end < mid {
		if t.left == nil {
			t.left = new(Tree)
		}
		t.left.AssignQuery(l, mid-1, start, end, queryId)
	} else if start > mid {
		if t.right == nil {
			t.right = new(Tree)
		}
		t.right.AssignQuery(mid+1, r, start, end, queryId)
	} else {
		t.queryIds = append(t.queryIds, queryId)
	}
}

var initCount []int64

func init() {
	initCount = make([]int64, 20)
	initCount[0] = 1
}

func (t *Tree) ProcessQueries(l, r int) {
	mid := (l + r) / 2
	if t.left != nil {
		t.left.ProcessQueries(l, mid-1)
	}
	if t.right != nil {
		t.right.ProcessQueries(mid+1, r)
	}
	count := initCount
	count[0] = 1
	leftLen := mid - l
	left := make([][]int64, leftLen)
	for i := 0; i < leftLen; i++ {
		p := mid - 1 - i
		add := s[p]
		left[i] = make([]int64, m)
		for j := 0; j < m; j++ {
			next := (j + add) % m
			left[i][j] = (left[i][j] + count[j]) % MOD
			left[i][next] = (left[i][next] + count[j]) % MOD
		}
		count = left[i]
	}
	count = initCount
	rightLen := r - mid
	right := make([][]int64, rightLen)
	for i := 0; i < rightLen; i++ {
		p := mid + 1 + i
		add := s[p]
		right[i] = make([]int64, m)
		for j := 0; j < m; j++ {
			next := (j + add) % m
			right[i][j] = (right[i][j] + count[j]) % MOD
			right[i][next] = (right[i][next] + count[j]) % MOD
		}
		count = right[i]
	}
	for _, queryId := range t.queryIds {
		query := &queries[queryId]
		query.count = getZeroCount(mid, left, right, query.start, query.end)
	}
}

func getZeroCount(mid int, left [][]int64, right [][]int64, start int, end int) int64 {
	if start == mid && mid == end {
		if s[start] == 0 {
			return 2
		}
		return 1
	}
	if start == mid {
		// only right part
		count := right[end-mid-1]
		i := (m - s[mid]) % m
		return (count[0] + count[i]) % MOD
	}
	if end == mid {
		// only left part
		count := left[mid-start-1]
		i := (m - s[mid]) % m
		return (count[0] + count[i]) % MOD
	}
	count := left[mid-start-1]
	count2 := right[end-mid-1]
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
		//var mem runtime.MemStats
		if _, err := scan(&n, &m); err != nil {
			break
		}
		for i := 0; i < n; i++ {
			scan(&s[i])
			s[i] %= m
		}
		/*
			runtime.ReadMemStats(&mem)
			printf("mem: before tree, total m = %fKB", float64(mem.Alloc)/1024.0)
		*/
		t := new(Tree)
		scan(&q)
		for i := 0; i < q; i++ {
			var l, r int
			scan(&l, &r)
			queries[i].start = l - 1
			queries[i].end = r - 1
			t.AssignQuery(0, n-1, l-1, r-1, i)
		}
		t.ProcessQueries(0, n-1)
		for i := 0; i < q; i++ {
			printf("%d\n", queries[i].count)
		}
		/*
			runtime.ReadMemStats(&mem)
			printf("mem: total m = %fKB\n", float64(mem.Alloc)/1024.0)
		*/
	}
}
