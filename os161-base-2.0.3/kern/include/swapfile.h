
#include <bitmap.h>

#define SWAP_MAX 9*1024*1024 / 4096

typedef struct{
    struct vnode* file;
    struct bitmap* bitmap;
    int free;
} swap_file;
// bit table che indica se un blocco sia occupato o meno

/*
 *
 * Functions:
 *     swap_create  -  apre lo swap_file e lo alloca se non esiste, restituisce il vnode ad esso associato
 * 
 *     swap_get  -  legge il blocco allocato nel file in posizione index, pone il corrispondente bit della bitmap a 0 e scrive il blocco in memoria all'indirizzo p_addr
 *     swap_set  -  legge il blocco di memoria all'indirizzo address e lo scrive nel file utilizzando la prima posizione libera, ritorna la posizione nel file
 */

swap_file* swap_create();
vdid swap_get(paddr_t address, int index, swap_file* swap);
int void swap_set(paddr_t address, swap_file* swap);