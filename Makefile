ipof: ipof.c
	gcc -o ipof -Wall $<

install: ipof
	sudo cp ipof /usr/local/bin

clean:
	rm -rf *.o *.out
