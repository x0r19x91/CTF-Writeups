# Roulette

> My most addictive habit is either gambling or reversing with IDA (500 points)

`main` takes the flag byte at offset 0x28 and xor's it with the bytes from 0x23e0 till the `main`. It then creates a new temp file with the new entry point and executes it. This pattern is followed to validate all the flag characters.  
Now there can be many bytes which on xoring will give a valid x86 code, but we have to select only one. The first guess is, all the entry points may start with the standard prologue - 0x55 (`push ebp`). But it fails for some offsets.  
The correct solution is to notice that all the xored entrypoints have a padding of `0xcc` bytes (`int3`), the padding used by MSVC.  
So, the byte for xoring is `0xcc ^ raw[prevEntryPoint-1]`

```asm
newEntryPoint:
  db ??, ??, ??, ...
prevEntryPoint:
  push ebp
  ...
  movzx e?x, byte ptr [e?x + flag_offset]
  ...
  mov e?x, offset newEntryPoint
  call xorDecrypt
  ...
```

Here's the solution using capstone bindings for Go

```go
package main

import (
    "fmt"
    "io/ioutil"
    "log"
    "strconv"
    "strings"

    "github.com/bnagy/gapstone"
)

func main() {
    raw, err := ioutil.ReadFile("E:\\CTF\\cscml\\roulette.exe")
    moduleBase := 0x400c00
    entryPoint := 0x23e0
    xorByte := byte(raw[0x24a0-1]^0xcc)
    if err != nil {
        log.Panic(err)
    }

    for i := entryPoint; i < 0x24a0; i++ {
        raw[i] ^= xorByte
    }

    dis, err := gapstone.New(gapstone.CS_ARCH_X86, gapstone.CS_MODE_32)
    if err != nil {
        log.Panic(err)
    }

    state := 0
    var pos int
    saved := 0x24a0
    i := 0
    array, err := dis.Disasm(raw[entryPoint:saved], uint64(moduleBase+entryPoint), uint64(saved-entryPoint))
    if err != nil {
        log.Panicln(err)
    }
    saved = entryPoint
    flag := make(map[int]byte)
    size := 0
    for ; i < len(array); i++ {
        asm := array[i]
        // fmt.Printf("%08x: %s %s\n", asm.Address, asm.Mnemonic, asm.OpStr)
        if asm.Address == uint(moduleBase+0x24a0) {
            break
        }
        if state == 0 && strings.Index(asm.OpStr, "byte ptr") >= 0 {
            state = 1
            // 1 indexed
            pos++
            pos = int(asm.Bytes[len(asm.Bytes)-1])-1
            if size < pos {
                size = pos
            }
        } else if state == 1 {
            x := strings.Index(asm.OpStr, ", 0x")
            if x == -1 {
                continue
            }
            state = 0
            if temp, err := strconv.ParseInt(asm.OpStr[x+4:], 16, 32); err == nil {
                entryPoint = int(temp)-moduleBase
                xorByte = byte(raw[saved-1]^0xcc)
                if _, err := flag[pos]; !err {
                    flag[pos] = xorByte
                }
                state = 0
                for i := entryPoint; i < saved; i++ {
                    raw[i] ^= xorByte
                }
                i = -1
                array, err = dis.Disasm(raw[entryPoint:saved], uint64(moduleBase+entryPoint), uint64(saved-entryPoint))
                if err != nil {
                    log.Panicln(err)
                }
                saved = entryPoint
            }
        }
    }

    flag[0x28] = 'm'
    szFlag := make([]byte, size+1)
    for i, j := range flag {
        szFlag[i] = j
    }
    fmt.Println(string(szFlag))
}
```

> `cscml2020{p3_i5_my_f4v0rit3_r0ul3tt3_f0rm4t}`
