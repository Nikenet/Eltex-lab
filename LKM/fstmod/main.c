#include <linux/module.h>

/* License type*/
MODULE_LICENSE("GPL");

/* Init-func */
int mod_init(void){
	printk(KERN_INFO "Module loaded\n");
	return 0;
}

/* Cleanup-func */
void mod_cleanup(void){
	printk(KERN_INFO "Module unloaded\n");
	return;
}

/* Kernel is informed the name of func, called at load/unload mod */
module_init(mod_init);
module_exit(mod_cleanup);