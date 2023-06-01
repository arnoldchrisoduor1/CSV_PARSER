CC = gcc
CFLAGS = -Wall -g
LIB = libhashtable
BINS = $(LIB).so $(LIB).a test

all: $(BINS)

test: test.c $(LIB).a
	$(CC) $(CFLAGS) -O $< -o $@ -L. -lhashtable

$(LIB).a: hashtable.o
	ar rcs $@ $<

$(LIB).so: hashtable.c
	$(CC) $(CFLAGS) -shared -fPIC $< -o $@

clean:
	rm -rf *.dSYM *.so *.a *.o $(BINS)
