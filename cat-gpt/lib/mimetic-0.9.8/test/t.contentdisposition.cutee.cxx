#include "cutee.h"
#include "t.contentdisposition.h"
using namespace cutee;
struct run_contentdisposition: public mimetic::contentdisposition
{
  void run()
  {
        setUp();
    run_parser0();
    run_parser1();
    tearDown();
  }
  uint count() { return 2; }
};
static struct contentdisposition_add_to_list: public cutee::TestList
{
  contentdisposition_add_to_list()
  {
  list[list_idx++] = new run_contentdisposition;
  }
} contentdisposition_addit;
