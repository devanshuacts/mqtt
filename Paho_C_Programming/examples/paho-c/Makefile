#LDFLAGS=-lpaho-mqtt3c
LDFLAGS=-lpaho-mqtt3c
all:pubtest subtest cleantest asyncpub asyncsub
pubtest:pubtest.o
	gcc $< -o $@ -lpaho-mqtt3c
subtest:subtest.o
	gcc $< -o $@ -lpaho-mqtt3c
cleantest:cleantest.o
	gcc $< -o $@ -lpaho-mqtt3c
asyncpub:asyncpub.o
	gcc $< -o $@ -lpaho-mqtt3a
asyncsub:asyncsub.o
	gcc $< -o $@ -lpaho-mqtt3a
clean:
	rm -f *.o pubtest subtest cleantest asyncpub asyncsub
