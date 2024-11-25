#include "cutee.h"
#include "t.circular_buffer.h"
using namespace cutee;
struct run_test_circular_buffer: public mimetic::test_circular_buffer
{
  void run()
  {
        setUp();
    run_testOverflow();
    run_testCount();
    run_testCmpCh();
    run_testInOut();
    run_testFill();
    run_testIdx();
    run_testEq();
    run_testCompare();
    run_testToStr();
    tearDown();
  }
  uint count() { return 9; }
};
static struct test_circular_buffer_add_to_list: public cutee::TestList
{
  test_circular_buffer_add_to_list()
  {
  list[list_idx++] = new run_test_circular_buffer;
  }
} test_circular_buffer_addit;
