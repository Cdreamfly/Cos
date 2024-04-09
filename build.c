#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(const int argc, const char **argv) {
	int fd_kernel = open("../kernel.bin", O_WRONLY | O_CREAT, 0664);
	if (fd_kernel < 0) {
		fprintf(stderr, "open file error %s", strerror(errno));
		return 0;
	}
	int fd = open("boot16.bin", O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open file error %s", strerror(errno));
		return 0;
	}
	ssize_t c = 0;
	char buf[512] = {0};
	while (1) {
		c = read(fd, buf, sizeof(buf));
		if (c > 0) {
			write(fd_kernel, buf, sizeof(buf));
		} else break;
	}
	close(fd);

	lseek(fd_kernel, 0x20000 - 0x10000, SEEK_SET);

	fd = open("boot32.bin", O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open file error %s", strerror(errno));
		return 0;
	}
	while (1) {
		c = read(fd, buf, sizeof(buf));
		if (c > 0) {
			write(fd_kernel, buf, sizeof(buf));
		} else break;
	}
	close(fd);
	close(fd_kernel);
	return 0;
}
