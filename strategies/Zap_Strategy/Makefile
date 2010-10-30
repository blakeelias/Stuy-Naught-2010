.PHONY: all clean out.c out2.c

all: out.c out2.c

out.c: main.c
	cpp -ansi < main.c | grep -v -e "#" -e "//" -e "^$$" > out.c

out2.c: T_Coast.c
	cpp -ansi < T_Coast.c | grep -v -e "#" -e "//" -e "^$$" > out2.c

clean:
	rm out.c out2.c

