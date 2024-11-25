#include "cutee.h"
#include "t.contenttype.h"
using namespace cutee;
struct run_contenttype: public mimetic::contenttype
{
  void run()
  {
        setUp();
    run_parser();
    tearDown();
  }
  uint count() { return 1; }
};
static struct contenttype_add_to_list: public cutee::TestList
{
  contenttype_add_to_list()
  {
  list[list_idx++] = new run_contenttype;
  }
} contenttype_addit;
