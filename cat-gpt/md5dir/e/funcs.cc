#include "system.hh"

int wait_nohang(int *stat) {
  int res = waitpid(-1,stat,WNOHANG);
  return res;
}
void sigchild(int arg){
  dprintf(1,"sigchild(%d)\n",arg);
  int wstat;
  dprintf(1,"wait_nohang(&wstat)=>%d\n", wait_nohang(&wstat));
  dprintf(1,"             wstat =>%d\n", wstat);
};
