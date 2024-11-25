#include "cutee.h"
#include "t.parser.h"
using namespace cutee;
struct run_parser_fixed_bugs: public mimetic::parser_fixed_bugs
{
  void run()
  {
        setUp();
    run_t0_input_iterator();
    run_t0_random_iterator();
    tearDown();
  }
  uint count() { return 2; }
};
static struct parser_fixed_bugs_add_to_list: public cutee::TestList
{
  parser_fixed_bugs_add_to_list()
  {
  list[list_idx++] = new run_parser_fixed_bugs;
  }
} parser_fixed_bugs_addit;
