all: out.c out2.c

out.c: main.c
	cpp -ansi < main.c | grep -v "#" > out.c

out2.c: T_Coast.c
	cpp -ansi < T_Coast.c | grep -v "#" > out2.c

.PHONY: clean
clean:
	rm out.c out2.c

