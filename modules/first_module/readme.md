第一个内核模块,加载内核模块之后打印出"hello world!"字符串.

## 操作内核模块的基本命令 ##

1. **lsmod** ---  列出系统中已经加载的内核模块
2. **insmod** --- 将一个模块插入内核
3. **modinfo** --- 显示模块信息
4. **rmmod** --- 将模块从内核中删除
5. **modprobe** --- 增加或者移除模块

## 写一个简单的内核模块

1. 写模块源代码
2. 创建编译内核模块的 makefile
3. 编译之后插入/移除模块


## 参考资料 ##

1. http://www.linuxchix.org/content/courses/kernel_hacking/lesson8
2. http://www.thegeekstuff.com/2013/07/write-linux-kernel-module/
3. http://www.tldp.org/LDP/lkmpg/2.6/html/x121.html
