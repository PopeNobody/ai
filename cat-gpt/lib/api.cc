#include <api.hh>
#include <iostream>
using namespace std;
namespace api {
  api_t::body_t::body_t(csr name)
  {
  }; 
  class gemini_t : public api_t::body_t {
    public:
      gemini_t(const string &name)
        :body_t(name)
      {
        char *api_key=getenv("GEMINI_API_KEY");
        assert(api_key);
        api_key_=api_key;
      };

    vector<string> &headers() {
      static vector<string> res;
      if(res.empty()){
        res.push_back("Content-Type: application/json");
        res.push_back("Authorization: Bearer " + api_key());
      }
      return res;
    };
    virtual vector<string> &headers() const {
      static vector<string> res;
      if(res.empty()){
        res.push_back("Content-Type: application/json");
        res.push_back("Authorization: Bearer " + api_key());
      }
      return res;
    }
    virtual json payload(const string &prompt) const {
      json res;
      return res;
    }
  };
  class chatgpt_t : public api_t::body_t {
    public:
    chatgpt_t(const string &name)
      : api_t::body_t(name)
    {
      env_key_="OPENAI_API_KEY";
      char *api_key=getenv(env_key_.c_str());
      api_key_=api_key;
      url_="http://api.openai.com/";
    };
    virtual vector<string> &headers() const {
      static vector<string> res;
      if(res.empty()){
        res.push_back("Content-Type: application/json");
        res.push_back("Authorization: Bearer " + api_key());
      }
      return res;
    }
    virtual json payload(const string &prompt) const {
      json res;
      return res;
    }
    vector<string> &headers() {
      static vector<string> res;
      if(res.empty()){
        res.push_back("Content-Type: application/json");
        res.push_back("Authorization: Bearer " + api_key());
      }
      return res;
    };
  };
  api_t::api_t(const string &name)
  {
    if(name=="chatgpt" || name=="cat-gpt") {
      body=new chatgpt_t(name);
    } else if (name=="gemini" || name =="cat-gem") {
      body=new gemini_t(name);
    } else {
      throw new runtime_error("no api for '"+name+"'");
    };
  };
};
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
  body_b::body_b()
  {
  };
  body_b::~body_b(){
    assert(!refs);
  };
};
