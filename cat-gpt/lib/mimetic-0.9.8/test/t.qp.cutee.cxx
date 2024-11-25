#include "cutee.h"
#include "t.qp.h"
using namespace cutee;
struct run_test_qp: public mimetic::test_qp
{
  void run()
  {
        setUp();
    run_testEncode();
    run_testEncodeBlock();
    run_testBinaryEncode();
    run_testBinaryEncodeBlock();
    run_testDecode();
    run_testDecodeBlock();
    run_testBinaryInputDecode();
    run_testBinaryInputDecodeBlock();
    run_testMalformedInputDecode();
    run_testMalformedInputDecodeBlock();
    run_testTbValues();
    tearDown();
  }
  uint count() { return 11; }
};
static struct test_qp_add_to_list: public cutee::TestList
{
  test_qp_add_to_list()
  {
  list[list_idx++] = new run_test_qp;
  }
} test_qp_addit;
