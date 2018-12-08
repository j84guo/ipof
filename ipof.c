#include <stdio.h>
#include <string.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <sys/types.h>

void default_hints(struct addrinfo *hints)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_UNSPEC;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_protocol = IPPROTO_TCP;
}

void print_addrinfo(struct addrinfo *info)
{
	char *version;
	void *addr;

	if (info->ai_family == AF_INET) {
		version = "IPv4";
		addr = &((struct sockaddr_in *) info->ai_addr)->sin_addr;
	} else {
		version = "IPv6";
		addr = &((struct sockaddr_in6 *) info->ai_addr)->sin6_addr;
	}

	char ip[INET6_ADDRSTRLEN];
	inet_ntop(info->ai_family, addr, ip, INET6_ADDRSTRLEN);
	printf("[%s] %s\n", version, ip);
}

int find_addresses(char *hostname)
{
	struct addrinfo hints;
	default_hints(&hints);

	struct addrinfo *info;
	int ret = getaddrinfo(hostname, NULL, &hints, &info);
	if (ret) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		return -1;
	}

	int num = 0;
	for (struct addrinfo *ptr = info; ptr; ptr = ptr->ai_next) {
		print_addrinfo(ptr);
		++num;
	}

	freeaddrinfo(info);
	return num;
}

int resolve_hosts(int num_hosts, char *hostlist[])
{
	int res = 0;

	for (int i = 0; i < num_hosts; ++i) {
		printf("Host: %s\n", hostlist[i]);
		int num_addr = find_addresses(hostlist[i]);
		if (num_addr == -1)
			res = -1;
		else if (num_addr > 0 && i != num_hosts - 1)
			printf("\n");
	}

	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
		return 1;
	}

	return !resolve_hosts(argc - 1, argv + 1) ? 0 : 1;
}
