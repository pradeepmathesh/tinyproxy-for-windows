CC      =       gcc

CFLAGS  =       -g -pedantic -DHAVE_CONFIG_H -DVERSION="\"@VERSION@\"" -DPACKAGE="\"@PACKAGE@\""
LINK    =       gcc
LDFLAGS  =
RANLIB = ranlib

OBJ = stats.o sock.o log.o network.o http_message.o htmlerror.o conns.o buffer.o anonymous.o acl.o hashmap.o \
	network.o reqs.o vector.o hashmap.o loop.o heap.o utils.o text.o\
	daemon.o filter.o scanner.o grammar.o
%.o : %.c
		#$(CC) $(CFLAGS) -c $< -o $@
		$(CC) -c $(DEFS) -I. $(CFLAGS) $<

all: libtinyproxy q

libtinyproxy: $(OBJ)
		rm -f libtinyproxy.a
		ar q $@.a $(OBJ)
		$(RANLIB) $@.a

q: $(OBJ) tinyproxy.o
		$(LINK) $(LDFLAGS) -o $@ tinyproxy.o libtinyproxy.a -lwsock32 -lpcreposix.dll -lpcre.dll
clean:
	rm *.o
	rm q.exe