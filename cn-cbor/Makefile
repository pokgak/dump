CC=gcc
CFLAGS=-std=c99 -no-pie -Wall -Wextra -Icn-cbor/include
#  -L to tell gcc where to find the library
#  -Wl,-rpath to make library available at runtime (alternative: export LD_LIBRARY_PATH)
#  -l<library name> to tell which library to use
LDFLAGS=-Lcn-cbor/build/dist/lib -Wl,-rpath=cn-cbor/build/dist/lib -lcn-cbor

OBJECTS=cbor-test.o cn-cbor/cn-cbor.o

cbor-test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o cbor-test

all: run

run: cbor-test
	./cbor-test

.PHONY: clean cn-cbor
clean:
	rm -f *~ *.o cbor-test

cn-cbor:
	cd cn-cbor && ./build.sh
	cd ..
