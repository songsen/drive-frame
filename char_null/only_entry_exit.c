/**
 * @file only_entry_exit.c
 * @author your name (you@domain.com)
 * @brief 
 将这个驱动编译得到 char_null.ko 模块，可以插入内核，也可从内核中卸载。插入内核
后，可以查看/proc/devices 文件，看设备号的分配情况。
将 major 的值改为 0，使用动态设备号，重新编译驱动，再次插入内核，查看设备号的
分配情况。
 * @version 0.1
 * @date 2023-12-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#define DEVICE_NAME "char_null"
static int major = 232; /* 保存主设备号的全局变量 */
static int __init char_null_init(void)
{
	int ret;

	ret = register_chrdev(major, DEVICE_NAME,
			      (const struct file_operations *)&major); /* 申请设备号和注册 */
	if (major > 0) { /* 静态设备号 */
		if (ret < 0) {
			printk(KERN_INFO " Can't get major number!\n");
			return ret;
		}
	} else { /* 动态设备号 */
		printk(KERN_INFO " ret is %d\n", ret);
		major = ret; /* 保存动态获取到的主设备号 */
	}
	printk(KERN_INFO "%s ok!\n", __func__);
	return ret;
}

static void __exit char_null_exit(void)
{
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_INFO "%s\n", __func__);
}

module_init(char_null_init);
module_exit(char_null_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chenxibing, linux@zlgmcu.com");