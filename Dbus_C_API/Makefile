all: server client

# Define pkg-config path
pkg_packages := dbus-1

PKG_CFLAGS := $(shell pkg-config --cflags $(pkg_packages))
PKG_LDFLAGS := $(shell pkg-config --libs $(pkg_packages))

CC = gcc

CFLAGS += -g -Wall $(PKG_CFLAGS)
LDFLAGS += $(PKG_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

server: server.o
	$(CC) -o $@ $^ $(LDFLAGS)

client: client.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f server client *.o *~
