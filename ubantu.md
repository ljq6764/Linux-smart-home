#ubuntu use
1.ubuntu的使用

	防止崩溃：
	版本回退：设置快照（时光机）

	快照管理器 ---》快照拍摄 ---》如有需要则转到原先的快照

	1，终端 terminal

	Windows ：dos （窗口 r cmd）
	Linux ：Terminal （alt ctrl t）

	lock to ???

	命令行提示符

	gec@ubuntu:~$ 

	gec 用户名

	ubuntu 主机名

	~ 当前所在位置（用户主文件夹：C:\Users\用户名\Desktop，家目录：/home/用户名）

	$ 用户标识 （$ 普通用户 # 超级管理员）

	@ : 间隔符 

	2，文本编辑器

	Linux ：gedit
	
	file ---> pre
	
	Windows：Notepad++
	
	3，文件资源管理器
	
	Windows ： 窗口 e
	Linux：Files (nautilus)
	
二，Linux基础命令

	位置显示和跳转

	1，pwd

	查看当前所在位置

	2，（ls 路径）
	
	缺省状态下，显示当前所在位置下的文件

	-l   以列表的形式列出文件
	-a 显示全部文件（以.开头的）

	3，（cd 路径）
	
	进入，跳转，切换 路径（位置）

	文件或文件夹操作

	4，（mkdir ... 名字）
	
	创建新的空的文件夹（目录）

	5，（rmdir ... 名字）

	删除已经存在空的文件夹（目录）
	
	6，（touch ... 名字）

	创建文件或更新文件所属

	7，（rm ... 名字）

	删除文件或目录

	-rf 强制删除并没有提示
	
	8，（mv 即将要操作的名字 ... 目的地）
	
	移动或重名文件和目录

	区别：目的地和即将要操作的位置是否一致

	9，（cp 即将要操作的名字 ... 目的地）

	复制文件或目录

	10，（cat 文件名字）

	查看文件内容
	
	. 当前位置 .. 上一级位置 - 记录上一次的位置


	练习：

	打开终端，进入桌面，创建三个文件夹，名字自拟

	进入第一个文件夹，创建三个文件，往文件输入内容

	将第一个文件进行重名

	将第二个文件进行移动到第二个文件夹中
	
	将第三个文件复制到第三个文件夹中

	返回上一级文件夹，删除所有文件（文件夹和文件）
	
三，开发板的使用

	盒子：开发板，电源适配器，串口线，usb转串口线，网线，安卓线，泡沫
	
	gec6818:http://www.gec-lab.com/arm/show/72.html
	
	该平台搭载三星Cortex-A53系列高性能八核处理器S5P6818，最高主频高达1.4GHz，
	
	内存 标配1GB，可定制2GB
	
	存储器  4GB/8GB/16GB/32GB emmc可选，标配8GB
	
	1，将电源适配器接在开发板上的电源接口，通电，打上开关
	
	正常：
	
	粤嵌logo
	登陆界面
	系统心跳灯
	
	异常：
	黑屏
	触摸屏不可用
	心跳灯不亮，不闪动
	
	2，将usb转串口线接在串口线上，usb接在电脑上，串口一端接在开发板的调试串口上（串口1）
	
	在虚拟机当中选择串口线连接主机
	
	3，查看端口 (前置条件：有安装usb转串口线驱动)
	
	窗口 i 打开设置 搜索 设备管理器
	
	端口（com和lpt）
	
	usb to serial com ???
	ch340 com ???
	
	4，打开终端连接工具进行连接开发板
	
	终端连接工具：SecureCRT.rar --> SecureCRT/SecureCRT.exe
	
	文件（F）-》快速连接（Q）
	
	协议：Serial
	端口：com ???
	波特率：115200
	流控不需要设置：勾去掉
	
	5，出现终端
	
	如果lcd屏幕显示的是登陆界面则，需要在终端上按下ctrl c退出此程序
	
	[root@gec6818:/IOT #]
	
	[root@gec6818:/ #]
	
四，开发流程

	1，代码编写
	
	源代码：*.c
	
	/* 包含头文件 */
	#include <stdio.h>
	
	/* 入口函数 */
	int main(void)
	{
		/* 代码块 */
		printf("hello world!\n");
		
		return 0;
	}
	
	头文件：*.h
	
	库文件：*.so *.a
	
	2，生成程序
	
	把源代码放置在ubuntu上 ，右键复制黏贴pauste
	
	右键打开终端 open in terminal
	
	进入桌面
	cd ~/Desktop
	
	生成程序
	
	格式：
	编译器名字 源代码文件名字 -o 应用程序名字
	
	ubuntu : gcc
	arm开发板：arm-linux-gcc
	
	eg ：
	
	arm-linux-gcc hello.c -o hello
	
	3，上传程序
	
	格式：
	rx 要上传的文件名字
	

	eg :
	
	rx hello
	
	按下回车
	
	选择这个程序，将hello程序拖动到开发板的终端上
	
	选择发送xmodem，
	
	100% 0 errors
	
	4，运行程序
	
	赋予权限并运行
	
	chmod 777 hello && ./hello