#include "string.h"

void *memmove(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;

    if (d == s) return d;
    if ((uintptr_t)s - (uintptr_t)d - n <= -2 * n) return memcpy(d, s, n);

    if (d < s) {
        if ((uintptr_t)s % WS == (uintptr_t)d % WS) {
            while ((uintptr_t)d % WS) {
                if (!n--) return dest;
                *d++ = *s++;
            }
            for (; n >= WS; n -= WS, d += WS, s += WS) *(WT *)d = *(WT *)s;
        }
        for (; n; n--) *d++ = *s++;
    } else {
        if ((uintptr_t)s % WS == (uintptr_t)d % WS) {
            while ((uintptr_t)(d + n) % WS) {
                if (!n--) return dest;
                d[n] = s[n];
            }
            while (n >= WS) n -= WS, *(WT *)(d + n) = *(WT *)(s + n);
        }
        while (n) n--, d[n] = s[n];
    }

    return dest;
}

size_t strlen(const char *s) {
    const char *a = s;
    typedef size_t __attribute__((__may_alias__)) word;
    const word *w;
    for (; (uintptr_t)s % ALIGN; s++)
        if (!*s) return s - a;
    for (w = (const void *)s; !HASZERO(*w); w++)
        ;
    s = (const void *)w;
    for (; *s; s++)
        ;
    return s - a;
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

#define LS >>
#define RS <<

    typedef uint32_t __attribute__((__may_alias__)) u32;
    uint32_t w, x;

    for (; (uintptr_t)s % 4 && n; n--) *d++ = *s++;

    if ((uintptr_t)d % 4 == 0) {
        for (; n >= 16; s += 16, d += 16, n -= 16) {
            *(u32 *)(d + 0) = *(u32 *)(s + 0);
            *(u32 *)(d + 4) = *(u32 *)(s + 4);
            *(u32 *)(d + 8) = *(u32 *)(s + 8);
            *(u32 *)(d + 12) = *(u32 *)(s + 12);
        }
        if (n & 8) {
            *(u32 *)(d + 0) = *(u32 *)(s + 0);
            *(u32 *)(d + 4) = *(u32 *)(s + 4);
            d += 8;
            s += 8;
        }
        if (n & 4) {
            *(u32 *)(d + 0) = *(u32 *)(s + 0);
            d += 4;
            s += 4;
        }
        if (n & 2) {
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 1) {
            *d = *s;
        }
        return dest;
    }

    if (n >= 32) switch ((uintptr_t)d % 4) {
            case 1:
                w = *(u32 *)s;
                *d++ = *s++;
                *d++ = *s++;
                *d++ = *s++;
                n -= 3;
                for (; n >= 17; s += 16, d += 16, n -= 16) {
                    x = *(u32 *)(s + 1);
                    *(u32 *)(d + 0) = (w LS 24) | (x RS 8);
                    w = *(u32 *)(s + 5);
                    *(u32 *)(d + 4) = (x LS 24) | (w RS 8);
                    x = *(u32 *)(s + 9);
                    *(u32 *)(d + 8) = (w LS 24) | (x RS 8);
                    w = *(u32 *)(s + 13);
                    *(u32 *)(d + 12) = (x LS 24) | (w RS 8);
                }
                break;
            case 2:
                w = *(u32 *)s;
                *d++ = *s++;
                *d++ = *s++;
                n -= 2;
                for (; n >= 18; s += 16, d += 16, n -= 16) {
                    x = *(u32 *)(s + 2);
                    *(u32 *)(d + 0) = (w LS 16) | (x RS 16);
                    w = *(u32 *)(s + 6);
                    *(u32 *)(d + 4) = (x LS 16) | (w RS 16);
                    x = *(u32 *)(s + 10);
                    *(u32 *)(d + 8) = (w LS 16) | (x RS 16);
                    w = *(u32 *)(s + 14);
                    *(u32 *)(d + 12) = (x LS 16) | (w RS 16);
                }
                break;
            case 3:
                w = *(u32 *)s;
                *d++ = *s++;
                n -= 1;
                for (; n >= 19; s += 16, d += 16, n -= 16) {
                    x = *(u32 *)(s + 3);
                    *(u32 *)(d + 0) = (w LS 8) | (x RS 24);
                    w = *(u32 *)(s + 7);
                    *(u32 *)(d + 4) = (x LS 8) | (w RS 24);
                    x = *(u32 *)(s + 11);
                    *(u32 *)(d + 8) = (w LS 8) | (x RS 24);
                    w = *(u32 *)(s + 15);
                    *(u32 *)(d + 12) = (x LS 8) | (w RS 24);
                }
                break;
        }
    if (n & 16) {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
    }
    if (n & 8) {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
    }
    if (n & 4) {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
    }
    if (n & 2) {
        *d++ = *s++;
        *d++ = *s++;
    }
    if (n & 1) {
        *d = *s;
    }
    return dest;

    for (; n; n--) *d++ = *s++;
    return dest;
}

int memcmp(const void *vl, const void *vr, size_t n) {
    const unsigned char *l = vl, *r = vr;
    for (; n && *l == *r; n--, l++, r++)
        ;
    return n ? *l - *r : 0;
}

