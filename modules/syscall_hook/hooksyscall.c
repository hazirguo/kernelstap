#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define __NR_mysyscall		223
#define __Syscall_table		0xc15b0000

void **sys_call_table;		//系统调用表起始地址
void *origin_syscall;


asmlinkage long mysyscall(void)
{
	printk("in my own syscall!\n");
	return 100;
}


void clear_cr0(void)
{
	asm volatile("mov %cr0, %eax;"
				"and $0xfffeffff, %eax;"
				"mov %eax, %cr0");
}

void setback_cr0(void)
{
	asm volatile("mov %cr0, %eax;"
				"or $0x00010000, %eax;"
				"mov %eax, %cr0");
}

void setup_syscall(void)
{
	origin_syscall = sys_call_table[__NR_mysyscall];
	sys_call_table[__NR_mysyscall] = mysyscall;
}

void uninstall_syscall(void)
{
	sys_call_table[__NR_mysyscall] = origin_syscall;
}

int __init init_mysyscall(void)
{
	sys_call_table = (void *)__Syscall_table;
	clear_cr0();
	setup_syscall();
	setback_cr0();
	printk("-------------insert a module！-----------\n");
	return 0;
}

void __exit exit_mysyscall(void)
{
	clear_cr0();
	uninstall_syscall();
	setback_cr0();
}


module_init(init_mysyscall);
module_exit(exit_mysyscall);

MODULE_LICENSE("GPL");
