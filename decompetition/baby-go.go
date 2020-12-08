package main

import (
  "strconv"
  "os"
  "fmt"
)

func main() {
  xn, _ := strconv.Atoi(os.Args[1])
  n := uint64(xn)
  if n * ^uint64(0x1111111111111110) + 0x888888888888888 <= 0x1111111111111110 {
    fmt.Println("Green")
    // return
  } else if n * ^uint64(0x5555555555555554) + 0x2aaaaaaaaaaaaaaa <= 0x5555555555555554 {
    fmt.Println("Yellow")
  } else if n * ^uint64(0x3333333333333332) + 0x1999999999999999 <= 0x3333333333333332 {
    fmt.Println("Blue")
    // return
  } else {
    fmt.Println(n)
  }
}
