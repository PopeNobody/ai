#ifndef api_hh
#define api_hh api_hh
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <map>
#include <iostream>
#include <rc.hh>
#include <type.hh>

namespace api {
  using util_ns::csr;
  using std::string;
  using std::vector;
  using nlohmann::json;
  using std::map;
  using std::cout;
  using util_ns::body_b;
  using util_ns::hand_t;
  class api_t {
    public:
    struct body_t : public body_b {
      mutable string api_key_;
      string name_;
      string env_key_;
      string url_;
      body_t(csr name, csr url, csr env_key);
      ~body_t(){
      };
      virtual vector<string> &headers() const=0;
      virtual const string &url() const {
        return url_;
      };
      virtual json payload(const string &prompt) const=0;
      virtual csr env_key() const {
        return env_key_;
      };
      virtual csr api_key() const {
        return api_key_;
      };
    };
    private:
    hand_t<body_t> body;
    public:
    api_t(const string &name);
    virtual vector<string> &headers() const {
      return body->headers();
    }
    virtual string url() const {
      return body->url();
    };
    string api_key() const {
      return body->api_key();
    };
    virtual json payload(const string &prompt) const {
      return body->payload(prompt);
    };
  };
}

#endif
