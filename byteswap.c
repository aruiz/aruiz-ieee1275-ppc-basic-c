#include <stdint.h>

uint16_t
swap_bytes_16(uint16_t bytes) {
  uint16_t ret;
  uint8_t *retptr = (uint8_t*)&ret;
  uint8_t *bytesptr = (uint8_t*)&bytes;

  retptr[0] = bytesptr[1];
  retptr[1] = bytesptr[0];

  return ret;
}

uint32_t
swap_bytes_32(uint32_t bytes) {
  uint32_t ret;
  uint8_t *retptr = (uint8_t*)&ret;
  uint8_t *bytesptr = (uint8_t*)&bytes;

  retptr[0] = bytesptr[3];
  retptr[1] = bytesptr[2];
  retptr[2] = bytesptr[1];
  retptr[3] = bytesptr[0];

  return ret;
}

uint64_t
swap_bytes_64(uint64_t bytes) {
  uint32_t ret;
  uint8_t *retptr = (uint8_t*)&ret;
  uint8_t *bytesptr = (uint8_t*)&bytes;

  retptr[0] = bytesptr[7];
  retptr[1] = bytesptr[6];
  retptr[2] = bytesptr[5];
  retptr[3] = bytesptr[4];
  retptr[4] = bytesptr[3];
  retptr[5] = bytesptr[2];
  retptr[6] = bytesptr[1];
  retptr[7] = bytesptr[0];

  return ret;
}
