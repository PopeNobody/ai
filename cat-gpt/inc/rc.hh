#ifndef rc_hh
#define rc_hh rc_hh
namespace util_ns {
  class body_b {
    int refs;
    public:
    body_b();
    body_b(const body_b &rhs)
    {
    };
    body_b &operator=(const body_b&rhs) {
      return *this;
    };
    body_b *add_ref();
    body_b *rem_ref();
    virtual ~body_b();
  };
  template<typename body_t>
  class hand_t 
  {
    body_b *body;
    public:
    hand_t(body_t *body=0)
      : body(body)
    {
    };
    body_t *get() const {
      return dynamic_cast<body_t*>(body);
    };
    void set(body_t *rhs) {
      rhs->add_ref();
      if(body)
        body->rem_ref();
      body=rhs;
    };
    body_t *operator->() const {
      return get();
    };
    body_t &operator*() const {
      return *get();
    };
  };

};

#endif
