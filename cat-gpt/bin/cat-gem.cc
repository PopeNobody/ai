#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <curl/curl.h> 
#include <boost/lexical_cast.hpp>
#include <nlohmann/json.hpp> 
#include <mmap_array.hh>
#include <sys/stat.h>

using json = nlohmann::json;
using std::string;
using boost::lexical_cast;
using namespace std;

// Function to handle the response from the API
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
  size_t newLength = size*nmemb;
  size_t oldLength = s->size();
  try {
    s->resize(oldLength + newLength);
  }
  catch(std::bad_alloc &e) {
    //handle memory problem
    return 0;
  }

  std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
  return size*nmemb;
}
void pexit(int code, const char *msg) {
  perror(msg);
  exit(code);
}
int run(vector<string> args) {
//     CURL *curl;
//     CURLcode res;
//     curl = curl_easy_init();
//     if(curl) {
//       // Set API endpoint 
//       std::string api_endpoint = api.url();
//   
//       vector<mmap_array> files;
//       if(args.size()==0) {
//         std::string prompt;
//         if(isatty(0))
//           std::cout << "Enter your prompt: ";
//         std::string line;
//         while( std::getline(std::cin, line) ) {
//           prompt+=line;
//         };
//         struct stat buf;
//         if(stat("tmp",&buf)){
//           if(mkdir("tmp",0755)){
//             pexit(1,"mkdir:tmp");
//           }
//         };
//         string tmp = "tmp/prompt-"+ lexical_cast<string>(getpid())+".txt";
//         ofstream str(tmp);
//         str << prompt << flush;
//         args.push_back(tmp);
//       };
//       for(auto &arg: args) {
//         files.push_back(mmap_array(arg));
//       };
//       for(auto const &file : files) {
//         string prompt(file.data(),file.size());
//         // Create JSON payload
//         json payload = {
//           {"model", "gemini-pro"}, 
//           {"prompt", prompt},
//           {"temperature", 0.7},
//           {"max_output_tokens", 1024}
//         };
//   
//         // Convert JSON payload to string
//         std::string json_payload = payload.dump();
//   
//         // Set cURL options
//         curl_easy_setopt(curl, CURLOPT_URL, api_endpoint.c_str());
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_payload.length());
//   
//         // Set headers (replace with your actual API key)
//         struct curl_slist *headers = NULL;
//         headers = curl_slist_append(headers, "Content-Type: application/json");
//         // Placeholder
//         string key_hdr="Authorization: Bearer "+get_key();
//         headers = curl_slist_append(headers, key_hdr.c_str());
//         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//   
//         // Set up response handling
//         const char *tmp;
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tmp);
//   
//         // Perform the request
//         res = curl_easy_perform(curl);
//   
//         // Check for errors
//         if(res != CURLE_OK) {
//           fprintf(stderr, "curl_easy_perform() failed: %s\n",
//               curl_easy_strerror(res));
//         } else {
//           // Parse the JSON response
//           json response = json::parse(string(tmp));
//   
//           // Extract and print the generated text
//           std::cout << response["text"] << std::endl;
//         }
//   
//         // Clean up
//         curl_slist_free_all(headers);
//         curl_easy_cleanup(curl);
//       }
//     }
  return 0;
}
int main(int argc, char**argv) {
  return run(vector<string>(argv+1,argv+argc-1));
};
