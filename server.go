package main

import (
	"fmt"
	"net"
)

func main() {
	server, e := net.Listen("tcp4", ":8000")
	if e != nil {
		panic(e)
	}
	defer server.Close()

	fmt.Println(server)
	for {
		func() {
			conn, e := server.Accept()
			if e != nil {
				panic(e);
			}
			defer conn.Close()
			fmt.Println(conn)
		}()
	}
}
