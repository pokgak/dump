#include "list.h"

#define MAXSIZE         (2)

static pair_t pairs[MAXSIZE];

int main(void)
{
    list_add_pair(pairs, MAXSIZE, "key0", "val0");
    list_add_pair(pairs, MAXSIZE, "key1", "val1");

    list_dump_pairs(pairs);
    return 0;
}
