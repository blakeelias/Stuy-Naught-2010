out.c: main.c
	cpp -ansi < main.c | grep -v "#" > out.c

.PHONY: clean
clean:
	rm out.c

