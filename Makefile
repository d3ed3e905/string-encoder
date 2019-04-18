build: encoder.o
	gcc -Wall encoder.o -o encoder -lm
encoder.o: encoder.c
	gcc -Wall -c encoder.c -o encoder.o -lm
run: encoder
	./encoder
clean:
	rm -f encoder.o encoder *~encoder
