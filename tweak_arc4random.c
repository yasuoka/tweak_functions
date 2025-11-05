/*
 * Copyright (c) 2025 YASUOKA Masahiko <yasuoka@yasuoka.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * cc -shared -o tweak_arc4random.so -Wall tweak_arc4random.c
 */
#include <sys/types.h>
#include <dlfcn.h>
#include <limits.h>
#include <stdlib.h>

static void		  arc4random_initialize(void);
static uint32_t		(*libc_arc4random_uniform)(uint32_t) = NULL;
static int volatile	  arc4random_initialized = 0;

void
arc4random_initialize(void)
{
	void	*libc;

	if (arc4random_initialized != 0)
		return;
	arc4random_initialized = 1;
	if ((libc = dlopen("libc.so", RTLD_NOW)) == NULL)
		return;

	libc_arc4random_uniform = dlsym(libc, "arc4random_uniform");
	dlclose(libc);
}

#include <unistd.h>

uint32_t
arc4random(void)
{
	uint32_t	 nbits = 32, ub = 0xFFFFFFFFUL;
	const char	*str, *errstr;

	arc4random_initialize();

	if ((str = getenv("TWEAK_ARC4RANDOM_NBITS")) != NULL) {
		nbits = strtonum(str, 0, 32, &errstr);
		if (errstr != NULL)
			nbits = 32;
	}
	if (nbits < 32)
		ub >>= (32 - nbits);

	return (libc_arc4random_uniform(ub));
}
