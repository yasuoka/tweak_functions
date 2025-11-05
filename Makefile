ALL=	adjust_clock_gettime.so adjust_arc4random.so

all: ${ALL}

adjust_clock_gettime.so: adjust_clock_gettime.c
	$(CC) -shared -o $@ -Wall adjust_clock_gettime.c
adjust_arc4random.so: adjust_arc4random.c
	$(CC) -shared -o $@ -Wall adjust_arc4random.c

clean:
	rm -f adjust_clock_gettime.so
	rm -f adjust_arc4random.so
