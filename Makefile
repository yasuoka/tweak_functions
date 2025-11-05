ALL=	adjust_clock_gettime.so tweak_arc4random.so

all: ${ALL}

adjust_clock_gettime.so: adjust_clock_gettime.c
	$(CC) -shared -o $@ -Wall adjust_clock_gettime.c
tweak_arc4random.so: tweak_arc4random.c
	$(CC) -shared -o $@ -Wall tweak_arc4random.c

clean:
	rm -f adjust_clock_gettime.so
	rm -f tweak_arc4random.so
