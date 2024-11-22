#ifndef checkret_hh
#define checkret_hh checkret_hh

#ifndef system_hh
#error system_hh not included
#endif


namespace checkret 
{
  using boost::filesystem::path;
  int xstat(const path &pathname, struct stat *statbuf);
  int xfstat(int fd, struct stat *statbuf);
  int xlstat(const path &pathname, struct stat *statbuf);

  int xfstatat (int fd, const path &file, struct stat *buf, int flag);
  int xfchmodat (int fd, const path &file, mode_t mode, int flag);
  int xmknodat (int fd, const path &path, mode_t mode, dev_t dev);
  int xmkfifoat (int fd, const path &path, mode_t mode);
  int xutimensat (int fd, const path &path, const struct timespec times[2], int flags);

  void xlinkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags);
  void xunlinkat(int dirfd, const char *path, int flags);

  void *xmmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

  void xmunmap(void *addr, size_t length);


  void xmkdirp(const path &pathname, mode_t mode);
  void xmkdirat(int dirfd, const path &pathname, mode_t mode);
  int xopenat(int dirfd, const path &fname, int flags, mode_t mode=0777);

  int xsocket(int family, int type, int prot);

  int xbind(int fd, const struct sockaddr *addr, socklen_t len);

  void xexit(int res) __attribute__ ((noreturn));

  int xlseek(int fd, int off, int origin);

  //     int xexecve(const char *pathname,
  //         const char * argv[], char * envp[])
  //       __attribute__ ((noreturn));;
  //     
  //     int xexecve(const char *pathname,
  //         const char * argv[], char *const envp[])
  //     ;
  //     int execve(const char *pathname, char *const argv[],
  //         char *const envp[]);

  // missing in action  
  //  int xexecveat(int dirfd, const char *pathname,
  //      char *const argv[], char *const envp[],
  //      int flags);
  //
  //          int execlp(const char *file, const char *arg, ...
  //   		       /* (char  *) NULL */);
  //          int execle(const char *pathname, const char *arg, ...
  //   		       /*, (char *) NULL, char *const envp[] */);
  //          int execv(const char *pathname, char *const argv[]);
  //          int execvp(const char *file, char *const argv[]);
  //          int execvpe(const char *file, char *const argv[],
  //   		       char *const envp[]);
  int xinet_aton(const char *cp, struct in_addr *inp);
  int xlisten(int sock, int backlog);
  int xaccept(int sock, sockaddr *addr, socklen_t *addrlen);
  int xaccept4(int sock, sockaddr *addr, socklen_t *addrlen, int flags);
  int xconnect(int sock, sockaddr *addr, socklen_t len);
  int xread(int fd, char *buf, size_t size, bool full=false);
  size_t xwrite(int fd, const char *beg, size_t size, bool full=false);
  int xdup2(int oldfd, int newfd);
  int xclose(int fd);
  int xsleep(int seconds);
  int xsetsockopt(int sockfd, int proto, int flag, char *value, size_t size);
  int xfork();

  void xchdir(const path &dir);
  void xpipe(int fds[2]);


  inline pid_t 
    xwaitpid(pid_t child, int *stat,int opts)
    {
      pid_t res;
      res = waitpid(child,stat,opts);
      return res;
    }

  // write the whole zero-termed string.
  inline size_t write_cs(int fd, const char *str)
  {
    return xwrite(fd, str, strlen(str), true);
  };

  //     int xexecve(const char *pathname,
  //         const char * argv[], char * envp[])
  //       __attribute__ ((noreturn));;
  //     
  //     int xexecve(const char *pathname,
  //         const char * argv[], char *const envp[])
  //     ;
  //     int execve(const char *pathname, char *const argv[],
  //         char *const envp[]);

  // missing in action  
  //  int xexecveat(int dirfd, const char *pathname,
  //      char *const argv[], char *const envp[],
  //      int flags);

  //          int execlp(const char *file, const char *arg, ...
  //   		       /* (char  *) NULL */);
  //          int execle(const char *pathname, const char *arg, ...
  //   		       /*, (char *) NULL, char *const envp[] */);
  //          int execv(const char *pathname, char *const argv[]);
  //          int execvp(const char *file, char *const argv[]);
  //          int execvpe(const char *file, char *const argv[],
  //   		       char *const envp[]);
  //     inline int xcreat(const char *pathname, mode_t mode) 
  //     {
  //       return xopenat(AT_FDCWD,pathname,O_CREAT|O_WRONLY|O_TRUNC,mode); 
  //     }
  //     inline int xopen(const char *pathname, int flags, mode_t mode = -1) 
  //     {
  //       return xopenat(AT_FDCWD, pathname, flags, mode); 
  //     };


  void xftruncate(int fd, off_t length);
  void xtruncate(const char *path, off_t length);

  int bind_accept_fork(const char *addr, int port);
  int bind_accept_nofork(const char *addr, int port);
  int xread_ln(int con);

  int pexit(int ret,const char *msg) __attribute__ ((noreturn));

  inline int pexit(int ret,const char *msg){
    perror(msg);
    exit(ret);
  };
  inline int pexit(const char *msg) {
    return pexit(EXIT_FAILURE,msg);
  };
  const char *fmt_now();
  const char *fmt_today();


  //     int xopen(const char *name, int flags,mode_t mode=0777);
  void xlink(const char *oldpath, const char *newpath);
  inline void xunlink(const char *pathname) {
    xunlinkat(AT_FDCWD, pathname, 0);
  }
  //     inline int xmkdir(const char *pathname, mode_t mode) 
  //     {
  //       return mkdir( pathname, mode ); 
  //     };
}

#endif
