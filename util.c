#include "util.h"

static long int seed = 0;

static ti_int __mulddi3(du_int a, du_int b) {
    twords r;
    const int bits_in_dword_2 = (int)(sizeof(di_int) * CHAR_BIT) / 2;
    const du_int lower_mask = (du_int)~0 >> bits_in_dword_2;
    r.s.low = (a & lower_mask) * (b & lower_mask);
    du_int t = r.s.low >> bits_in_dword_2;
    r.s.low &= lower_mask;
    t += (a >> bits_in_dword_2) * (b & lower_mask);
    r.s.low += (t & lower_mask) << bits_in_dword_2;
    r.s.high = t >> bits_in_dword_2;
    t = r.s.low >> bits_in_dword_2;
    r.s.low &= lower_mask;
    t += (b >> bits_in_dword_2) * (a & lower_mask);
    r.s.low += (t & lower_mask) << bits_in_dword_2;
    r.s.high += t >> bits_in_dword_2;
    r.s.high += (a >> bits_in_dword_2) * (b >> bits_in_dword_2);
    return r.all;
}

ti_int __multi3(ti_int a, ti_int b) {
    twords x;
    x.all = a;
    twords y;
    y.all = b;
    twords r;
    r.all = __mulddi3(x.s.low, y.s.low);
    r.s.high += x.s.high * y.s.low + x.s.low * y.s.high;
    return r.all;
}

int rand_beebs(void) {
    seed = (seed * 1103515245L + 12345) & ((1UL << 31) - 1);
    return (int)(seed >> 16);
}

void srand_beebs(unsigned int new_seed) { seed = (long int)new_seed; }

/** STRING.h */
