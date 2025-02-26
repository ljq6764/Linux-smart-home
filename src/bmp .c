#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int show_bmp(const char *pathname, int x, int y, int w, int h)
{
	/* 1，打开文件 */
	
	/* a 打开图片文件：1.bmp */
	
	int bmp_fd = open(pathname, O_RDWR);

	if (bmp_fd == -1) {
		printf("open bmp file failed!\n");
		return -1;
	}
	
	/* b 打开lcd设备文件 */
	
	int lcd_fd = open("/dev/fb0", O_RDWR);

	if (lcd_fd == -1) {
		printf("open lcd devcie failed!\n");
		return -1;
	}
	
	/* 2，数据处理：写入，读取 */
	
	char header[54];
	char rgb_buf[w*h*3];
	/* 屏幕的大小 */
	int lcd_buf[800*480];
	
	/* 处理文件头，拿到真正的图片颜色数据 */
	read(bmp_fd, header, 54);
	/* a 将图片文件里面颜色数据读取出来 */
	read(bmp_fd, rgb_buf, w*h*3);
	
	/* 24 --- 32*/
	
	int i, j;
	int r, g, b, color;
	
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			b = rgb_buf[(w*j+i)*3+0];
			g = rgb_buf[(w*j+i)*3+1];
			r = rgb_buf[(w*j+i)*3+2];
			
			/* 24 --- 32 */
			color = (r | g << 8 | b);
			
			/* 0 479 */
			/* 1 478 */
			/* 2 477 */
			/* 3 476 */
			/* ???? */
			
			/* j不断变大，整体的值不断变小 */
			
			lcd_buf[800*(h-1-j)+i] = color;
		}
	}
	
	/* b 将颜色数据显示开发板屏幕上 */
	write(lcd_fd, lcd_buf, 800*480*4);
	
	/* 3，关闭文件 */
	
	/* a 关闭图片文件：1.bmp */
	close(bmp_fd);
	/* b 关闭lcd设备文件 */
	close(lcd_fd);
}

int main(void)
{
	show_bmp("IMG00000.bmp");
	
	//show_bmp("1.bmp", 0, 0, 800, 480);
	
	/* int x = 0, y = 0;
	 * int w = 800, h = 480;
	 */
	
	usleep(30000);
	show_bmp("IMG00001.bmp");
	usleep(30000);

	return 0;
}