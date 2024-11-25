#include <rc.hh>
#include <cassert>

namespace util_ns {
  body_b *body_b::add_ref() {
    ++refs;
    return this;
  };
  body_b *body_b::rem_ref() {
    if(--refs)
      return this;
    else
      return 0;
  };
  body_b::~body_b(){
    assert(!refs);
  };
}
