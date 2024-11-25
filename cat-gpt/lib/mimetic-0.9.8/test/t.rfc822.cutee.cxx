#include "cutee.h"
#include "t.rfc822.h"
using namespace cutee;
struct run_testRfc822: public mimetic::testRfc822
{
  void run()
  {
        setUp();
    run_testAddress();
    run_testMailbox();
    run_testGroup();
    tearDown();
  }
  uint count() { return 3; }
};
static struct testRfc822_add_to_list: public cutee::TestList
{
  testRfc822_add_to_list()
  {
  list[list_idx++] = new run_testRfc822;
  }
} testRfc822_addit;
