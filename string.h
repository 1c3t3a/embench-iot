#define NULL ((void *)0)
#define UCHAR_MAX 255
#define ALIGN (sizeof(unsigned long) - 1)
#define ONES ((unsigned long)-1 / UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
#define HASZERO(x) ((x)-ONES & ~(x)&HIGHS)
typedef unsigned long size_t;
typedef unsigned int uintptr_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
#define assert(x) (void)0

void *memcpy(void *dest, const void *src, size_t n);

int memcmp(const void *, const void *, size_t);

void *memset(void *dest, int c, size_t n);

typedef __attribute__((__may_alias__)) size_t WT;
#define WS (sizeof(WT))

void *memmove(void *dest, const void *src, size_t n);

size_t strlen(const char *s);

#define HEAP_SIZE 1200
static char heap[HEAP_SIZE];

static const char *encode;
static int size;

static int benchmark_body(int rpt);

/* Heap records and sane initial values */

static void *heap_ptr = NULL;
static void *heap_end = NULL;
static size_t heap_requested = 0;

void free_beebs(void *ptr __attribute__((unused)));

void *realloc_beebs(void *ptr, size_t size);

void *calloc_beebs(size_t nmemb, size_t size);

void *malloc_beebs(size_t size);

int check_heap_beebs(void *heap);

void init_heap_beebs(void *heap, size_t heap_size);
