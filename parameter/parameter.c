/**
 * @file parameter.c
 * @author your name (you@domain.com)
 * @brief 程序清单 2.5 可接受参数的内核模块
 在加载模块的时候指定参数的值：
# insmod hellop.ko whom="MASTER" num=5
MASTER, I get 5
 * @version 0.1
 * @date 2023-12-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <linux/module.h>
#include <linux/init.h>

static int num = 3;
static char *whom = "master";

module_param(num, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

static int __init hello_init(void)
{
	printk(KERN_INFO "%s, I get %d\n", whom, num);
	return 0;
}

static void __exit hello_exit(void)
{
	printk("I'll be leaving, bye!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");