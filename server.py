import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP) as server:
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(("10.0.0.92", 8000))
    server.listen()

    print("server: {}".format(server))

    while True:
        conn, addr = server.accept()
        with conn:
            print(conn)
            print(addr)
    
