all:rbtree-tst

CFLAGS=-g -O0 -Wall

rbtree-tst:test_rbtree.o pub_rbtree.o

pub_rbtree.o:pub_rbtree.h pub_rbtree.c

test_rbtree.o:test_rbtree.c

.PHONY:clean

clean:
	rm *.o rbtree-tst
