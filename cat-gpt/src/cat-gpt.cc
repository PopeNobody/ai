/**
 *
 *  The cat-gpt program copies it's input to cat-gpt, and cat-gpt's
 *  output to you, the happy user.
 *
 *  ChatGPT ... Could you do me a favor, and change this to use mmap\
 *  rather than iostreams to do it's business?  Also, I'd like to add
 *  the ability to log.
 *
 *
 *
 */

#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <boost/program_options.hpp>

using json = nlohmann::json;
using namespace std;
using namespace std::filesystem;
namespace po = boost::program_options;

void pexit(int code, const string &m1) __attribute__((__noreturn__));
void pexit(int code, const string &m1){
  perror(m1.c_str());
  exit(code);
};
int xopenat(int dirfd, const char *pathname, int flags, mode_t mode=0) {
  int fd=openat(dirfd,pathname,flags,mode);
  if(fd<0)
    pexit(1,"openat");
  return fd;
};
int xopenat(int dirfd, const string &pathname, int flags, mode_t mode=0) {
  return xopenat(dirfd,pathname.c_str(),flags,mode);
};
int xopen(const char *pathname, int flags, mode_t mode) {
  return xopenat(AT_FDCWD,pathname,flags,mode);
};

// Function to write the response data from curl to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void *xmmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
  auto res=mmap(addr,length,prot,flags,fd,offset);
  if(res==(void*)-1)
    pexit(7,"mmap");
  return (void*)res;
};

bool mmap_file(const string &fname, const char *&beg, const char *&end)
{
  bool write=false;
  int prot=PROT_READ;
  int mode=O_RDONLY;
  if(write) {
    prot|=PROT_WRITE;
    mode|=O_RDWR;
  };
  int fd=xopenat(AT_FDCWD,fname,mode);
  size_t size=lseek(fd,0,SEEK_END);
  beg=(char*)xmmap(0,size?size:1,prot,MAP_PRIVATE,fd,0);
  end=beg+size;
  return true;
};
string generate_response(const string& prompt, const string& api_key) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

        // Set up headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Prepare the JSON payload
        json payload = {
            {"model", "gpt-4"},
            {"messages", {
                {{"role", "user"}, {"content", prompt}}
            }}
        };
        string payload_str = payload.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());

        // Set up callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // Parse the response JSON
    auto response_json = json::parse(readBuffer);
    if (response_json.contains("choices") && !response_json["choices"].empty()) {
        return response_json["choices"][0]["message"]["content"];
    } else {
        return "Error: Unable to retrieve a valid response from ChatGPT.";
    }
}
string trim(const string &str) {
  auto b(str.begin()), e(str.end());
  while( b!=e ) {
    if(isspace(*b))
      b++;
    else
      break;
  }; 
  return string(b,e);
};
int main(int argc, char** argv) {
    // Define and parse command-line arguments
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("api_key", po::value<string>(), "OpenAI API key");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    // Get the API key
    string api_key;
    if (vm.count("api_key")) {
        api_key = vm["api_key"].as<string>();
    } else {
        const char* env_api_key = getenv("OPENAI_API_KEY");
        if (!env_api_key) {
            cerr << "Error: OpenAI API key must be provided via --api_key option or OPENAI_API_KEY environment variable." << endl;
            return 1;
        }
        api_key = string(env_api_key);
    }

    // Read the prompt from stdin
    string buf;
    string line;
    while (getline(cin, line)) {
        buf+=line+="\n";
    }
    
    buf=trim(buf);
    // Generate the response
    string response = generate_response(buf, api_key);
    cout << response << endl;

    return 0;
}
