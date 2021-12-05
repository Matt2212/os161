#include <swapfile.h>
#include <kern/fcntl.h>
#include <vfs.h>
#include <lib.h>
#include <types.h>
#include <bitmap.h>
#include <vnode.h>
#include <errno.h>
#include <uio.h>

swap_file* swap_create() {
    swap_file* ret = kmalloc(sizeof(swap_file));
    if (ret == NULL) {
        panic("OUT OF MEMORY");
        return NULL;
    }
    ret->bitmap = bitmap_create(SWAP_MAX);
    if (ret->bitmap == NULL) {
        panic("OUT OF MEMORY");
        kfree(ret);
        return NULL;
    }
    vfs_open("SWAP_FILE", O_CREAT | O_RDWR, 0,&ret->file);
}

// FORSE NON VA BENE VADDR_T CONTROLLA SE NEL BUFFER DEVI METTEER UN INDIRIZZO FISICO O LOGICO DEL KERNEL (PROBABILMENTE LA SECONDA)

void swap_get(vaddr_t address, int index, swap_file* swap) {
    struct iovec iov;
	struct uio ku;
    bitmap_unmark(swap->bitmap, index);
    uio_kinit(&iov, &ku, address, 4096, index*4096, UIO_READ);
    VOP_READ(swap->file, &ku);
}

int swap_set(vaddr_t address, swap_file* swap) {
    struct iovec iov;
	struct uio ku;
    int index;
    if (bitmap_alloc(swap->bitmap, &index) == ENOSPC)
        panic("OUT OF MEMORY");
    bitmap_mark(swap->bitmap, index);
    uio_kinit(&iov, &ku, address, 4096, index*4096, UIO_WRITE);
    VOP_READ(swap->file, &ku);
}