#include "insertionsort.h"
#include <cstdio>

struct sth {
    int start_time {};
};

int main (int argc, char *argv[]) {
    sth a, b, c, d;
    a.start_time =  1;
    b.start_time =  2;
    c.start_time =  3;
    d.start_time =  44;
    sth* arr[4] = {&d, &a, &c, &b};

    insertionSort(arr, 4);
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", arr[i]->start_time);
    }

    
    return 0;
}
