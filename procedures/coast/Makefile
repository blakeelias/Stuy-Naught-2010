.PHONY: all clean out1.c out2.c

all: out1.c out2.c

out1.c: K_Coast.c
	cpp -ansi < $< | grep -v -e "^#" -e "^//" -e "^$$" > $@

out2.c: K_Vfunc.c
	cpp -ansi < $< | grep -v -e "^#" -e "^//" -e "^$$" > $@

clean:
	rm out1.c out2.c

