typedef struct pair {
    const char *key;
    const char *val;
    struct pair *next;
} pair_t;

int list_add_pair(pair_t *pairs, int maxsize, const char *key, const char *val);
int list_dump_pairs(pair_t *pairs);
