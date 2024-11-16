#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <boost/program_options.hpp>

using json = nlohmann::json;
namespace po = boost::program_options;

// Function to write the response data from curl to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string generate_response(const std::string& prompt, const std::string& api_key) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

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

int main(int argc, char** argv) {
    // Define and parse command-line arguments
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("api_key", po::value<std::string>(), "OpenAI API key");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    // Get the API key
    std::string api_key;
    if (vm.count("api_key")) {
        api_key = vm["api_key"].as<std::string>();
    } else {
        const char* env_api_key = std::getenv("OPENAI_API_KEY");
        if (!env_api_key) {
            std::cerr << "Error: OpenAI API key must be provided via --api_key option or OPENAI_API_KEY environment variable." << std::endl;
            return 1;
        }
        api_key = std::string(env_api_key);
    }

    // Read the prompt from stdin
    std::stringstream prompt_buffer;
    std::string line;
    while (std::getline(std::cin, line)) {
        prompt_buffer << line << "\n";
    }

    // Generate the response
    std::string response = generate_response(prompt_buffer.str(), api_key);
    std::cout << response << std::endl;

    return 0;
}

