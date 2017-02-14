 #ifndef _LINUX_MM_H
 #define _LINUX_MM_H
 
#include <linux/page.h>
#include <linux/fs.h>
#include <linux/kernel.h>

// TODO WGJA WIP: /*
// TODO WGJA WIP:  * Linux kernel virtual memory manager primitives.
// TODO WGJA WIP:  * The idea being to have a "virtual" mm in the same way
// TODO WGJA WIP:  * we have a virtual fs - giving a cleaner interface to the
// TODO WGJA WIP:  * mm details, and allowing different kinds of memory mappings
// TODO WGJA WIP:  * (from shared memory to executable loading to arbitrary
// TODO WGJA WIP:  * mmap() functions).
// TODO WGJA WIP:  */
// TODO WGJA WIP: 
// TODO WGJA WIP: /*
// TODO WGJA WIP:  * This struct defines a memory VMM memory area. There is one of these
// TODO WGJA WIP:  * per VM-area/task.  A VM area is any part of the process virtual memory
// TODO WGJA WIP:  * space that has a special rule for the page-fault handlers (ie a shared
// TODO WGJA WIP:  * library, the executable area etc).
// TODO WGJA WIP:  */
// TODO WGJA WIP: struct vm_area_struct {
// TODO WGJA WIP: 	struct task_struct * vm_task;		/* VM area parameters */
// TODO WGJA WIP: 	unsigned long vm_start;
// TODO WGJA WIP: 	unsigned long vm_end;
// TODO WGJA WIP: 	unsigned short vm_page_prot;
// TODO WGJA WIP: 	struct vm_area_struct * vm_next;	/* linked list */
// TODO WGJA WIP: 	struct vm_area_struct * vm_share;	/* linked list */
// TODO WGJA WIP: 	struct inode * vm_inode;
// TODO WGJA WIP: 	unsigned long vm_offset;
// TODO WGJA WIP: 	struct vm_operations_struct * vm_ops;
// TODO WGJA WIP: };
// TODO WGJA WIP: 
// TODO WGJA WIP: /*
// TODO WGJA WIP:  * These are the virtual MM functions - opening of an area, closing it (needed to
// TODO WGJA WIP:  * keep files on disk up-to-date etc), pointer to the functions called when a
// TODO WGJA WIP:  * no-page or a wp-page exception occurs, and the function which decides on sharing
// TODO WGJA WIP:  * of pages between different processes.
// TODO WGJA WIP:  */
// TODO WGJA WIP: struct vm_operations_struct {
// TODO WGJA WIP: 	void (*open)(struct vm_area_struct * area);
// TODO WGJA WIP: 	void (*close)(struct vm_area_struct * area);
// TODO WGJA WIP: 	void (*nopage)(int error_code,
// TODO WGJA WIP: 		       struct vm_area_struct * area, unsigned long address);
// TODO WGJA WIP: 	void (*wppage)(struct vm_area_struct * area, unsigned long address);
// TODO WGJA WIP: 	int (*share)(struct vm_area_struct * from, struct vm_area_struct * to, unsigned long address);
// TODO WGJA WIP: };
// TODO WGJA WIP: 
// TODO WGJA WIP: extern unsigned long __bad_page(void);
// TODO WGJA WIP: extern unsigned long __bad_pagetable(void);
// TODO WGJA WIP: extern unsigned long __zero_page(void);
// TODO WGJA WIP: 
// TODO WGJA WIP: #define BAD_PAGETABLE __bad_pagetable()
// TODO WGJA WIP: #define BAD_PAGE __bad_page()
// TODO WGJA WIP: #define ZERO_PAGE __zero_page()
// TODO WGJA WIP: 
// TODO WGJA WIP: extern volatile short free_page_ptr; /* used by malloc and tcp/ip. */
// TODO WGJA WIP: 
// TODO WGJA WIP: extern int nr_swap_pages;
// TODO WGJA WIP: extern int nr_free_pages;
// TODO WGJA WIP: extern unsigned long free_page_list;
// TODO WGJA WIP: extern int nr_secondary_pages;
// TODO WGJA WIP: extern unsigned long secondary_page_list;
// TODO WGJA WIP: 
// TODO WGJA WIP: #define MAX_SECONDARY_PAGES 10
// TODO WGJA WIP: 
// TODO WGJA WIP: /*
// TODO WGJA WIP:  * This is timing-critical - most of the time in getting a new page
// TODO WGJA WIP:  * goes to clearing the page. If you want a page without the clearing
// TODO WGJA WIP:  * overhead, just use __get_free_page() directly..
// TODO WGJA WIP:  */
// TODO WGJA WIP: extern unsigned long __get_free_page(int priority);
// TODO WGJA WIP: extern inline unsigned long get_free_page(int priority)
// TODO WGJA WIP: {
// TODO WGJA WIP: 	unsigned long page;
// TODO WGJA WIP: 
// TODO WGJA WIP: 	page = __get_free_page(priority);
// TODO WGJA WIP: 	if (page)
// TODO WGJA WIP: 		__asm__ __volatile__("rep ; stosl"
// TODO WGJA WIP: 			: /* no outputs */ \
// TODO WGJA WIP: 			:"a" (0),"c" (1024),"D" (page)
// TODO WGJA WIP: 			:"di","cx");
// TODO WGJA WIP: 	return page;
// TODO WGJA WIP: }
// TODO WGJA WIP: 
// TODO WGJA WIP: /* mmap.c */
// TODO WGJA WIP: 
// TODO WGJA WIP: /* memory.c */
// TODO WGJA WIP: 
// TODO WGJA WIP: extern void free_page(unsigned long addr);
// TODO WGJA WIP: extern unsigned long put_dirty_page(struct task_struct * tsk,unsigned long page,
// TODO WGJA WIP: 	unsigned long address);
// TODO WGJA WIP: extern void free_page_tables(struct task_struct * tsk);
// TODO WGJA WIP: extern void clear_page_tables(struct task_struct * tsk);
// TODO WGJA WIP: extern int copy_page_tables(struct task_struct * to);
// TODO WGJA WIP: extern int clone_page_tables(struct task_struct * to);
// TODO WGJA WIP: extern int unmap_page_range(unsigned long from, unsigned long size);
// TODO WGJA WIP: extern int remap_page_range(unsigned long from, unsigned long to, unsigned long size, int mask);
// TODO WGJA WIP: extern int zeromap_page_range(unsigned long from, unsigned long size, int mask);
// TODO WGJA WIP: 
// TODO WGJA WIP: extern void do_wp_page(unsigned long error_code, unsigned long address,
// TODO WGJA WIP: 	struct task_struct *tsk, unsigned long user_esp);
// TODO WGJA WIP: extern void do_no_page(unsigned long error_code, unsigned long address,
// TODO WGJA WIP: 	struct task_struct *tsk, unsigned long user_esp);

