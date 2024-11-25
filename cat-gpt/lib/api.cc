#include <api.hh>
#include <iostream>
using namespace std;
namespace api {
  api_t::body_t::body_t(csr name, csr env_key, csr url) 
    : name_(name), env_key_(env_key), url_(url)
  {
    char *env=getenv(env_key_.c_str());
    if(env)
      api_key_=env;
  }; 
  const string gem_host="generativelanguage.googleapis.com";
  const string gem_path="v1beta/models/gemini-1.5-flash:generateContent";
  const string gem_url="https://"+gem_host+"/"+gem_path;
  class gemini_t : public api_t::body_t {
    public:
      gemini_t(const string &name)
        :body_t(name, "GEMINI_API_KEY", gem_url)
      {
        cerr << "name: " << name << endl;
        cerr << "ekey: " << env_key() << endl;
        cerr << " url: " << url() << endl;
      };

    vector<string> &headers() const {
      static vector<string> res;
      if(api_key_.empty()) {
        cerr << "no ami_key for this api" << endl;
      };
      if(res.empty()){
        res.push_back("Content-Type: application/json");
        res.push_back("Authorization: Bearer " + api_key());
      }
      return res;
    };
    virtual json payload(const string &prompt) const {
      json payload = {
        {"model", "gpt-4"},
        {"messages", 
          {
            {
              {
                "role", "user"
              }, 
              {
                "content", prompt
              }
            }
          }
        }
      };
      return payload;
    };
  };
  static string gpt_url="https://api.openai.com/v1/chat/completions";
  class chatgpt_t : public api_t::body_t {
    public:
      chatgpt_t(const string &name)
        : api_t::body_t(name, "OPENAI_API_KEY", gpt_url)
      {
        cerr << "name: " << name << endl;
        cerr << "ekey: " << env_key() << endl;
        cerr << " url: " << url() << endl;
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
        json res = {
          {"model", "gemini-pro"}, 
          {"prompt", prompt},
          {"temperature", 0.7},
          {"max_output_tokens", 1024}
        };
        cout << setw(2) << res << endl;

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
