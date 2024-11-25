#include "cutee.h"
#include "t.mimemessage.h"
using namespace cutee;
struct run_test_mime: public mimetic::test_mime
{
  void run()
  {
        setUp();
    run_testMimeEntityBuild();
    run_testMimeBinaryQpAttach();
    run_testMimeBinaryQpBinaryAttach();
    run_testMimeBinaryBase64Attach();
    run_testMimeMessageRfc822();
    run_testMimeHeaderFold();
    tearDown();
  }
  uint count() { return 6; }
};
static struct test_mime_add_to_list: public cutee::TestList
{
  test_mime_add_to_list()
  {
  list[list_idx++] = new run_test_mime;
  }
} test_mime_addit;
