# Copyright (C) 2013  Jérémie Galarneau <jeremie.galarneau@efficios.com>
#
# THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
# OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
#
# Permission is hereby granted to use or copy this program for any
# purpose,  provided the above notices are retained on all copies.
# Permission to modify the code and to distribute modified code is
# granted, provided the above notices are retained, and a notice that
# the code was modified is included with the above copyright notice.

CC = gcc
LIBS = -lbabeltrace-ctf
LOCAL_CPPFLAGS += -I.

all: unaligned-float

unaligned-float: unaligned-float.o
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(AM_CFLAGS) \
		unaligned-float.o $(LIBS)

unaligned-float.o: unaligned-float.c
	$(CC) $(CPPFLAGS) $(LOCAL_CPPFLAGS) $(CFLAGS) $(AM_CPPFLAGS) \
		$(AM_CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o unaligned-float
