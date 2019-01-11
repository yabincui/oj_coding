package main

import (
	"bufio"
	"fmt"
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

var s string

func main() {
	for true {
		if _, err := scan(&s); err != nil {
			break
		}
		n := len(s)
		longest := 0
		count := 1
		var leftBraceStack []int
		leftBraceStack = append(leftBraceStack, -1)
		stackI := 0
		for i := 0; i < n; i++ {
			if s[i] == '(' {
				if stackI + 1 == len(leftBraceStack) {
					leftBraceStack = append(leftBraceStack, i)
				} else {
					leftBraceStack[stackI + 1] = i
				}
				stackI++
			} else {
				if stackI > 0 {
					length := i - leftBraceStack[stackI - 1]
					stackI--
					if length == longest {
						count++
					} else if (length > longest) {
						longest = length
						count = 1
					}
				} else {
					leftBraceStack[0] = i
				}
			}
		}
		printf("%d %d\n", longest, count)
		stdout.Flush()
	}
}