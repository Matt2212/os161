#include <lib.h>
#include <types.h>
#include <machine/current.h>
#include <thread.h>
#include <proc.h>
#include <addrspace.h>

void sys__exit(int exit_code){
	as_destroy(proc_getas());
	if(curproc) curproc->status = exit_code;
	thread_exit();
	panic("thread_exit returned. First reaction: SHOCK!\n");
}
