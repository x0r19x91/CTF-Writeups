package main

import (
  "os"
  "strconv"
  "container/list"
  "fmt"
)

func main() {
	n, _ := strconv.Atoi(os.Args[1])
	l := list.New()
	l.PushFront(0)
	l.PushFront(1)
	for i := 0; i < n; i++ {
	  p := l.Front()
	  pn := p.Next()
	  l.PushFront(p.Value.(int)+pn.Value.(int))
	}
	fmt.Println(l.Front().Value)
}
