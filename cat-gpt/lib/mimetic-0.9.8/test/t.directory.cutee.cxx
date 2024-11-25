#include "cutee.h"
#include "t.directory.h"
using namespace cutee;
struct run_test_directory: public mimetic::test_directory
{
  void run()
  {
        setUp();
    run_exists();
    run_emptyDir();
    run_withFiles();
    run_moreFiles();
    tearDown();
  }
  uint count() { return 4; }
};
static struct test_directory_add_to_list: public cutee::TestList
{
  test_directory_add_to_list()
  {
  list[list_idx++] = new run_test_directory;
  }
} test_directory_addit;
