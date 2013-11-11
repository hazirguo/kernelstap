//#include <linux/kernel.h>   /* We're doing kernel work */
#include <linux/init.h>
#include <linux/module.h>   /* Specifically, a module */
MODULE_LICENSE("GPL");

///* Deal with CONFIG_MODVERSIONS */
//#if CONFIG_MODVERSIONS==1
//#define MODVERSIONS
//#include <linux/modversions.h>
//#endif        
/* For character devices */
#include <linux/fs.h>     /* The character device definitions are here */
#include <asm/uaccess.h>  /* for put_user */

#define DEVICE_NAME "char_dev"

static int device_open(struct inode *inode, struct file *file)
{
//  static int counter = 0;
#ifdef DEBUG
  printk ("device_open(%p,%p)\n", inode, file);
#endif
  printk("Device: %d.%d\n", 
	 inode->i_rdev >> 8, inode->i_rdev & 0xFF);
  //MOD_INC_USE_COUNT;
  return 0;
}

static int device_release(struct inode *inode, 
			   struct file *file)
{
#ifdef DEBUG
  printk ("device_release(%p,%p)\n", inode, file);
#endif
  //MOD_DEC_USE_COUNT;
  return 0;
}

static ssize_t device_read(struct file *file,
    char *buffer,    /* The buffer to fill with data */
    int length,   /* The length of the buffer */
    loff_t *offset)  /* Our offset in the file */
{
  int i;
  printk("<0>""read char_dev\n");
  for(i = 0; i < length; i++)
  {
 	 put_user('a',buffer++);
  }
  return (ssize_t)length;
}

static ssize_t device_write(struct file *file,
    const char *buffer,    /* The buffer */
    size_t length,   /* The length of the buffer */
    loff_t *offset)  /* Our offset in the file */
{
  return (ssize_t)-EINVAL;
}

static int Major;
struct file_operations Fops = {
.owner=THIS_MODULE,
.open=device_open,
.release=device_release,
.read=device_read,
.write=device_write
};

static int chardev_init()
{
   Major =  register_chrdev(0, DEVICE_NAME, &Fops);
  if (Major < 0) 
  {
    printk ("device failed with %d\n", Major);
    return Major;
  }
  printk ("mknod %s c %d <minor>\n", DEVICE_NAME, Major);
  return 0;
}
static void chardev_exit()
{
	printk("<1>""remove chardev module\n");
	unregister_chrdev(Major, DEVICE_NAME);
}  

module_init(chardev_init);
module_exit(chardev_exit);
