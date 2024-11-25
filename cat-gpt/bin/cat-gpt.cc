#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <boost/program_options.hpp>
#include <api.hh>

using json = nlohmann::json;
namespace po = boost::program_options;
using namespace std;
using api::api_t;

// Function to write the response data from curl to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void set_headers(CURL *curl, const vector<string> headers) {
  curl_slist *list=0;
  for(const auto &header : headers) {
    list = curl_slist_append(list,  header.c_str());
  };
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
}

std::string generate_response(api_t &api, const string& prompt)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    cout << "prompt: " << prompt << endl;
    cout << "   url: " << api.url()  << endl;
    cout << "   key: " << api.api_key() << endl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api.url().begin());

        // Set up headers
        set_headers(curl, api.headers());

        // Prepare the JSON payload
        json payload = api.payload(prompt);
        std::string payload_str = payload.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());

        // Set up callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

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
string read_file(const istream &str) {
  string text;
  string line;
  while (getline(std::cin, line)) {
    text+=line+"\n";
  }
  return text;
};
string trim(const string &str) {
  auto beg(str.begin()), end(str.end());
  while(beg!=end && isspace(*beg++))
    ;
  --beg;
  while(beg!=end && isspace(*--end))
    ;
  ++end;
  return string(beg,end);
};
char *basename(char *path) {
  char *base=path;
  while(*path) {
    if(*path=='/')
      base=++path;
    else
      ++path;
  };
  cout << (path-base) << endl;
  return base;
};
int main(int argc, char** argv) {
  try {
    po::options_description desc("options:");
    desc.add_options()
      ("help", "produce help message");
    //        ("api_key", po::value<std::string>(), "OpenAI API key");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 1;
    }

    {
      api_t api("cat-gem");
       cout << setw(2) << api.payload("<THIS IS THE PROMPT>") << endl;
       cout << endl << endl;
    };
    {
      api_t api("cat-gpt");
      cout << setw(2) << api.payload("<THIS IS THE PROMPT>") << endl;
      cout << endl << endl;
    };
    string prompt = read_file(cin);
    prompt=trim(prompt);
    if(prompt.empty()){
      cerr << "No prompt" << endl;
      return 1;
    };
    cout << (void*)basename(argv[0]) << endl;
    cout << basename(argv[0]) << endl;
    api_t api(basename(argv[0]));
    std::string response = generate_response(api,prompt);
    std::cout << response << std::endl;
    return 0;
  } catch ( std::exception &ex ) {
    cout << "caught: " << ex.what() << endl;
    return 1;
  };
}

