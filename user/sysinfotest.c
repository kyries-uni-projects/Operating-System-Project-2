#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

void
sinfo(struct sysinfo *info) {
  if (sysinfo(info) < 0) {
    printf("FAIL: sysinfo failed\n");
    exit(1);
  }
}

void
testmem() {
  struct sysinfo info;
  uint64 n = 20000;
  struct sysinfo info1;
  
  sinfo(&info);
  
  if (info.nproc == 0) {
    printf("FAIL: nproc is 0\n");
    exit(1);
  }
  
  if (info.freemem == 0) {
    printf("FAIL: freemem is 0\n");
    exit(1);
  }
  
  if((uint64)sbrk(n) == -1){
    printf("sbrk failed");
    exit(1);
  }

  sinfo(&info1);
  
  if(info1.freemem >= info.freemem){
    printf("FAIL: free mem %lu -> %lu\n", info.freemem, info1.freemem);
    exit(1);
  }
  
  printf("sysinfotest: OK\n");
}

int
main(int argc, char *argv[])
{
  testmem();
  exit(0);
}
