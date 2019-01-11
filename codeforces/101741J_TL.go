package main

import (
	"bufio"
	"fmt"
	"os"
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
	for t := 1; t * 2 <= n; t *= 2 {
		i++
	}
	return i
}


const MOD = int64(1000000007)
var n, m, q int
var s [200000]int
var cacheMap map[int64][]int64

type SegTree struct {
	count []int64
	left *SegTree
	right *SegTree
}

func NewSegTree() *SegTree {
	return &SegTree{count: make([]int64, m)}
}

var mergeCC int64

func (t *SegTree) mergeCount(l []int64, r []int64, to []int64) {
	mergeCC++
	for i := 0; i < m; i++ {
		if l[i] == 0 {
			continue
		}
		for j := 0; j < m; j++ {
			if r[j] == 0 {
				continue
			}
			c := l[i] * r[j]
			mod := (i + j) % m
			to[mod] = (to[mod] + c) % MOD
		}
	}
}

func (t *SegTree) InitValue(l, r int) {
	if l == r {
		t.count[0]++
		t.count[s[l] % m]++
		return
	}
	mid := (l + r) / 2
	t.left = NewSegTree()
	t.left.InitValue(l, mid)
	t.right = NewSegTree()
	t.right.InitValue(mid + 1, r)
	t.mergeCount(t.left.count, t.right.count, t.count)
}

func (t *SegTree) GetCountsForRange(l, r, start, end int) []int64 {
	if l >= start && r <= end {
		return t.count
	}
	mid := (l + r) / 2
	if end <= mid {
		return t.left.GetCountsForRange(l, mid, start, end)
	}
	if start >= mid + 1 {
		return t.right.GetCountsForRange(mid + 1, r, start, end)
	}
	key := (int64(start) << 20) | int64(end)
	res := cacheMap[key]
	if res != nil {
		return res
	}
	lc := t.left.GetCountsForRange(l, mid, start, mid)
	rc := t.right.GetCountsForRange(mid + 1, r, mid + 1, end)
	res = make([]int64, m)
	t.mergeCount(lc, rc, res)
	cacheMap[key] = res
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
		if _, err := scan(&n, &m); err != nil {
			break
		}
		for i := 0; i < n; i++ {
			scan(&s[i])
		}
		cacheMap = make(map[int64][]int64)
		t := NewSegTree()
		t.InitValue(0, n - 1)
		scan(&q)
		for i := 0; i < q; i++ {
			var l, r int
			scan(&l, &r)
			counts := t.GetCountsForRange(0, n - 1, l - 1, r - 1)
			printf("%d\n", counts[0])
		}
		//printf("mergeCC = %d\n", mergeCC)
	}
}