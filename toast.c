#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#include "toast.h"

int toast_readdir(struct file *filp, void *dirent, filldir_t filldir) 
{
	return 0;
}

/*
Comments:
Allows us to find names in directories.
*/
static dentry *toast_lookup_inode(struct inode *parent_inode,
									struct dentry *child_dentry,
									unsigned int flags)
{
	return NULL;
}


struct file_operations toast_dir_ops = {
	.owner = THIS_MODULE,
	.readdir = toast_readdir
};

struct inode_operations toast_inode_ops = {
	.lookup = toast_lookup_inode
}; 

static int toast_fill_super(struct super_block *sb, void *data, int silent) 
{
	struct inode *root;

	sb->s_magic = TOAST_MAGIC_NUM;

	root = new_inode(sb);

	if(!root) {
		pr_err("Inode Allocation Failed");
		return -ENOMEM;
	}

	root->i_ino = get_next_ino(); //Get valid inode 
	root->i_sb = sb;
	root->i_op = &toast_inode_ops;
	root->i_fop = &toast_dir_ops;
	root->i_atime = root->i_mtime = root->i_ctime = CURRENT_TIME;
	inode_init_owner(root,NULL,S_IFDIR);

	sb->s_root = d_make_root(root);

	if(!sb->s_root) {
		pr_err("Root Dir Creation Failed");
		return -ENOMEM;
	}

	return 0;
}

/*
Comments:
Mount_bdev initializes the superblock. Dentry contains the root of our system which toast_fill_sb creates
*/
static struct dentry *toast_mnt(struct file_system_type *type,
									int flags, char const *dev,
									void *data)
{
	struct dentry *entry = mount_bdev(type, flags, dev, data,
										toast_fill_super); 

	if(IS_ERR(entry)) 
		pr_err("Mounting ToastFS failed");
	else 
		printk("ToastFS Mounted Successfully");

	return entry;	
}


static void toast_kill_sb(struct super_block *sb)
{

}

struct file_system_type toast_type = {
	.owner = THIS_MODULE,
	.name = "ToastFS",
	.mount = toast_mnt,
	.kill_sb = toast_kill_sb,
	.fs_flags = FS_REQUIRES_DEV //Needs disk for operation
};


static int __init toast_init(void) 
{

	int regis = register_filesystem(&toast_type);
	if(!regis) 
		printk("ToastFS Loaded\n");
	else
		printk("ToastFS could not be registered. %d", regis);	

	return 0;
}

static void __exit toast_exit(void)
{
	int regis = unregister_filesystem(&toast_type); 
	if(!regis) 
		printk("Goodbye. ToastFS Module unloaded\n");
	else
		printk("Cannot unregister ToastFS. %d", regis);
}



module_init(toast_init);
module_exit(toast_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Wir3dToast");
