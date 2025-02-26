一，文件操作流程

	内核提供函数接口：open，close，read，write

	/* 包含头文件 */
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>

	/* 1,打开瓶盖（打开文件） */

	/* 函数原型 ：让开发者更深入了解接口 */
	int open(const char *pathname, int flags);
	
	有两个参数，一个返回值
	const char *pathname：即将要打开的文件名字（路径 文件名字）
	int flags：
	
	权限标志：
	
	常用标志：
	O_RDONLY：只读
	O_WRONLY：只写
	O_RDWR：读写
	
	返回值：返回一个整形数据int
	成功返回文件的别名（文件描述符）
	失败则返回-1
	
	eg :
	
	int txt_fd = open("笔记.txt", O_RDWR);

	if (txt_fd == -1) {
		printf("open txt file failed!\n");
		return -1;
	}


	/* 2，喝水、倒水（数据处理：写入，读取） */

	ssize_t read(int fd, void *buf, size_t count);
	ssize_t write(int fd, const void *buf, size_t count);

	3个参数，一个返回值
	
	int fd : 已经打开的文件别名
	void *buf/const void *buf : 缓冲区，临时容器（将文件的内容读取放置在buf中、将buf中的数据写入到文件中）
	size_t count : 理想上读取、写入的数据大小 
	
	返回值：返回实际读取、写入的大小

	实际大小 <= 理想大小
	
	实际大小 > 0 读取或写入正常
 	实际大小 < 0 读取或写入异常
	实际大小 = 0 结束
	
	eg :
	
	/* 读取 1024 字节*/
	char buf[1024];
	
	read(txt_fd, buf, 1024);
	
	printf("%s\n", buf);

	/* 3，盖上瓶盖（关闭文件） */

	int close(int fd);
	
	int fd : 已经打开的即将要关闭的文件别名指定
	
	eg :
	
	close(txt_fd);
	
二，lcd设备操作

	1，lcd设备特性
	
	（1）硬件特性
	宽：800
	高：480
	
	尺寸、像素点，分辨率：800*480
	
	（2）位深度（一个像素点所占用字节大小）：32
	
	1字节 = 8 位
	32位  = 4 字节 
	
	屏幕大小：宽*高*位深度/8
	
	int buf[800*480];
	
	（3）属性组成（一个像素点的属性组成）
	
	透明度，红，绿，蓝
	
	1字节
	
	十进制：0~255
	
	十六进制: 0~0xff
	
	   透明度，红，绿，蓝
	0x ff      ff  ff  ff
	
	蓝色：0x 00 00 00 ff   0xff
	红色：0x 00 ff 00 00   0xff0000
	绿色：0x 00 00 ff 00
	
	int color = 0xff;
	
	int argb_buf[800*480];
	
	argb_buf[0] = 0xff;
	argb_buf[1] = 0xff;
	argb_buf[2] = 0xff;
	argb_buf[...] = 0xff;
	argb_buf[800*480] = 0xff;
	
	int i, j;
	
	/* 5000 = 800*6+200 */
	/* 3000 = 800*3+600 */
	
	/* 有多少行 */
	for (j = 0; j < 480; j++) {
		/* 一行的数据有多少 */
		for (i = 0; i < 800; i++) {
			argb_buf[800*j+i] = color;
		}
	}
	
	2，使用文件操作进行控制设备
	
	lcd 设备文件 "/dev/fb0"
	
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


	练习：


	1，全屏一种颜色
	2，圆，彩虹
	
	原点（x, y）
	半径（r）

	(x-i)*(x-i)+(y-j)*(y-j) <= (r*r)
	
	(x-i)*(x-i)+(y-j)*(y-j) <= (100*100) && (x-i)*(x-i)+(y-j)*(y-j) <= (150*150)
	
三，图片显示

	bmp图片格式存储颜色数据最为完整

	bmp特性
	
	（1）文件头 文件信息 （宽，高，像素点，位深度，。。。）54字节
	
	（2）位深度：24
	
	lcd ：32 4 bmp ：24 3 红，绿，蓝
	
	bmp图片颜色数据大小：宽*高*3 
	图片大小：宽*高*位深度/8+文件头的大小
	
	（3）存储方式：从左往右，从下往上
	
	操作流程：（将图片颜色数据显示在开发板的屏幕上）
	
	/* 1，打开文件 */
	
	/* a 打开图片文件：1.bmp */
	
	int bmp_fd = open("1.bmp", O_RDWR);

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
	
	char rgb_buf[800*480*3];
	int lcd_buf[800*480];
	
	/* a 将图片文件里面颜色数据读取出来 */
	read(bmp_fd, rgb_buf, 800*480*3);
	/* b 将颜色数据显示开发板屏幕上 */
	write(lcd_fd, lcd_buf, 800*480*4);
	
	/* 3，关闭文件 */
	
	/* a 关闭图片文件：1.bmp */
	close(bmp_fd);
	/* b 关闭lcd设备文件 */
	close(lcd_fd);
	
	运行程序之前，找打一张800 480 24 bmp图片
	
	ubutun的终端
	arm-linux-gcc bmp.c -o bmp
	
	开发板的终端
	rx 1.bmp
	rx bmp
	chmod 777 bmp && ./bmp