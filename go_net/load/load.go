package main

import (
	"fmt"
	"net"
	"os"
)

const (
	url      = "localhost:8889"
	protocol = "tcp"
)

// func ReadMessage() {
// 	buf := make([]byte, 1024)
// 	_, err := conn.Read(buf)
// 	if err != nil {
// 		fmt.Println("conn.read failed")
// 		os.Exit(1)
// 	}
// 	fmt.Println("server: ", string(buf))
// }

func SendMessage(conn net.Conn, message string) {
	_, err := conn.Write([]byte(message))
	if err != nil {
		fmt.Println("conn.write failed")
		os.Exit(1)
	}
}

func Load(conn net.Conn, message string, repeat int) {
	defer conn.Close()
	for i := 0; i < repeat; i++ {
		SendMessage(conn, message)
	}
}

func main() {
	log := fmt.Println

	conn, err := net.Dial(protocol, url)
	if err != nil {
		log("net.dial failed")
		os.Exit(1)
	}
	defer conn.Close()

	Load(conn, "hihi\n", 1)
}
