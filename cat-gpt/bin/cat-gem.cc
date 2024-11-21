#include <iostream>
#include <string>
#include <curl/curl.h> 
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

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

int main() {
    // Initialize libcurl
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        // Set API endpoint 
        std::string api_endpoint = "https://api.gemini.com/v1/completions"; // Placeholder

        // Get prompt from standard input
        std::string prompt;
        std::cout << "Enter your prompt: ";
        std::getline(std::cin, prompt);

        // Create JSON payload
        json payload = {
            {"model", "gemini-pro"}, 
            {"prompt", prompt},
            {"temperature", 0.7},
            {"max_output_tokens", 1024}
        };

        // Convert JSON payload to string
        std::string json_payload = payload.dump();

        // Set cURL options
        curl_easy_setopt(curl, CURLOPT_URL, api_endpoint.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_payload.length());

        // Set headers (replace with your actual API key)
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer YOUR_API_KEY"); // Placeholder
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set up response handling
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        } else {
            // Parse the JSON response
            json response = json::parse(response_string);

            // Extract and print the generated text
            std::cout << response["text"] << std::endl;
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}