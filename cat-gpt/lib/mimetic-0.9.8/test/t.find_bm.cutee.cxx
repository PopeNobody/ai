#include "cutee.h"
#include "t.find_bm.h"
using namespace cutee;
struct run_test_find_bm: public mimetic::test_find_bm
{
  void run()
  {
        setUp();
    run_find();
    tearDown();
  }
  uint count() { return 1; }
};
static struct test_find_bm_add_to_list: public cutee::TestList
{
  test_find_bm_add_to_list()
  {
  list[list_idx++] = new run_test_find_bm;
  }
} test_find_bm_addit;
