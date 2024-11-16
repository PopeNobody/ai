#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ... (WriteCallback function remains the same) ...

int main() {
  // Set up cURL
  CURL *curl = curl_easy_init();
  if (!curl) {
    std::cerr << "Failed to initialize cURL" << std::endl;
    return 1;
  }

  // Set GitLab API URL
  std::string api_url = "https://gitlab.com/api/v4/groups/your_group_id/projects"; // Replace with your group ID

  // Set GitLab access token
  std::string access_token = "your_access_token"; // Replace with your access token
  std::string header = "PRIVATE-TOKEN: " + access_token;

  // Set cURL options
  curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, (curl_slist *)header.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

  // Perform the request
  std::string response_string;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
    return 1;
  }

  // Clean up cURL
  curl_easy_cleanup(curl);

  // Parse the JSON response
  json response_json = json::parse(response_string);
  for (const auto& project : response_json) {
    std::cout << project["name"] << std::endl;
  }

  return 0;
}