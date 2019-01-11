package main

import (
	"bufio"
	"fmt"
	"os"
	"math/rand"
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



func main() {
	defer stdout.Flush()
	n := 200000
	m := 3
	q := 200000
	printf("%d %d\n", n, m)
	for i := 0; i < n; i++ {
		v := rand.Int() % 1000000001
		printf("%d ", v)
	}
	printf("\n%d\n", q)
	for i := 0; i < q; i++ {
		l := rand.Int() % n + 1
		r := rand.Int() % n + 1
		if l > r {
			l, r = r, l
		}
		printf("%d %d\n", l, r)
	}
}