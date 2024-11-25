#include "cutee.h"
#include "t.file.h"
using namespace cutee;
struct run_test_file: public mimetic::test_file
{
  void run()
  {
        setUp();
    run_testFileStdFile();
    run_testBinFileStdFile();
    run_testStdFile();
    run_testFileIterator();
    run_testFileConstIterator();
    run_testBinFileIterator();
    run_testBinFileConstIterator();
    tearDown();
  }
  uint count() { return 7; }
};
static struct test_file_add_to_list: public cutee::TestList
{
  test_file_add_to_list()
  {
  list[list_idx++] = new run_test_file;
  }
} test_file_addit;
