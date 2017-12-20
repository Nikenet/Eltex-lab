#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Nikita Mikhaylov <Nikenet1@gmail.com>");
MODULE_DESCRIPTION("Reverse string kernel module");
MODULE_SUPPORTED_DEVICE( "/dev/buffer" );

#define DEVICE_NAME "reverse"
#define BUF_LEN 100

int init_module(void);
void cleanup_module(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static int Major;
static int Device_Open = 0;
static char msg[BUF_LEN];
static char *msg_Ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/* Init module func */
int init_module(void){

	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0){
		printk("Registering the device failed with %d\n", Major);
		return Major;
	}

	printk("Module is loaded!\n" );
	printk("Please, create a dev file with 'sudo mknod /dev/buffer c %d 0'.\n", Major);

	return 0;
}

/* Cleanup module func */
void cleanup_module(void){

	unregister_chrdev(Major, DEVICE_NAME);

	if (Major < 0){

		printk("Error in unregister /dev/buffer\n");
		return;

	} else {

		unregister_chrdev(Major, DEVICE_NAME);
	}
}


/* Used when we call the devfile */
static int device_open(struct inode *inode, struct file *file){

	if (Device_Open)
		printk("Trying to open mpdole /dev/buffer\n");

	try_module_get(THIS_MODULE);

	return 0;
}

/* Used when we close devfile */
static int device_release(struct inode *inode, struct file *file){

	module_put(THIS_MODULE);
	return 0;
}

/* Used wen the prosess call already opened file*/
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t * offset){

	int bytes_read = 0;

	if (*msg_Ptr == 0)
		return 0;

	while (length && *msg_Ptr) {
		put_user(*(msg_Ptr++), buffer++);
		length--;
		bytes_read++;
	}

	printk("Trying read file\n");

	return bytes_read;
}

/* Used when we try wryte someone to /dev/reverse */
static ssize_t device_write(struct file *filp, const char *buffer, size_t len, loff_t * off){

	int size_of_message = 0;
	int i = 0;
	char tmp[1];

	snprintf(msg, len, "%s", buffer);
	size_of_message = strlen(msg);

	msg_Ptr = msg;

	printk("Received %d characters from the user\n", size_of_message);

	return len;

}

