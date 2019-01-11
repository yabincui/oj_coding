package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
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

func main() {
	n, m, a, b := 1000, 1000, 5, 5
	printf("%d %d %d %d\n", n, m, a, b)
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			t := rand.Int31()
			printf("%d ", t)
		}
		printf("\n")
	}
	stdout.Flush()
}