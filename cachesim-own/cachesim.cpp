#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>

#include "cachesim.h"

int main() {

    srand ( time (0));

    FILE *f = fopen("trace-ls.txt", "rt");
    if (!f) return EXIT_FAILURE;

    Cache icache(4096, 32, 1);
    icache.print_config();

    Cache dcache(262144, 32, 4);
    dcache.print_config();

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        unsigned long addr;
        unsigned short size;
        sscanf(&line[3], "%lx,%hx\n", &addr, &size);

        if (line[0] == 'I')
            icache.process(MemAccess(MemAccess::CODE, addr, size));
        else if (line[1] == 'L')
            dcache.process(MemAccess(MemAccess::LOAD, addr, size));
        else if (line[1] == 'S')
            dcache.process(MemAccess(MemAccess::STORE, addr, size));
        else if (line[1] == 'M')
            dcache.process(MemAccess(MemAccess::MODIFY, addr, size));
    }

    printf("instructions: %.4f hits, %.4f misses, %.2f full\n",
        icache.hitRate(), icache.missRate(), icache.fillRate());
    printf("data: %.4f hits, %.4f misses, %.2f full\n",
        dcache.hitRate(), dcache.missRate(), dcache.fillRate());

    return EXIT_SUCCESS;
}
