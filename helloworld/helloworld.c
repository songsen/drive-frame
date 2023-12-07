/**
 * @file helloworld.c
 * @author your name (you@domain.com)
 * @brief
 插入/卸载驱动模块，由于各发行版控制台打印级别设置不同，
可能在一些发行版上看不到提示信息打印，可以输入 dmesg 命令查看或者另打开一个终端，
输入 tail -f /var/log/messages 命令，实时查看提示信息。 
 * @version 0.1
 * @date 2023-12-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <linux/module.h>
#include <linux/init.h>
static int __init hello_init(void)
{
	printk("Hello world!\n");
	return 0;
}
static void __exit hello_exit(void)
{
	printk("world bye!\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");