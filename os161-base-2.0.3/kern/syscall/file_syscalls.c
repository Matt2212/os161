#include <syscall.h>
#include <sys/types.h>
#include <lib.h>

ssize_t sys_write(int fd, const void *buff, size_t count){
	
	(void) fd;
	char* buf = (char*) buff;
	int i = 0;
	while(buff[i] != 0 && i < (int)count)
		putch(buff[i++]);
	return i;
}

ssize_t sys_read(int fd, void *buff, size_t count) {
	(void) fd;
	int i = 0;
	char* buf = (char*) buff;
        while(i < (int)count) {
        	buff[i] = getch();
		if (buff[i] < 0) return i;
		i++;
	}
	return i;
}
