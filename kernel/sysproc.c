#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int mprotect(void *addr, int len)
{
    if (!addr || len <= 0)
        return -1;
    struct proc *p = myproc();

    // Calculate the total length in bytes (number of pages * page size)
    uint64 total_len = len * PGSIZE;

    // Check if the address and range are within user space bounds
    if ((uint64)addr >= MAXVA || (uint64)addr + total_len > MAXVA)
        return -1; // Address or range is out of bounds

    // recorrer the pages to protect
    for (int i = 0; i < len; i++)
    {

        //shift the initial address to the right place for a PTE 
        uint64 va = (uint64)addr + i*PGSIZE;

        //get a pointer to the PTE
        pte_t *pte = walk(p->pagetable, va, 0);
        //check if the PTE we got is valid
        if (pte == 0) return -1;
        // Dereference to get the entry
        pte_t entry = *pte; 
        // Check if the page is valid by checking the V bit
        //the and operation will return 0 if the V bit is 0 thus the page is not valid
        // PTE_V = 1L << 0 -> 00000001 and 00000001 = 00000001 -> 1
        if ((entry & PTE_V) == 0) return -1; // La dirección virtual no está mapeada

        // flips the W bit to 1
        *pte &= ~PTE_W; 
        }
    return 0; // Éxito
}

int munprotect(void *addr, int len)
{
    if (!addr || len <= 0)
        return -1;
    struct proc *p = myproc();

    // Calculate the total length in bytes (number of pages * page size)
    uint64 total_len = len * PGSIZE;

    // Check if the address and range are within user space bounds
    if ((uint64)addr >= MAXVA || (uint64)addr + total_len > MAXVA)
        return -1; // Address or range is out of bounds

    // recorrer the pages to protect
    for (int i = 0; i < len; i++)
    {

        //shift the initial address to the right place for a PTE 
        uint64 va = (uint64)addr + i*PGSIZE;

        //get a pointer to the PTE
        pte_t *pte = walk(p->pagetable, va, 0);
        //check if the PTE we got is valid
        if (pte == 0) return -1;
        // Dereference to get the entry
        pte_t entry = *pte; 
        // Check if the page is valid by checking the V bit
        //the and operation will return 0 if the V bit is 0 thus the page is not valid
        // PTE_V = 1L << 0 -> 00000001 and 00000001 = 00000001 -> 1
        if ((entry & PTE_V) == 0) return -1; // La dirección virtual no está mapeada

        // flips the W bit to 1
        *pte |= PTE_W; 
        }
    return 0; // Éxito
}

uint64
sys_mprotect(void)
{
  uint64 addr;
  uint64 len;
  argaddr(0, &addr);
  argaddr(1, &len);
  return mprotect((void *)addr, len);
}

uint64
sys_munprotect(void)
{
  uint64 addr;
  uint64 len;
  argaddr(0, &addr);
  argaddr(1, &len);
  return munprotect((void *)addr, len);
}


