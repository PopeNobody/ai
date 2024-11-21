#include "system.hh"
#include "checkret.hh"
#include "md5.hh"
#include "unixpp.hh"
#include "util.hh"

using unixpp::range_t;
using checkret::xopenat;
using checkret::xmmap;


range_t unixpp::xmmap_file(const path &fname,bool write) {
  int prot=PROT_READ;
  int mode=O_RDONLY;
  if(write) {
    prot|=PROT_WRITE;
    mode|=O_RDWR;
  };
  range_t res;
  int fd=xopenat(AT_FDCWD,fname,mode);
  size_t size=lseek(fd,0,SEEK_END);
  char*mem=
    (char*)xmmap(0,size?size:1,prot,MAP_PRIVATE,fd,0);
  res=range_t(mem,mem+size);
  return res;
};

using unixpp::range_t;
using unixpp::xmmap_file;
using std::string;
using hash_ns::md5_ctx;

unixpp::md5_t unixpp::md5(const unixpp::range_t &range)
{
  md5_ctx ctx;
  md5_init_ctx(&ctx);
  md5_process_bytes( range.beg(),range.size(),&ctx);
  md5_t res;
  md5_finish_ctx(&ctx,(char*)&res);
  return res;
}
unixpp::md5_t unixpp::md5(const path &file) {
  return md5(xmmap_file(file));
};
