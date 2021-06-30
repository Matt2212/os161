#include <types.h>
#include <lib.h>
#include <current.h>
#include <thread.h>
#include <proc.h>
#include <addrspace.h>
#include <syscall.h>
#if OPT_WAIT_PROC
#include <synch.h>
#endif
void sys__exit(int exit_code){

	#if !OPT_WAIT_PROC
		as_destroy(proc_getas());
	#endif
	
	if(curproc) {
		curproc->status = exit_code;
#if OPT_WAIT_PROC
		struct proc* p = curproc;
		proc_remthread(curthread);
		lock_acquire(p->lock);
		curthread->t_exited = true;
		cv_broadcast(p->cv, p->lock);
		lock_release(p->lock);
#endif
		
	}
	thread_exit();
	panic("thread_exit returned. First reaction: SHOCK!\n");
}


#if OPT_WAIT_PROC
pid_t sys_waitpid(pid_t pid, int *status, int flags) {
	return pid;
}
#endif