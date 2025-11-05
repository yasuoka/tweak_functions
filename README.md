adjust\_clock\_gettime
----------------------

Tweak ``clock_gettime(3)`` for debug by ``LD_PRELOAD``.

To adjust -1 day the result of ``clock_gettime(CLOCK_MONOTIME,)``

```
$ cc -shared -o adjust_clock_gettime.so -Wall adjust_clock_gettime.c
$ ADJUST_MONOTIME=-86400 LD_PRELOAD=./adjust_clock_gettime.so PROGRAM
```

tweak\_arc4random
------------------

Tweak ``arc4random(3)`` for debug by ``LD_PRELOAD``.

To limit 16 bits

```
$ cc -shared -o tweak_arc4random.so -Wall tweak_arc4random.c
$ TWEAK_ARC4RANDOM_NBITS=16 LD_PRELOAD=./tweak_arc4random.so PROGRAM
```
