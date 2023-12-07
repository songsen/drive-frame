/**
 * @file char_null_udev.c
 * @author your name (you@domain.com)
 * @brief 
 编译代码后得到 char_null_udev.ko 模块，插入系统，将可以在/sys/class 目录下看到
char_null _udev 目录以及其它信息，先看 dev 文件：
# insmod char_null_udev.ko
#cat /sys/class/char_null_udev_class/char_null_udev/dev
232:0
udev 将根据 dev 文件来创建设备节点。
可以看到在 sysfs 中创建的设备节点的主次设备号分别是 232 和 0。再看 uevent 文件：
#cat /sys/class/char_null_udev_class/char_null_udev/uevent
MAJOR=232
 * @version 0.1
 * @date 2023-12-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

static int major = 232; /* 静态设备号方式的默认值 */
static int minor = 0; /* 静态设备号方式的默认值 */
module_param(major, int, S_IRUGO);
module_param(minor, int, S_IRUGO);

struct cdev *char_null_udev; /* cdev 数据结构 */
static dev_t devno; /* 设备编号 */
static struct class *char_null_udev_class;

#define DEVICE_NAME "char_null_udev"

static int __init char_null_udev_init(void)
{
	int ret;

	if (major > 0) { /* 静态设备号 */
		devno = MKDEV(major, minor);
		ret = register_chrdev_region(devno, 1, "char_null_udev");
	} else { /* 动态设备号 */
		ret = alloc_chrdev_region(
			&devno, minor, 1,
			"char_null_udev"); /* 从系统获取主设备号 */
		major = MAJOR(devno);
	}
	if (ret < 0) {
		printk(KERN_ERR "cannot get major %d \n", major);
		return -1;
	}
	char_null_udev = cdev_alloc(); /* 分配 char_null_udev 结构 */
	if (char_null_udev != NULL) {
		cdev_init(char_null_udev,
			  NULL); /* 初始化 char_null_udev 结构 */
		char_null_udev->owner = THIS_MODULE;
		if (cdev_add(char_null_udev, devno, 1) !=
		    0) { /* 增加 char_null_udev 到系统中 */
			printk(KERN_ERR "add cdev error!\n");
			goto error;
		}
	} else {
		printk(KERN_ERR "cdev_alloc error!\n");
		return -1;
	}
	//在/sys/class/下创建 char_null_udev_class 目录
	char_null_udev_class =
		class_create(THIS_MODULE, "char_null_udev_class");
	if (IS_ERR(char_null_udev_class)) {
		printk(KERN_INFO "create class error\n");
		return -1;
	}
	/* 将创建/dev/char_null_udev0 文件 */
	//device_create(char_null_udev_class, NULL, devno, NULL, "char_null_udev" "%d",MINOR(devno));
/* 将创建/dev/char_null_udev 文件 */
    device_create(char_null_udev_class, NULL, devno, NULL, "char_null_udev");

    return 0;

error:
	unregister_chrdev_region(devno, 1); /* 释放已经获得的设备号 */
	return ret;
}

static void __exit char_null_udev_exit(void)
{
	device_destroy(char_null_udev_class, devno);
	class_destroy(char_null_udev_class);
	cdev_del(char_null_udev); /* 移除字符设备 */
	unregister_chrdev_region(devno, 1); /* 释放设备号 */
}

module_init(char_null_udev_init);
module_exit(char_null_udev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chenxibing, linux@zlgmcu.com");