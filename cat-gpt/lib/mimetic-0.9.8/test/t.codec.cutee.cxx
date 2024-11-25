#include "cutee.h"
#include "t.codec.h"
using namespace cutee;
struct run_test_codec: public mimetic::test_codec
{
  void run()
  {
        setUp();
    run_one();
    tearDown();
  }
  uint count() { return 1; }
};
static struct test_codec_add_to_list: public cutee::TestList
{
  test_codec_add_to_list()
  {
  list[list_idx++] = new run_test_codec;
  }
} test_codec_addit;
