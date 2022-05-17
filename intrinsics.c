#include <stdint.h>

void*
memcpy(void *destination, const void *source, uint32_t num) {
  uint8_t *dest = destination;
  const uint8_t *src = source;
  for (uint32_t i = 0; i < num; i++) {
    dest[i] = src[i];
  }

  return destination;
}

int
strncmp (const char* str1, const char *str2, uint32_t num) {
    for (uint32_t i=0; i<num; i++) {
        if (str1[0] != str2[0])
            return -1;
    }
    return 0;
}