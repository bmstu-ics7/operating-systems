#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/time.h>

#define wfs_MAGIC_NUMBER 0x13131313

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Stepanov");
MODULE_DESCRIPTION("BMSTU operating systems VFS");

static struct wfs_inode
{
     int i_mode;
     unsigned long i_ino;
} wfs_inode;

static struct inode *wfs_make_inode(struct super_block *sb, int mode)
{
    struct inode *ret = new_inode(sb);

    if (ret)
    {
        inode_init_owner(ret, NULL, mode);
        ret->i_size = PAGE_SIZE;
        ret->i_atime = ret->i_mtime = ret->i_ctime = current_time(ret);
        ret->i_private = &wfs_inode;
    }

    return ret;
}

static void wfs_put_super(struct super_block * sb)
{
    printk(KERN_DEBUG "wfs super block destroyed!\n" ) ;
}

static struct super_operations const wfs_super_ops = {
    .put_super = wfs_put_super,
    .statfs = simple_statfs,
    .drop_inode = generic_delete_inode,
};

static int wfs_fill_sb(struct super_block *sb, void *data, int silent)
{
    struct inode* root = NULL;

    sb->s_blocksize = PAGE_SIZE;
    sb->s_blocksize_bits = PAGE_SHIFT;
    sb->s_magic = wfs_MAGIC_NUMBER;
    sb->s_op = &wfs_super_ops;

    root = wfs_make_inode(sb, S_IFDIR | 0755);
    if (!root)
    {
        printk (KERN_ERR "wfs inode allocation failed !\n");
        return -ENOMEM;
    }

    root->i_op   = &simple_dir_inode_operations;
    root->i_fop = &simple_dir_operations;

    sb->s_root = d_make_root(root);
    if (!sb->s_root)
    {
        printk(KERN_ERR "wfs root creation failed !\n");
        iput(root);
        return -ENOMEM;
    }

    return 0;
}

static struct dentry* wfs_mount(struct file_system_type *type, int flags, char const *dev, void *data)
{
    struct dentry* const entry = mount_bdev(type, flags, dev, data, wfs_fill_sb);

    if (IS_ERR(entry))
        printk(KERN_ERR "wfs mounting failed!\n");
    else
        printk(KERN_DEBUG "wfs mounted!\n");

    return entry;
}

static struct file_system_type wfs_type = {
    .owner = THIS_MODULE,
    .name = "wfs",
    .mount = wfs_mount,
    .kill_sb = kill_block_super,
};

static int __init wfs_init(void)
{
    int ret = register_filesystem(& wfs_type);

    if(ret != 0)
    {
        printk(KERN_ERR "wfs_MODULE cannot register filesystem!\n");
        return ret;
    }

    printk(KERN_DEBUG "wfs_MODULE loaded !\n"); return 0;
}

static void __exit wfs_exit(void)
{
    int ret = unregister_filesystem(&wfs_type);

    if (ret != 0)
        printk(KERN_ERR "wfs_MODULE cannot unregister filesystem !\n");

    printk(KERN_DEBUG "wfs_MODULE unloaded !\n");
}

module_init(wfs_init);
module_exit(wfs_exit);
