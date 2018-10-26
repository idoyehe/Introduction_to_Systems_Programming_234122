#ifndef HW2_WET_MY_MALLOC_H
#define HW2_WET_MY_MALLOC_H

#include <stdlib.h>
#define EVERY 30
static inline void* my_malloc(int size) {
    static int x = 0;
    ++x;
    if (x % EVERY) {
        return malloc(size);
    }

    return NULL;
}

#define malloc(x) my_malloc(x)


#endif //HW2_WET_MY_MALLOC_H
