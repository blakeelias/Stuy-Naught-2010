.PHONY: all clean out1.c out2.c out3.c

all: out1.c out2.c out3.c

out1.c: main.c
	cpp -ansi < $< | grep -v -e "^#" -e "^//" -e "^$$" > $@

out2.c: T_Coast.c
	cpp -ansi < $< | grep -v -e "^#" -e "^//" -e "^$$" > $@

out3.c: T_Vfunc.c
	cpp -ansi < $< | grep -v -e "^#" -e "^//" -e "^$$" > $@

clean:
	rm out1.c out2.c out3.c


