#include "cutee.h"
#include "t.strutils.h"
using namespace cutee;
struct run_testStrUtils: public mimetic::testStrUtils
{
  void run()
  {
        setUp();
    run_test_remove_external_blanks();
    tearDown();
  }
  uint count() { return 1; }
};
static struct testStrUtils_add_to_list: public cutee::TestList
{
  testStrUtils_add_to_list()
  {
  list[list_idx++] = new run_testStrUtils;
  }
} testStrUtils_addit;
