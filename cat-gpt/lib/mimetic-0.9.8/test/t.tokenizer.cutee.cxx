#include "cutee.h"
#include "t.tokenizer.h"
using namespace cutee;
struct run_test_tokenizer: public mimetic::test_tokenizer
{
  void run()
  {
        setUp();
    run_testTwo();
    tearDown();
  }
  uint count() { return 1; }
};
static struct test_tokenizer_add_to_list: public cutee::TestList
{
  test_tokenizer_add_to_list()
  {
  list[list_idx++] = new run_test_tokenizer;
  }
} test_tokenizer_addit;
