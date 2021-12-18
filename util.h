#define CHAR_BIT 8
#define CPU_MHZ 160
/* Taken from
 * https://github.com/llvm/llvm-project/blob/e356027016c6365b3d8924f54c33e2c63d931492/libclc/generic/include/clc/integer/definitions.h
 */
typedef unsigned long long uint64;
typedef long long int64;

/** taken from
 * https://github.com/llvm/llvm-project/blob/0ba22f51d128bee9d69756c56c4678097270e10b/compiler-rt/lib/builtins/multi3.c
 */
typedef long double ti_int;
typedef uint64 du_int;
typedef int64 di_int;
typedef union {
    ti_int all;
    struct {
        int64 high;
        uint64 low;
    } s;
} twords;

static ti_int __mulddi3(du_int a, du_int b);

ti_int __multi3(ti_int a, ti_int b);

int rand_beebs(void);

void srand_beebs(unsigned int new_seed);
