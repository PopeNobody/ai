#include "cutee.h"
#include "t.composite.h"
using namespace cutee;
struct run_test_composite: public mimetic::test_composite
{
  void run()
  {
        setUp();
    run_testBase64ToUpperCase();
    run_testBase64ToLowerCase();
    tearDown();
  }
  uint count() { return 2; }
};
static struct test_composite_add_to_list: public cutee::TestList
{
  test_composite_add_to_list()
  {
  list[list_idx++] = new run_test_composite;
  }
} test_composite_addit;
