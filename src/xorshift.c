#include "../inc/Header.h"

Uint8 xorshift() {
    static Uint32 x = 123456789;
    static Uint32 y = 362436069;
    static Uint32 z = 521288629;
    static Uint32 w = 88675123;
    Uint32 t;
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}
