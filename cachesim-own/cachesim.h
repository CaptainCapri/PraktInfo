#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <ctime>

struct MemAccess {
    typedef enum {CODE, LOAD, STORE, MODIFY} access_t;
    MemAccess(access_t t, unsigned long a, unsigned short s) : type(t), addr(a), size(s) {
    }

    access_t type;
    unsigned long addr;
    unsigned short size;
};

#define Rule FIFO

static bool powerof2(unsigned x) {
    return (x != 0) && !(x & (x - 1));
}

struct Cache {
    Cache(unsigned s, unsigned cl, unsigned w = 1) : size(s), cacheline(cl), ways(w) {
        assert(ways > 0 && powerof2(ways));
        assert(cacheline > 0 && powerof2(cacheline));

        offset_bits = log2(cl);
        offset_mask = (1 << offset_bits) - 1;

        index_bits = log2(size / cacheline / ways);
        index_mask = (1 << index_bits) - 1;

        tags = new unsigned long*[size / cacheline / ways];
        creationdate = new time_t*[size / cacheline / ways];
        accessdate = new time_t*[size / cacheline / ways];
        valid = new bool*[size / cacheline];
        for (unsigned i = 0; i < size / cacheline / ways; i++) {
            tags[i] = new unsigned long[ways];
            valid[i] = new bool[ways];
            creationdate[i] = new time_t[ways];
            accessdate[i] = new time_t[ways];


            for (unsigned j = 0; j < ways; j++) {
                tags[i][j] = 0;
                valid[i][j] = false;
                creationdate[i][j] = 0;
                accessdate[i][j] = 0;
            }
        }

        hits = misses = 0;
    }

    ~Cache() {
        for (unsigned i = 0; i < size / cacheline / ways; i++) {
            delete [] tags[i];
            delete [] valid[i];
            delete [] accessdate[i];
            delete [] creationdate[i];
        }
        delete [] tags;
        delete [] valid;
        delete [] creationdate;
        delete [] accessdate;
    }

    void process(const MemAccess &ma)  {
        assert(ma.size > 0);

        unsigned long tag;
        unsigned index;
        unsigned offset;
        split_address(ma.addr, tag, index, offset);

        // see if access touches more than one cacheline
        int s = ma.size;
        while (s > 0) {
            if (ma.type == MemAccess::LOAD || ma.type == MemAccess::CODE)
                process(tag, index, false);
            else if (ma.type == MemAccess::STORE)
                process(tag, index, true);
            else if (ma.type == MemAccess::MODIFY) {
                process(tag, index, false);
                process(tag, index, true);
            }

            s -= cacheline - offset;
            offset = 0;
        }
    }

    void process(unsigned long tag, unsigned index, bool write = false) {

        // see if address is in cache
        for (unsigned w = 0; w < ways; w++) {
            if (valid[index][w] && tags[index][w] == tag) {
                hit();
                accessdate[index][w] = time(0);
		 

                return;
            }
        }
        miss();

        // see if there is an empty set

        for(unsigned w = 0; w < ways; w++)
        {
            if ( !valid[index][w] )
            {
                tags[index][w] = tag;
                valid[index][w] = true;
                creationdate [index][w] = time (0);
                accessdate [index][w] = time (0);
                return;
            }

        }

		
			
#if RULE == LRU
        int j = 0;

        for(unsigned w = 0; w< ways; w++)
        {
            if (ways == 1)
            {
                accessdate [index][w] = time(0);
                tags[index][w] = tag;
                return;
            }



            if (ways > 1)
            {
                int i = w+1;

                if (accessdate[index][i] > accessdate [index][j])
                {
                    j = i;

                }

                if (w == ways - 1)
                {
                    accessdate [index][j] = time(0);
                    tags[index][j] = tag;
                    return;
                }

            }
        }







#elif RULE == FIFO
        int j = 0;

        for(unsigned w = 0; w< ways; w++)
        {
            if (ways == 1)
            {
                creationdate [index][w] = time(0);
                tags[index][w] = tag;
                return;
            }



            if (ways > 1)
            {
                int i = w+1;

                if (creationdate[index][i] > creationdate [index][j])
                {
                    j = i;

                }

                if (w == ways - 1)
                {
                    creationdate [index][j] = time(0);
                    tags[index][j] = tag;
                    return;
                }

            }
        }

#elif RULE == RANDOM
        //random evict strategy
        int numrand = rand() % ways;
        tags[index][numrand] = tag;
        return;
#endif

      // evict if necessary with replacement rule



        //LRU evict strategy


        // put address in cache
    }

    void hit() {
        hits++;
    }

    void miss() {
        misses++;
    }

    float hitRate() {
        return hits / (float) (hits + misses);
    }

    float missRate() {
        return misses / (float) (hits + misses);
    }

    float fillRate() {
        unsigned full = 0;
        unsigned empty = 0;
        for (unsigned i = 0; i < size / cacheline / ways; i++) {
            for (unsigned w = 0; w < ways; w++) {
                if (valid[i][w]) full++;
                else empty++;
            }
        }
        return full / (float) (full + empty);
    }

    void split_address(unsigned long addr, unsigned long &tag, unsigned &index, unsigned &offset) const {
        offset = addr & offset_mask;
        index = (addr >> offset_bits) & index_mask;
        tag = addr >> (offset_bits + index_bits);
    }

    void print_config() const {
        printf("size %d bytes, cacheline %d bytes, %d-ways associative\n",
            size, cacheline, ways);
        printf("  tag: %d bits\n", 64 - (offset_bits + index_bits));
        printf("  index: %d bits\n", index_bits);
        printf("  offset: %d bits\n", offset_bits);
        printf("  %d x %d cache entries\n", size / cacheline / ways, ways);
    }

    const unsigned size; // size of the cache in bytes
    const unsigned cacheline; // size of a cache line in bytes
    const unsigned ways; // associativity

    unsigned long offset_mask;
    unsigned offset_bits;
    unsigned long index_mask;
    unsigned index_bits;

    unsigned long **tags;
    bool **valid;

    unsigned hits;
    unsigned misses;
    time_t **creationdate;
    time_t **accessdate;


};
