#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DEBUG 1
#ifndef NDEBUG
    #define D(x) do { if (DEBUG) { x; } } while (0)
#else
    #define D(x)
#endif

int main() {
    return 0;
}