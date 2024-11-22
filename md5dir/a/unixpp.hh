#ifndef unixpp_hh
#define unixpp_hh unixpp_hh

#ifndef system_hh
#error system_hh not included
#endif
#include <string>
#include <array>

namespace unixpp {
  using boost::filesystem::path;
  using std::string;
  using std::array;
  using std::ostream;

  struct range_t {
    char *_beg;
    char *_end;
    range_t()
      :_beg(0),_end(0)
    {
    }
    range_t(char *beg, char *end=0)
      :_beg(beg), _end(end)
    {
      if(_end || !_beg)
        return;
      _end=_beg;
      while(*_end++)
        ;
    }
    range_t(char *beg, size_t size)
      :_beg(beg), _end(beg+size)
    {
    } 
    const char *beg() const{
      return _beg;
    };
    const char *end() const{
      return _end;
    };
    size_t size() const {
      return end()-beg();
    }
    const char &operator[](int idx) const{
      return beg()[idx];
    }
  };
  struct range_vt {
  };
  struct md5_t {
    array<unsigned char,16> data;
    public:
    md5_t()
      : data{
        0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78,
        0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xf0, 0x00
      }
    {
    };
    md5_t(const array<unsigned char,16> data)
      : data(data)
    {
    }
    md5_t(const md5_t &rhs)
      : data(rhs.data)
    {
    };
    md5_t(const path &path);
    md5_t(const range_t &text);
    string to_string() const;
  };
  ostream &operator<<(ostream &lhs, const md5_t &rhs);

  range_t xmmap_file(const path &fname,bool write=false);


  using std::array;
  using unixpp::range_t;
  using unixpp::md5_t;

  md5_t md5(const range_t &range);
  md5_t md5(const path &file);

  string magic_mime(const range_t &range);
  string magic_ext(const range_t &range);
}

#endif
