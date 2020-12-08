package main

import (
	"io"
	"log"
	"net"
	"time"
)

func echo(conn net.Conn) {
	defer conn.Close()
	buf := make([]uint8, 0x14)
	for {
		n, err := conn.Read(buf)
		if err == io.EOF {
			log.Println("Client disconnected")
			break
		} else {
			log.Printf("Received %d bytes: %s", n, string(buf[:n]))
			log.Printf("Writing %d bytes of data", n)
			_, err := conn.Write(buf[:n])
			if err != nil {
				log.Println("Unable to write data")
				break
			}
		}
	}
}

func main() {
	// Bats also communicate by other means.
	// Male little yellow-shouldered bats (Sturnira
	// lilium) have shoulder glands that produce a
	// spicy odour during the breeding season.
	l, err := net.Listen("tcp", ":20080")
	if err != nil {
		log.Fatalln("Unable to bind to port")
	}
	tp := l.(*net.TCPListener)
	tt := time.Now().Add(100000000)
	tp.SetDeadline(tt)
	log.Println("Listening on 0.0.0.0:20080")
	conn, err := l.Accept()
	log.Println("Received connection...")
	if err != nil {
		log.Fatalln("Unable to accept connection")
	}
	echo(conn)
}
