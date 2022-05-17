#ifndef __GPT_H__
#define __GPT_H__

#include <stdint.h>

#define PACK __attribute__((packed))

typedef struct {
  uint32_t time_low;
  uint16_t time_mid;
  uint16_t time_hi_and_version;
  uint8_t clock_seq_hi_and_reseved;
  uint8_t clock_seq_loq;
  uint8_t node[6];
} PACK Uuid;

typedef struct {
  uint8_t signature[8];
  uint32_t revision;
  uint32_t header_size;
  uint32_t header_crc32;
  uint32_t reserved;
  uint64_t current_lba;
  uint64_t backup_lba;
  uint64_t first_usable;
  uint64_t last_usable;
  Uuid disk_guid;
  uint64_t part_start_lba;
  uint32_t num_parts;
  uint32_t part_size;
  uint32_t part_table_crc32;
  // [u8; 96 - 512],
} PACK GPTHeader;

typedef struct {
  Uuid part_type;
  Uuid id;
  uint64_t first_lba;
  uint64_t last_lba;
  uint8_t attr[8];
  uint16_t name[36];
} PACK GPTPartition;

Uuid gpt_uuid_read(const Uuid *buffer);
GPTHeader gpt_read_header(const GPTHeader *buffer);
GPTPartition gpt_read_partition(GPTPartition *buffer);

#endif