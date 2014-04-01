#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>

#include "cachesim.h"

int main() {

    FILE *f = fopen("trace-ex1.txt", "rt");
    if (!f) return EXIT_FAILURE;

    Cache cache(128, 32, 1);
    cache.print_config();

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        unsigned long addr;
        unsigned short size;
        sscanf(&line[3], "%lx,%hx\n", &addr, &size);

        if (line[1] == 'L')
            cache.process(MemAccess(MemAccess::LOAD, addr, size));
    }

    printf("instructions: %.4f hits, %.4f misses, %.2f full\n",
        cache.hitRate(), cache.missRate(), cache.fillRate());

    return EXIT_SUCCESS;
}
