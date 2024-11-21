#include "system.hh"
#include "checkret.hh"
#include "fixed_buf.hh"
#include "unixpp.hh"

#define announce() 
//dprintf(2,"%s:%d:%s\n",__FILE__,__LINE__,__PRETTY_FUNCTION__);

using namespace checkret;
using unixpp::range_t;

int checkret::xbind(int fd, const struct sockaddr *addr, socklen_t len){
  announce();
  int res=bind(fd,addr,len);
  if(res<0)
    pexit(2,"bind");
  return res;
};
int checkret::xinet_aton(const char *cp, struct in_addr *inp){
  announce();
  int res=inet_aton(cp,inp);
  if(!res)
   pexit(3,"inet_aton"); 
  return res;
};
int checkret::xconnect(int sock, sockaddr*addr,socklen_t len){
  announce();
  int res=connect(sock,addr,len);
  if(res<0)
    pexit(5,"connect");
  return res;
};


int checkret::xopenat(int dirfd, const path &name, int flags,mode_t mode)
{
  announce();
  int res=openat(dirfd,name.c_str(),flags,mode);
  if(res<0){
    perror("open");
    exit(6);
  };
  return res;
};
void checkret::xexit(int res){
  _exit(1);
  abort();
};
int checkret::xread(int fd, char *const buf, size_t size,bool full){
  announce();
  char *beg=buf;
  char *end=beg+size;  
  while(beg!=end) {
    int res=read(fd,beg,end-beg);
    if(res<0){
      perror("read");
      exit(7);
    } else if (res==0) {
      break;
    } else {
      beg+=res;
    }
  }
  return beg-buf;
};
int checkret::xsocket(int family, int type, int prot){
  announce();
  int res=socket(family,type,prot);
  if(res<0) {
    perror("socket");
    exit(1);
  };
  return res;
};
int checkret::xlisten(int sock, int backlog){
  announce();
  int res=listen(sock,backlog);
  if(res){
    perror("listen");
    exit(4);
  };
  return 0;
};
int checkret::xaccept(int sock, sockaddr *addr, socklen_t *addrlen){
  announce();
  int res=accept(sock,addr,addrlen);
  if(res<=0){
    perror("accept");
    exit(4);
  };
  return res;
}
int checkret::xaccept4(int sock, sockaddr *addr, socklen_t *addrlen,int flags){
  announce();
  int res=accept4(sock,addr,addrlen,flags);
  if(res<=0){
    perror("accept4");
    exit(4);
  };
  return res;
}
size_t xxwrite(int fd, const char *const buf, size_t size, bool full) {
  announce();
  const char *beg=buf;
  const char *end;
  if(size==-1){
    end=beg;
    while(*end)
      end++;
  } else {
    end=beg+size;
  };

  while(end>beg){
    int res=write(fd,beg,end-beg);
    if(!res) {
      if(full)
        continue;
      else
        return 0;
    };
    beg+=res;
  }
  return beg-buf;
};
void checkret::xchdir(const path &dir){
  if(chdir(dir.c_str()))
    perror("chdir");
};
size_t checkret::xwrite(int fd, const char *const buf, size_t size, bool full) {
  size_t res = xxwrite(fd,buf,size,full);
  //dprintf(2,"xwrite(%lu) => %lu\n", size, res);
  return res;
}
//   int xwrite(int fd, const char *const buf, size_t size, bool full) {
//     int res;
//     for(int i=0;i<size;i++){
//       res+=xxwrite(fd,buf+i,1,true);
//     };
//     return res;
//   }
int checkret::xdup2(int oldfd, int newfd) {
  announce();
  int res=dup2(oldfd,newfd);
  if(res<0){
    perror("dup2");
    exit(9);
  }
  return res;
};
int checkret::xclose(int fd){
  int res=close(fd);
  if(res<0){
    perror("close");
    exit(10);
  }
  return res;
};
int checkret::xsleep(int seconds){
  return sleep(seconds);
};
int checkret::xsetsockopt(int sock, int proto, int flag, char *value, size_t size){
  int res=setsockopt(sock,proto,flag,value,size);
  if(res<0)
    pexit(19,"setsockopt");
  return res;
};
void checkret::xftruncate(int fd, off_t off) {
  if(ftruncate(fd,off))
    pexit(12,"xftruncate");
};
int checkret::bind_accept_fork(const char *addr, int port) {
  int sock = xsocket(AF_INET,SOCK_STREAM,0);
  int flag=1;
  xsetsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &flag, sizeof(int));
  xsetsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (char *) &flag, sizeof(int));
  linger lin;
  lin.l_onoff = 0;
  lin.l_linger = 0;
  xsetsockopt(sock, SOL_SOCKET, SO_LINGER, (char *)&lin, sizeof(linger));

  int res; 
  sockaddr_in sin_addr;
  memset(&sin_addr,0,sizeof(sin_addr)); 
  res = xinet_aton(addr,&sin_addr.sin_addr);
  sin_addr.sin_port = htons(port);
  sin_addr.sin_family = AF_INET;
  size_t len=sizeof(sin_addr);
  dprintf(2,"%s: listen\n",fmt_now());
  res=xbind(sock,(sockaddr*)&sin_addr,len);  
  dprintf(2,"%s: listen\n",fmt_now());
  res=xlisten(sock,1);
  while(true){
    socklen_t socklen;
    dprintf(2,"%s: accepting on %s:%d\n",fmt_now(),addr,port);
    int sockfd=xaccept(sock,(sockaddr*)&sin_addr,&socklen);
    dprintf(2,"%s: connection from: %s %d\n",
        fmt_now(),
        inet_ntoa(sin_addr.sin_addr),ntohs(sin_addr.sin_port));
    xsetsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
    int pid=xfork();
    dprintf(2,"%d => %d\n",getpid(),pid);
    if(!pid) {
      xclose(sock);
      return sockfd;
    };
    close(sockfd);
  };
};
int checkret::bind_accept_nofork(const char *addr, int port) {
  int sock = xsocket(AF_INET,SOCK_STREAM,0);
  int flag=1;
  xsetsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &flag, sizeof(int));
  xsetsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (char *) &flag, sizeof(int));
  linger lin;
  lin.l_onoff = 0;
  lin.l_linger = 0;
  xsetsockopt(sock, SOL_SOCKET, SO_LINGER, (char *)&lin, sizeof(linger));

  int res; 
  sockaddr_in sin_addr;
  memset(&sin_addr,0,sizeof(sin_addr)); 
  res = xinet_aton(addr,&sin_addr.sin_addr);
  sin_addr.sin_port = htons(port);
  sin_addr.sin_family = AF_INET;
  size_t len=sizeof(sin_addr);
  dprintf(2,"%s: listen\n",fmt_now());
  res=xbind(sock,(sockaddr*)&sin_addr,len);  
  dprintf(2,"%s: listen\n",fmt_now());
  res=xlisten(sock,1);
  while(true){
    socklen_t socklen;
    dprintf(2,"%s: accepting on %s:%d\n",fmt_now(),addr,port);
    int sockfd=xaccept(sock,(sockaddr*)&sin_addr,&socklen);
    dprintf(2,"%s: connection from: %s %d\n",
        fmt_now(),
        inet_ntoa(sin_addr.sin_addr),ntohs(sin_addr.sin_port));
    xsetsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
    close(sock);
    return sockfd;
  };
};
int checkret::xfork(){
  int res=fork();
  if(res<0)
    pexit(12,"fork");
  return res;
};
void checkret::xpipe(int fds[2]) {
  if(pipe(fds))
    pexit(13,"pipe");
};
void checkret::xmkdirat(int dirfd, const path &pathname, mode_t mode){
  dprintf(2,"xmkdirat(%d,\"%s\",%d)\n",dirfd,pathname,mode);
  if(!mkdirat(dirfd,pathname.c_str(),mode))
    return;
  pexit(14,"mkdirat");
};
void checkret::xlink(const char *oldpath, const char *newpath){
  if(!link(oldpath,newpath))
    return;
  pexit(17,"link");
};
void checkret::xunlinkat(int dirfd, const char *path, int flags) {
  if(unlinkat(dirfd,path,flags))
    pexit(16,"unlinkat");
}
void checkret::xlinkat(int olddirfd, const char *oldpath,
    int newdirfd, const char *newpath, int flags)
{
  if(!linkat(olddirfd,oldpath,newdirfd,newpath,flags)) 
    return;
  pexit(18,"linkat");
};
const char *checkret::fmt_today()
{
  static fixed_buf<20> res;
  tm gm;
  time_t now;
  time(&now);
  gmtime_r(&now,&gm);
  snprintf(res.buf,res.size(),"%04d%02d%02d",
      gm.tm_year+1900,gm.tm_mon+1,gm.tm_mday);
  return res.beg();
}
const char *checkret::fmt_now()
{
  static fixed_buf<20> res;
  tm gm;
  time_t now;
  time(&now);
  gmtime_r(&now,&gm);
  snprintf(res.buf,res.size(),"%04d%02d%02d-%02d%02d%02d",
      gm.tm_year+1900,gm.tm_mon+1,gm.tm_mday,
      gm.tm_hour,gm.tm_min,gm.tm_sec);
  return res.beg();
};
void *checkret::xmmap(void *addr, size_t length, int prot, int flags,
    int fd, off_t offset)
{
  void *res=mmap(addr,length,prot,flags,fd,offset);
  if(res==MAP_FAILED)
    pexit(1,"mmap");
  return res;
};
void checkret::xmunmap(void *addr, size_t length){
  if(munmap(addr,length))
    pexit(1,"munmap");
};

int checkret::xfstatat (int fd, const path &file, struct stat *buf, int flag);
int checkret::xfchmodat (int fd, const path &file, mode_t mode, int flag);
int checkret::xmknodat (int fd, const path &path, mode_t mode, dev_t dev);
int checkret::xmkfifoat (int fd, const path &path, mode_t mode);
int checkret::xutimensat (int fd, const path &path, const struct timespec times[2], int flags);
int checkret::xlseek(int fd, int off, int origin){
  int res = lseek(fd,off,origin);
  if(res==(off_t)-1)
    pexit(16,"lseek");
  return res;
};
