#include "prom-services.h"
#include "gpt.h"
#include "intrinsics.h"
#include "crc32.h"

EntryCB ENTRY_CB;
IHandle *STDOUT;
LBA BLOCKBUFFER;

void _start(int _a, int _b, EntryCB callback) {
  ENTRY_CB = callback;
  IHandle *disk = 0;
  STDOUT = 0;
  char propbuf[1024];

  for (int i = 0; i < sizeof(propbuf); i++)
    propbuf[i] = 0;
  for (int i = 0; i < sizeof(BLOCKBUFFER); i++)
    BLOCKBUFFER.d4096[i] = 0;

  FindDeviceArgs fdargs = {{"finddevice", 1, 1}, "/chosen", 0};
  if (callback(&fdargs.args) == -1 || fdargs.phandle == (PHandle *)-1)
    return;

  PropArgs propargs = {{"getprop", 4, 1},  fdargs.phandle, "stdout",
                       (uint8_t *)&STDOUT, sizeof(void *), 0};
  if (callback(&propargs.args) == -1 || propargs.size == -1)
    return;

  write_line("Hello world from C into OpenFirmware!");

  propargs = (PropArgs){{"getprop", 4, 1},  fdargs.phandle,      "bootpath",
                        (uint8_t *)propbuf, sizeof(propbuf) - 1, 0};
  if (callback(&propargs.args) == -1 || propargs.size == -1)
    return;

  disk = open(propbuf);
  if (disk == INVALID_PTR) {
    write_line("Could not open device");
    write_line(propbuf);
    exit();
  }

  uint32_t blksize = device_get_block_size(disk);
  uint32_t block_cur = blksize * 1;

  if (blksize != 512 && blksize != 4096) {
    write_line(
        "Block sizes different than 512 and 4096 bytes are not supported");
    goto out;
  }

  if (seek(disk, block_cur) == -1) {
    write_line("Could not seek");
    goto out;
  }

  if (read(disk, &BLOCKBUFFER, blksize) != blksize) {
    write_line("Could not read a block");
  }

  GPTHeader gpt_header = gpt_read_header((GPTHeader*)&BLOCKBUFFER);
  if (strncmp ((const char*)gpt_header.signature, "EFI PART", 8) != 0) {
    write_line("Invalid GPT signature");
    goto out;
  }

  gpt_header.header_crc32 = 0;

  crc_update (crc_init(), &gpt_header, gpt_header.);

out:
  close(disk);
  exit();
}
