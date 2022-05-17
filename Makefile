
SOURCES = boot.c prom-services.c gpt.c byteswap.c intrinsics.c crc32.c
HEADERS = prom-services.h gpt.h intrinsics.h crc32.h

boot-ppc: $(SOURCES) $(HEADERS)
	powerpc64le-linux-gnu-gcc -Wall -m32 -mbig-endian -fPIC -nostdlib -ffreestanding $(SOURCES) -o boot-ppc

disk-template.img: disk-template.gpt boot-ppc
	fallocate -l 256MiB disk-template.img
	sfdisk disk-template.img < disk-template.gpt
	dd if=boot-ppc of=disk-template.img bs=512 seek=2048 conv=notrunc

run-qemu: disk-template.img
	qemu-system-ppc64 -M pseries -drive file=disk-template.img -serial stdio

clean:
	rm -rf boot-ppc disk-template.img
