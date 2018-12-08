package main

import (
	"os"
	"fmt"
	"net"
)

func resolve_hosts(hostlist []string) {
	for i, hostname := range hostlist {
		fmt.Println("Host:", hostname)
		results, e := net.LookupHost(hostname)
		if e != nil {
			fmt.Fprintf(os.Stderr, "%s\n", e.Error())
			continue
		}
		for _, addr := range results {
			fmt.Println(addr)
		}
		if i != len(hostlist) - 1 {
			fmt.Println()
		}
	}
}

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "Usage: ./ipof <hostname>\n")
		return
	}
	resolve_hosts(os.Args[1:])
}
