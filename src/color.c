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
	}
	
	/* 2，喝水、倒水（数据处理：写入，读取） */
	
	/* a 设置即将要显示的颜色 */
	
	/* b 将数据写入到开发板上 */
	write(txt_fd, argb_buf, ???);
	
	/* 3，盖上瓶盖（关闭文件） */
	close(txt_fd);

	return 0;
}