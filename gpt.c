#include "gpt.h"

uint64_t swap_bytes_64(uint64_t bytes);
uint32_t swap_bytes_32(uint32_t bytes);
uint16_t swap_bytes_16(uint16_t bytes);

Uuid gpt_uuid_read(const Uuid *buffer) {
  Uuid ret = *(Uuid *)buffer;

  ret.time_low = swap_bytes_32(ret.time_low);
  ret.time_mid = swap_bytes_16(ret.time_mid);
  ret.time_hi_and_version = swap_bytes_16(ret.time_hi_and_version);

  return ret;
}

GPTHeader gpt_read_header(const GPTHeader *buffer) {
  GPTHeader ret = *buffer;

  ret.revision = swap_bytes_32(ret.revision);
  ret.header_size = swap_bytes_32(ret.header_size);
  ret.header_crc32 = swap_bytes_32(ret.header_crc32);
  ret.current_lba = swap_bytes_64(ret.current_lba);
  ret.first_usable = swap_bytes_64(ret.first_usable);
  ret.last_usable = swap_bytes_64(ret.last_usable);
  ret.disk_guid = gpt_uuid_read(&ret.disk_guid);
  ret.num_parts = swap_bytes_32(ret.num_parts);
  ret.part_size = swap_bytes_32(ret.part_size);
  ret.part_size = swap_bytes_32(ret.part_table_crc32);

  return ret;
}

GPTPartition gpt_read_partition(GPTPartition *buffer) {
  GPTPartition ret = *buffer;

  ret.part_type = gpt_uuid_read(&ret.part_type);
  ret.id = gpt_uuid_read(&ret.id);
  ret.first_lba = swap_bytes_64(ret.first_lba);
  ret.last_lba = swap_bytes_64(ret.last_lba);

  for (uint32_t i = 0; i < sizeof(ret.name); i++) {
    ret.name[i] = swap_bytes_16(ret.name[i]);
  }

  return ret;
}