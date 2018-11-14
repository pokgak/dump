#include <stdio.h>
#include <string.h>

static void _parse(char *copy, size_t limit)
{
    char *delim = ">=;,";
    char *attr, *val;
    int i = 0;

    attr = strtok(copy, delim);
    printf("-----Resource %d------\n", ++i);
    printf("path: %s\n", ++attr);
    
    while (i <= limit) {
        attr = strtok(NULL, delim);
        if (attr == NULL)
            break;
        if (strstr(attr, "coap://") != NULL) {
            printf("-----Resource %d------\n", ++i);
            printf("path: %s\n", ++attr);
            continue;
        }
        val = strtok(NULL, delim);
        if (*attr == '<' || *attr == ';')
            ++attr;

        printf("attr: %s; ", attr);
        printf("val: %s\n", val);
    }
}

int main(void)
{
    //const char teststr[] = "<coap://[2001:db8:3::123]:61616/temp>;rt=\"temperature\";anchor=\"coap://[2001:db8:3::123]:61616\"";
    const char teststr[] = "<coap://[2001:db8:3::124]/west>;rt=\"light\";anchor=\"coap://[2001:db8:3::124]\",<coap://[2001:db8:3::124]/south>;rt=\"light\";anchor=\"coap://[2001:db8:3::124]\",<coap://[2001:db8:3::124]/east>;rt=\"light\";anchor=\"coap://[2001:db8:3::124]\"";
    printf("test string: %s\nsize: %lu\n", teststr, sizeof(teststr));


    char copy[sizeof(teststr)];
    memcpy(copy, teststr, sizeof(teststr));

    _parse(copy, 3);
    return 0;
}
