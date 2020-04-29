p : L08_01_bkim1790_fg.o L08_01_bkim1790_fo.o
	gcc -Wall L08_01_bkim1790_fg.o L08_01_bkim1790_fo.o -o p -lm

L08_01_bkim1790_fg.o : L08_01_bkim1790_fg.c headerfile.h
	gcc -Wall L08_01_bkim1790_fg.c -c

L08_01_bkim1790_fo.o : L08_01_bkim1790_fo.c headerfile.h
	gcc -Wall L08_01_bkim1790_fo.c -c     
.PHONY : clean
clean:
	rm -f p L08_01_bkim1790_fg.o L08_01_bkim1790_fo.o core *~ 
