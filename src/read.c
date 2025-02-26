#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	/* 1,打开瓶盖（打开文件） */
	int txt_fd = open("笔记.txt", O_RDWR);

	if (txt_fd == -1) {
		printf("open txt file failed!\n");
		return -1;
	}else {
		printf("open txt file success!\n");
	}
	
	/* 读取 1024 字节*/
	char buf[1024];
	
	read(txt_fd, buf, 1024);
	
	printf("%s\n", buf);
	
	close(txt_fd);

	return 0;
}