#include <stdio.h>
#include "cn-cbor/cn-cbor.h"

/*
 * Encode the following JSON to CBOR and
 * decode it back.
 *
 * {
 *   name: "John",
 *   age: 31,
 *   city: "New York"
 * }
 */

int _parse_children(cn_cbor *first)
{
	cn_cbor *child = first;
	while (child) {
		switch (child->type) {
			case CN_CBOR_MAP:
				puts("Got a CBOR map!");
				_parse_children(child->first_child);
				break;
			case CN_CBOR_TEXT:
				printf("v: %.*s\n", child->length, child->v.str);
				break;
			case CN_CBOR_INT:
			case CN_CBOR_UINT:
				printf("v: %d\n", (int)child->v.sint);
				break;
			default:
				puts("ERROR: No handler for type");
		}

		/* get to next child */
		child = child->next;
	}

	return 0;
}


int main(void)
{
	/* Create CBOR map to hold the CBOR object key and value */
	cn_cbor *map = cn_cbor_map_create(NULL);
	if (!map) {
		puts("ERROR: failed creating cbor map: name_m");
		return -1;
	}

	/* Create CBOR object key and value */
	cn_cbor *name_v = cn_cbor_string_create("John", NULL);
	if (!name_v) {
		puts("ERROR: creating cbor string: John");
		return -1;
	}

	/* Put the CBOR object key and value to the created CBOR map */
	if (cn_cbor_mapput_string(map, "name", name_v, NULL)) {
		/* Null-terminate the string, because cn-cbor
		 * does not do this automatically */
		printf("SUCCESS: put key '%s' with value '%.*s' to map\n",
				"name", name_v->length,	name_v->v.str);
	}

	/* ***
	 * age
	 ****/

	cn_cbor *age_v = cn_cbor_int_create(31, NULL);
	if (!age_v) {
		puts("ERROR: creating cbor int: 31");
		return -1;
	}

	if (cn_cbor_mapput_string(map, "age", age_v, NULL)) {
		printf("SUCCESS: put key '%s' with value %d to map\n",
				"name", (int)age_v->v.sint);
	}

	/* ***
	 * city 
	 ****/

	cn_cbor *city_v = cn_cbor_string_create("New York", NULL);
	if (!city_v) {
		puts("ERROR: creating cbor string: New York");
		return -1;
	}

	if (cn_cbor_mapput_string(map, "city", city_v, NULL)) {
		printf("SUCCESS: put key '%s' with value '%.*s' to map\n",
				"name", city_v->length, city_v->v.str);
	}


	/* Encode the CBOR to buffer */
	size_t buf_size = 256;
	size_t buf_offset = 0;
	uint8_t buf[buf_size];
	ssize_t encoded_len = cn_cbor_encoder_write(buf, buf_offset,
					buf_size, (const cn_cbor *)map);
	if (encoded_len < 0) {
		puts("ERROR: fail to encode to buffer");
		return -1;
	} else if (encoded_len == 0) {
		puts("WARNING: no bytes encoded to buffer");
	} else {
		printf("SUCCESS: encoded %zd bytes to buffer\n", encoded_len);
	}


	/* Decoding the buffer */
	cn_cbor *decoded = cn_cbor_decode((const uint8_t *)buf,
					encoded_len, NULL);

	/* Get number of children of decoded CBOR array */
	int decoded_len = decoded->length;
	printf("decoded_len: %d\n", decoded_len);

	_parse_children(decoded->first_child);

	return 0;
}
