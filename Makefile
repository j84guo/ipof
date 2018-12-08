ipof: ipof.c
	gcc -o ipof -Wall $<

clean:
	rm -rf *.o *.out