void *memset(void *dest, int c, size_t n) {
    unsigned char *s = dest;
    size_t k;

    /* Fill head and tail with minimal branching. Each
     * conditional ensures that all the subsequently used
     * offsets are well-defined and in the dest region. */

    if (!n) return dest;
    s[0] = c;
    s[n - 1] = c;
    if (n <= 2) return dest;
    s[1] = c;
    s[2] = c;
    s[n - 2] = c;
    s[n - 3] = c;
    if (n <= 6) return dest;
    s[3] = c;
    s[n - 4] = c;
    if (n <= 8) return dest;

    /* Advance pointer to align it at a 4-byte boundary,
     * and truncate n to a multiple of 4. The previous code
     * already took care of any head/tail that get cut off
     * by the alignment. */

    k = -(uintptr_t)s & 3;
    s += k;
    n -= k;
    n &= -4;

    typedef uint32_t __attribute__((__may_alias__)) u32;
    typedef uint64_t __attribute__((__may_alias__)) u64;

    u32 c32 = ((u32)-1) / 255 * (unsigned char)c;

    /* In preparation to copy 32 bytes at a time, aligned on
     * an 8-byte bounary, fill head/tail up to 28 bytes each.
     * As in the initial byte-based head/tail fill, each
     * conditional below ensures that the subsequent offsets
     * are valid (e.g. !(n<=24) implies n>=28). */

    *(u32 *)(s + 0) = c32;
    *(u32 *)(s + n - 4) = c32;
    if (n <= 8) return dest;
    *(u32 *)(s + 4) = c32;
    *(u32 *)(s + 8) = c32;
    *(u32 *)(s + n - 12) = c32;
    *(u32 *)(s + n - 8) = c32;
    if (n <= 24) return dest;
    *(u32 *)(s + 12) = c32;
    *(u32 *)(s + 16) = c32;
    *(u32 *)(s + 20) = c32;
    *(u32 *)(s + 24) = c32;
    *(u32 *)(s + n - 28) = c32;
    *(u32 *)(s + n - 24) = c32;
    *(u32 *)(s + n - 20) = c32;
    *(u32 *)(s + n - 16) = c32;

    /* Align to a multiple of 8 so we can fill 64 bits at a time,
     * and avoid writing the same bytes twice as much as is
     * practical without introducing additional branching. */

    k = 24 + ((uintptr_t)s & 4);
    s += k;
    n -= k;

    /* If this loop is reached, 28 tail bytes have already been
     * filled, so any remainder when n drops below 32 can be
     * safely ignored. */

    u64 c64 = c32 | ((u64)c32 << 32);
    for (; n >= 32; n -= 32, s += 32) {
        *(u64 *)(s + 0) = c64;
        *(u64 *)(s + 8) = c64;
        *(u64 *)(s + 16) = c64;
        *(u64 *)(s + 24) = c64;
    }

    return dest;
}

/* Initialize the BEEBS heap pointers. Note that the actual memory block is
   in the caller code. */

void init_heap_beebs(void *heap, size_t heap_size) {
    assert(heap_size % sizeof(void *) == 0); /* see #138 */
    heap_ptr = (void *)heap;
    heap_end = (void *)((char *)heap_ptr + heap_size);
    heap_requested = 0;
}

/* Report if malloc ever failed.

   Return non-zero (TRUE) if malloc did not reqest more than was available
   since the last call to init_heap_beebs, zero (FALSE) otherwise. */

int check_heap_beebs(void *heap) {
    return ((void *)((char *)heap + heap_requested) <= heap_end);
}

/* BEEBS version of malloc.

   This is primarily to reduce library and OS dependencies. Malloc is
   generally not used in embedded code, or if it is, only in well defined
   contexts to pre-allocate a fixed amount of memory. So this simplistic
   implementation is just fine.

   Note in particular the assumption that memory will never be freed! */

void *malloc_beebs(size_t size) {
    if (size == 0) return NULL;

    void *next_heap_ptr = (char *)heap_ptr + size;

    heap_requested += size;

    const size_t alignment = sizeof(void *);

    /* Check if the next heap pointer is aligned, otherwise add some padding */
    if (((uintptr_t)next_heap_ptr % alignment) != 0) {
        size_t padding = alignment - ((uintptr_t)next_heap_ptr % alignment);

        next_heap_ptr = (char *)next_heap_ptr + padding;

        /* padding is added to heap_requested because otherwise it will break
           check_heap_beebs() */
        heap_requested += padding;
    }

    /* Check if we can "allocate" enough space */
    if (next_heap_ptr > heap_end) return NULL;

    void *new_ptr = heap_ptr;
    heap_ptr = next_heap_ptr;

    return new_ptr;
}

/* BEEBS version of calloc.

   Implement as wrapper for malloc */

void *calloc_beebs(size_t nmemb, size_t size) {
    void *new_ptr = malloc_beebs(nmemb * size);

    /* Calloc is defined to zero the memory. OK to use a function here, because
       it will be handled specially by the compiler anyway. */

    if (NULL != new_ptr) memset(new_ptr, 0, nmemb * size);

    return new_ptr;
}

/* BEEBS version of realloc.

   This is primarily to reduce library and OS dependencies. We just have to
   allocate new memory and copy stuff across. */

void *realloc_beebs(void *ptr, size_t size) {
    if (ptr == NULL) return NULL;

    /* Get a new aligned pointer */
    void *new_ptr = malloc_beebs(size);

    /* This is clunky, since we don't know the size of the original pointer.
       However it is a read only action and we know it must be big enough if we
       right off the end, or we couldn't have allocated here. If the size is
       smaller, it doesn't matter. */

    if (new_ptr != NULL)
        for (size_t i = 0; i < size; i++)
            ((char *)new_ptr)[i] = ((char *)ptr)[i];

    return new_ptr;
}

/* BEEBS version of free.

   For our simplified version of memory handling, free can just do nothing. */

void free_beebs(void *ptr __attribute__((unused))) {}
