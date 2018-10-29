#include "list.h"
#include <stdio.h>
#include <string.h>

int list_add_pair(pair_t *pairs, int maxsize, const char *key, const char *val)
{
    puts("adding pair");
    int count = 0;
    pair_t *current = pairs;
    /* get to last pair in pairs */
    while (current) {
        current = current->next;
        count++;
        /* stop if we are already at max allowed pairs */
        if (count > maxsize) {
            return -1;
        }
    }
    /* write new pair to pairs */
    pair_t newpair  = {
        .key = key,
        .val = val,
    };
    memcpy((void *)&(pairs[count - 1]), (void *) &newpair, sizeof(newpair));

    return 0;
}

int list_dump_pairs(pair_t *pairs)
{
    puts("dumping pairs");
    int count = 0;
    pair_t *pair = pairs;
    while (pair) {
        printf("Pair[%d]: key=%.*s; val=%.*s;\n",
                count,
                (int)sizeof(pair->key), pair->key,
                (int)sizeof(pair->val), pair->val);
        pair = pair->next;
        count++;
    }
    return 0;
}
