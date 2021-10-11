all:
	cc *.c -lm -lX11 -Wextra -Wall -pedantic -o ns

install:ns
	mkdir -p /usr/local/bin
	cp ns /usr/local/bin/ns
	chmod +x /usr/local/bin/ns

clean:
	rm -f /usr/local/bin/ns
	rm -f ns
