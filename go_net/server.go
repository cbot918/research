package main

import (
	"fmt"
	"net"
	"os"
)

func main() {

	listen, err := net.Listen("tcp", "localhost:5555")
	fmt.Println("listen on: 5555")
	if err != nil {
		fmt.Println("net.Listen failed")
		os.Exit(1)
	}

	for {
		conn, err := listen.Accept()
		// block
		if err != nil {
			fmt.Println("listen.Accept failed")
			os.Exit(1)
		}

		go handleConn(conn)
	}
}

func handleConn(conn net.Conn) {
	defer conn.Close()
	packet := make([]byte, 1024)
	for {
		n, err := conn.Read(packet)
		if err != nil {
			continue
		}
		message := string(packet[:n])
		fmt.Println("client: ", message)
		_, _ = conn.Write(packet[:n])
	}
}
