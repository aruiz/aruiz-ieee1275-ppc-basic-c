#ifndef __BOOT_TYPES_H__
#define __BOOT_TYPES_H__

#include <stdint.h>

#define INVALID_PTR (void *)-1

typedef struct {
} PHandle;
typedef struct {
} IHandle;

typedef struct {
  char *service;
  int nargs;
  int nret;
} ServiceArgs;

typedef struct {
  ServiceArgs args;
  char *device;
  PHandle *phandle;
} FindDeviceArgs;

typedef struct {
  ServiceArgs args;
  PHandle *phandle;
  char *prop;
  uint8_t *buf;
  uint32_t buflen;
  int32_t size;
} PropArgs;

typedef struct {
  ServiceArgs args;
  IHandle *ihandle;
  char *msg;
  int32_t len;
  int32_t ret;
} WriteArgs;

typedef struct {
  ServiceArgs args;
  uint8_t *virt;
  uint32_t size;
  uint32_t align;
  uint8_t *ret;
} ClaimArgs;

typedef struct {
  ServiceArgs args;
  uint8_t *virt;
  uint32_t size;
} ReleaseArgs;

typedef struct {
  ServiceArgs args;
  const char *dev;
  IHandle *handle;
} OpenArgs;

typedef struct {
  ServiceArgs args;
  IHandle *handle;
  uint8_t *buffer;
  uint32_t size;
  uint32_t actual_size;
} ReadArgs;

typedef struct {
  ServiceArgs args;
  IHandle *handle;
} CloseArgs;

typedef struct {
  ServiceArgs args;
  IHandle *handle;
  uint64_t pos;
  int32_t status;
} SeekArgs;

typedef struct {
  ServiceArgs args;
  char *method;
  IHandle *handle;
} CallMethodArgs;

typedef struct {
  CallMethodArgs args;
  uint32_t result;
  uint32_t block_size;
} BlockSizeArgs;

typedef struct {
  uint8_t __data[512];
} LBA512;

typedef struct {
  uint8_t __data[4096];
} LBA4096;

typedef union {
  uint8_t d512[512];
  uint8_t d4096[4096];
} LBA;

typedef int (*EntryCB)(ServiceArgs *);

void write_line(const char *msg);
IHandle *open(const char *device);
void close(IHandle *device);
int32_t seek(IHandle *device, uint64_t pos);
uint32_t read(IHandle *device, void *buffer, uint32_t size);
void exit();
uint32_t device_get_block_size(IHandle *device);

#endif // __BOOT_TYPES_H__
