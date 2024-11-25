#include "cutee.h"
#include "t.base64.h"
using namespace cutee;
struct run_test_base64: public mimetic::test_base64
{
  void run()
  {
        setUp();
    run_testEncode();
    run_testEncodeBlock();
    run_testDecode();
    run_testDecodeBlock();
    tearDown();
  }
  uint count() { return 4; }
};
static struct test_base64_add_to_list: public cutee::TestList
{
  test_base64_add_to_list()
  {
  list[list_idx++] = new run_test_base64;
  }
} test_base64_addit;
