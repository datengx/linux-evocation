#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/tty.h>
#include <linux/user.h>

// TODO WGJA syscall_trace 
extern "C" int syscall_trace(void)
{
	printk("TODO: syscall_trace\n");
	return -ENOSYS;
}

// TODO WGJA sys_ptrace 
extern "C" int sys_ptrace(void)
{
	printk("TODO: sys_ptrace\n");
	return -ENOSYS;
}

// TODO WGJA sys_socketcall 
extern "C" int sys_socketcall(void)
{
	printk("TODO: sys_socketcall\n");
	return -ENOSYS;
}

// TODO WGJA sys_ipc 
extern "C" int sys_ipc(void)
{
	printk("TODO: sys_ipc\n");
	return -ENOSYS;
}

// TODO WGJA sys_modify_ldt 
extern "C" int sys_modify_ldt(void)
{
	printk("TODO: sys_modify_ldt\n");
	return -ENOSYS;
}

// TODO WGJA move sound_mem_init to real thing
void sound_mem_init(void)
{
}

// TODO WGJA pty_open
int pty_open(struct tty_struct *tty, struct file * filp)
{
	printk("// TODO WGJA pty_open\n");
	tty->write = con_write;
	return 0;
}

// TODO WGJA math_emulate
extern "C" void math_emulate(long arg)
{
	printk("TODO WGJA math_emulate\n");
}

// TODO WGJA sock_fcntl
int sock_fcntl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("// TODO WGJA sock_fcntl\n");
	return(-EINVAL);
}

// TODO WGJA lp_init
long lp_init(long mem_start)
{
	printk("TODO WGJA lp_init\n");
	return mem_start;
}

// TODO WGJA mouse_init
long mouse_init(unsigned long mem_start)
{
	printk("TODO WGJA mouse_init\n");
	return mem_start;
}

// TODO WGJA soundcard_init
long soundcard_init(long mem_start)
{
	printk("TODO WGJA soundcard_init\n");
	return mem_start;
}
