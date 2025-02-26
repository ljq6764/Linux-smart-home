#include <stdio.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/* arm-none-linux-gcc ts_printf.c -o ts */
int main(void)
{
	/* 打开文件 */
	int ts_fd = open("/dev/input/event0", O_RDWR);
	/* 数据处理：读取 */
	struct input_event ts;

	/* char* buf[800*480*3] */
	/* read(bmp_fd, buf, 800*480*3); */

	read(ts_fd, &ts, sizeof(ts));

	printf("type : %d\t", ts.type);
	printf("code : %d\t", ts.code);
	printf("value : %d\t", ts.value);
	
	/* 关闭文件 */
	close(ts_fd);

	return 0;
}