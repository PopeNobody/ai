#include "system.hh"
#include "md5.hh"

using namespace std;
using namespace boost::filesystem;
using unixpp::range_t;
using unixpp::xmmap_file;

char to_hex(int val) {
  if(val>16)
    val=val&0xf;
  if ( val < 10 ) {
    return '0'+val;
  } else {
    return 'a'+val-10;
  };
};
using unixpp::md5_t;
class md5_map : public map<path,md5_t> {
};
md5_t::md5_t(const range_t &rhs)
  :data(md5(rhs).data)
{
};
string unixpp::md5_t::to_string() const {
  char res[33];
  for(int i=0;i<16;i++) {
    sprintf(res+i*2,"%02x",data[i]);
  };
  res[32]=0;
  return res;
};
ostream &unixpp::operator<<(ostream &lhs, const md5_t &rhs) {
  return lhs << rhs.to_string();
};
md5_t md5(const path &rhs) {
  if(is_directory(rhs)){
    vector<path> dir;
    vector<path> reg;
    md5_map txt;
    for(auto &ent : directory_iterator(rhs)) {
      if(ent.path().filename()==".md5")
        continue;
      if(ent.path().filename()==".git")
        continue;
      if(is_directory(ent)) {
        dir.push_back(ent.path());
      } else if ( is_regular_file(ent) ) {
        reg.push_back(ent.path());
      } else {
        cerr << "ignore: " << endl;
        system((string("ls -l ")+ent.path().c_str()).c_str());
      };
    };
    using boost::filesystem::ofstream;
    path dirname = rhs;
    {
      dirname += "/.md5";
      ofstream dirfile(dirname);
      sort(dir.begin(),dir.end());
      for(auto d : dir) {
        dirfile << md5(d) << "  "
          << d.filename() << "/.md5"
          << endl;
      };
      sort(reg.begin(),reg.end());
      for(auto r : reg) {
        dirfile << md5(r) << "  " << r <<endl;
      };
    }
    return md5(dirname);
  } else if ( is_regular_file(rhs) ) {
    return md5(xmmap_file(rhs));
  } else {
    return md5("/dev/null");
  };
};
int main(int argc, char* argv[])
{
  path name=".";
  if(argc==2)
    name=argv[1];
  if(argc>2) {
    cerr << "usage: argv[0] <dir>" << endl;
    exit(1);
  };
  cout << md5(name) << "  " << name << endl;
  return 0;  
}
