#include "cutee.h"
#include "t.tree.h"
using namespace cutee;
struct run_tree: public mimetic::tree
{
  void run()
  {
        setUp();
    run_buildTree();
    run_search();
    tearDown();
  }
  uint count() { return 2; }
};
static struct tree_add_to_list: public cutee::TestList
{
  tree_add_to_list()
  {
  list[list_idx++] = new run_tree;
  }
} tree_addit;
