#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

static struct file_system_type toast_type = {
	.owner = THIS_MODULE,
	.name = "ToastFS",
	.mount = toast_mnt,
	.kill_sb = toast_kill_sb,
	.fs_flags = FS_REQUIRES_DEV, //Needs disk for operation

};

/*
Comments:
Mount_bdev initializes the superblock. Dentry contains the root of our system which toast_fill_sb creates
*/
static struct dentry *toast_mnt(struct file_system_type type,
									int flags, char const *dev,
									void *data)
{
	struct dentry *entry = mount_bdev(type, flags, dev, data,
										toast_fill_super); 

	if(IS_ERR(entry)) 
		pr_err("Mounting ToastFS failed");
	else 
		printk("ToastFS Mounted Successfully")

	return entry;	
}

static int toast_fill_super(struct super_block *sb, void *data, int silent) 
{
	/*Fill SuperBlock */	
}

static int __init toast_init(void) 
{

	printk("ToastFS Loaded\n");
	return 0;
}

static void __exit toast_exit(void)
{
	printk("Goodbye. ToastFS Module unloaded\n");
}



module_init(toast_init);
module_exit(toast_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Wir3dToast");