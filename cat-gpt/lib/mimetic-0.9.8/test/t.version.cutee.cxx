#include "cutee.h"
#include "t.version.h"
using namespace cutee;
struct run_test_version: public mimetic::test_version
{
  void run()
  {
        setUp();
    run_ctor();
    run_eq();
    run_diff();
    run_less();
    run_greater();
    tearDown();
  }
  uint count() { return 5; }
};
static struct test_version_add_to_list: public cutee::TestList
{
  test_version_add_to_list()
  {
  list[list_idx++] = new run_test_version;
  }
} test_version_addit;
