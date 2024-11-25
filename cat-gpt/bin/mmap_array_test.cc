#include <iostream>
#include "mmap_array.hh"
using namespace std;

const char *exe_name=0;
void usage(const string &msg) {
    cerr << "usage: " <<  exe_name << " <filename>" << endl;
    cerr << msg << endl;
    exit(1);
};
int main(int argc, char**argv) {
  exe_name=argv[0];
  if(argc<2)
    usage("no filename provided");
  for(int i=1;i<argc;i++) {
    try {
      mmap_array fileArray(argv[i]);
      cout.write(fileArray.begin(),fileArray.size());
      if(fileArray.size()) {
        cout << (int)fileArray.front() << endl;
        cout << (int)fileArray.back() << endl;
      };
    } catch (const std::exception& ex) {
      std::cerr << "Error: " << ex.what() << std::endl;
    }
  }
  return 0;
}
