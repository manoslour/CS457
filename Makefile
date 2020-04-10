all: crypto

crypto: cs457_crypto.o main.c
	gcc -o crypto main.c cs457_crypto.o

cs457_crypto.o: cs457_crypto.c
	gcc -c cs457_crypto.c

clean:
	rm *o
