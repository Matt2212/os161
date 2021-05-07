#include <types.h>
#include <kern/unistd.h>
#include <clock.h>
#include <copyinout.h>
#include <syscall.h>
#include <lib.h>

int sys_write(int fd, void *buff, size_t count){

	if (fd!=STDOUT_FILENO && fd!=STDERR_FILENO) {
		kprintf("sys_write supported only to stdout\n");
		return -1;
	}
	char* buf = (char*) buff;
	int i = 0;
	while(buf[i] != 0 && i < (int)count)
		putch(buf[i++]);
	return i;
}

int sys_read(int fd, const void *buff, size_t count) {
	if (fd!=STDIN_FILENO) {
		kprintf("sys_write supported only to stdout\n");
		return -1;
	} 	int i = 0;
	char* buf = (char*) buff;
	while(i < (int)count) {
		buf[i] = getch();
		if (buf[i] < 0) return i;
		i++;
	}
	return i;
}
