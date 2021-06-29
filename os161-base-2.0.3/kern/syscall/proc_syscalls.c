#include <types.h>
#include <lib.h>
#include <current.h>
#include <thread.h>
#include <proc.h>
#include <addrspace.h>
#include <syscall.h>
void sys__exit(int exit_code){
	as_destroy(proc_getas());
	if(curproc) {
		curproc->status = exit_code;
#if OPT_WAIT_PROC
		spinlock_acquire(&curproc->p_lock);
		wchan_wakeall(curproc->wchan, &curproc->p_lock);
		spinlock_release(&curproc->p_lock);
#endif
	}
	thread_exit();
	panic("thread_exit returned. First reaction: SHOCK!\n");
}
