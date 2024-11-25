#include "cutee.h"
#include "t.utils.h"
using namespace cutee;
struct run_t_utils: public mimetic::t_utils
{
  void run()
  {
        setUp();
    run_t_int2str();
    run_t_int2hex();
    tearDown();
  }
  uint count() { return 2; }
};
static struct t_utils_add_to_list: public cutee::TestList
{
  t_utils_add_to_list()
  {
  list[list_idx++] = new run_t_utils;
  }
} t_utils_addit;
