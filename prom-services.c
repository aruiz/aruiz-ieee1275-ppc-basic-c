#include "prom-services.h"

extern IHandle* STDOUT;
extern EntryCB  ENTRY_CB;


uint32_t strlen(const char *str) {
  for (uint32_t i = 0; i < UINT32_MAX; i++)
    if (str[i] == '\0')
      return i;

  return 0;
}


void write_line(const char *msg) {
  uint32_t len = strlen(msg);

  if (len == 0)
    return;

  WriteArgs wargs = {{"write", 3, 1}, STDOUT, (void *)msg, len, 0};
  if (ENTRY_CB(&wargs.args) == -1)
    return;

  wargs = (WriteArgs){{"write", 3, 1}, STDOUT, "\n\r", 2, 0};
  ENTRY_CB (&wargs.args);
}

IHandle* open(const char *device) {
  OpenArgs openargs = {{"open", 1, 1}, device, 0};
  if (ENTRY_CB(&openargs.args) == -1 || openargs.handle == INVALID_PTR)
    return INVALID_PTR;

  return openargs.handle;
}

void close(IHandle *device) {
  CloseArgs closeargs = {{"open", 1, 0}, device};
  ENTRY_CB(&closeargs.args);
}

int32_t seek(IHandle *device, uint64_t pos) {
  SeekArgs seekargs = {{"seek", 3, 1}, device, pos, 0};
  if (ENTRY_CB(&seekargs.args) == -1 || seekargs.status == -1)
    return -1;

  return seekargs.status;
}

uint32_t read(IHandle *device, void *buffer, uint32_t size) {
  ReadArgs rargs = {{"read", 3, 1}, device, buffer, size, 0};
  if (ENTRY_CB(&rargs.args) == -1 || rargs.actual_size == UINT32_MAX)
    return -1;
  return rargs.actual_size;
}

void exit() {
  ServiceArgs args = {"exit", 1, 0};
  ENTRY_CB(&args);
}

uint32_t device_get_block_size(IHandle *device) {
  BlockSizeArgs bsargs = {{{"call-method", 2, 2}, "block-size", device}, 0, 0};
  if (ENTRY_CB(&bsargs.args.args) == -1 || bsargs.result != 0)
    return (uint32_t)-1;

  return bsargs.block_size;
}