#include "cutee.h"
#include "t.fieldparam.h"
using namespace cutee;
struct run_testFieldParam: public mimetic::testFieldParam
{
  void run()
  {
        setUp();
    run_parser();
    tearDown();
  }
  uint count() { return 1; }
};
static struct testFieldParam_add_to_list: public cutee::TestList
{
  testFieldParam_add_to_list()
  {
  list[list_idx++] = new run_testFieldParam;
  }
} testFieldParam_addit;