extern unsigned long paging_init(unsigned long start_mem, unsigned long end_mem);
// TODO WGJA WIP: extern void mem_init(unsigned long low_start_mem,
// TODO WGJA WIP: 		     unsigned long start_mem, unsigned long end_mem);
// TODO WGJA WIP: extern void show_mem(void);
// TODO WGJA WIP: extern void oom(struct task_struct * task);
// TODO WGJA WIP: extern void si_meminfo(struct sysinfo * val);
// TODO WGJA WIP: 
// TODO WGJA WIP: /* swap.c */
// TODO WGJA WIP: 
// TODO WGJA WIP: extern void swap_free(unsigned long page_nr);
// TODO WGJA WIP: extern unsigned long swap_duplicate(unsigned long page_nr);
// TODO WGJA WIP: extern void swap_in(unsigned long *table_ptr);
// TODO WGJA WIP: extern void si_swapinfo(struct sysinfo * val);
// TODO WGJA WIP: extern void rw_swap_page(int rw, unsigned long nr, char * buf);
// TODO WGJA WIP: 
// TODO WGJA WIP: /* mmap.c */
// TODO WGJA WIP: extern int do_mmap(struct file * file, unsigned long addr, unsigned long len,
// TODO WGJA WIP: 	unsigned long prot, unsigned long flags, unsigned long off);
// TODO WGJA WIP: 
// TODO WGJA WIP: #define read_swap_page(nr,buf) \
// TODO WGJA WIP: 	rw_swap_page(READ,(nr),(buf))
// TODO WGJA WIP: #define write_swap_page(nr,buf) \
// TODO WGJA WIP: 	rw_swap_page(WRITE,(nr),(buf))

#define invalidate() \
__asm__ __volatile__("movl %%cr3,%%eax\n\tmovl %%eax,%%cr3": : :"ax")

// TODO WGJA WIP: extern unsigned long high_memory;
// TODO WGJA WIP: 
// TODO WGJA WIP: #define MAP_NR(addr) ((addr) >> PAGE_SHIFT)
// TODO WGJA WIP: #define MAP_PAGE_RESERVED (1<<15)
// TODO WGJA WIP: 
// TODO WGJA WIP: extern unsigned short * mem_map;

#define PAGE_PRESENT	0x001
#define PAGE_RW		0x002
#define PAGE_USER	0x004
#define PAGE_PWT	0x008	/* 486 only - not used currently */
#define PAGE_PCD	0x010	/* 486 only - not used currently */
#define PAGE_ACCESSED	0x020
#define PAGE_DIRTY	0x040
#define PAGE_COW	0x200	/* implemented in software (one of the AVL bits) */

#define PAGE_PRIVATE	(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED | PAGE_COW)
#define PAGE_SHARED	(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED)
#define PAGE_COPY	(PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED | PAGE_COW)
#define PAGE_READONLY	(PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED)
#define PAGE_TABLE	(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED)

// TODO WGJA WIP: #define GFP_BUFFER	0x00
// TODO WGJA WIP: #define GFP_ATOMIC	0x01
// TODO WGJA WIP: #define GFP_USER	0x02
// TODO WGJA WIP: #define GFP_KERNEL	0x03
// TODO WGJA WIP: 
// TODO WGJA WIP: 
// TODO WGJA WIP: /* vm_ops not present page codes */
// TODO WGJA WIP: #define SHM_SWP_TYPE 0x41        
// TODO WGJA WIP: extern void shm_no_page (ulong *);

#endif
