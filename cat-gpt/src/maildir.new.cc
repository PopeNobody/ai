Sure, below is a simple implementation of a delivery program in C++:

```cpp
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip> //for std::setfill, std::setw
#include <time.h>  //for time_t, struct tm, time, localtime
#include <openssl/md5.h>

void create_maildir(const std::string& path)
{
    std::string cmd = "mkdir -p ";
    cmd += path;
    cmd += "{tmp,new,cur}";
    system(cmd.c_str());
}

void write_to_file(const std::string& filename, const std::string& content)
{
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::app);
    if(file.is_open()) 
    {
        file << content;
        file.close();
    } 
    else 
    {
        std::cout << "Failed to open file: " << filename << '\n';
    }
}

std::string get_local_time_str() 
{
    time_t rawtime;
    struct tm *ptm;

    time ( &rawtime );
    ptm = localtime ( &rawtime );

    std::ostringstream strs;
    strs
      << std::setfill('0') 
      << std::setw(4) << (ptm->tm_year+1900) << "-"
      << std::setw(2) <<  ptm->tm_mon << "-"
      << std::setw(2) <<  ptm->tm_mday << "_"
      << std::setw(2) <<  ptm->tm_hour << "-"
      << std::setw(2) <<  ptm->tm_min << "-"
      << std::setw(2) <<  ptm->tm_sec;
         
    return strs.str();
}

int main(int argc, char *argv[]) 
{
    // Check if the -c flag was passed
    bool createNewMaildir = false;
    int i = 1; // skip the 0th element because it's the program's name

    if (strcmp(argv[1], "-c") == 0) 
    {
        createNewMaildir = true;
        i++;
    }

    for( ; i < argc; i++)
    {
        std::string maildirPath = argv[i];
        if(createNewMaildir)
            create_maildir(maildirPath);

        std::string message = "Test message"; //here, replace with your real message content
        
        std::string fileName = get_local_time_str();
        //Add calculating md5 logic here. Giving an exmaple that fileName is your time 
        std::string fullPath = maildirPath + "/" + fileName;

        write_to_file(fullPath, message);
    }
    return 0;
}
```
For this program, the assumption is that you are passing the path(s) of the mail directories as command line arguments. If you want to create new mail directories, pass in the `-c` flag before the paths.

This implementation doesn't calculate md5 because it requires your exact message format but you can easily add that using openssl library. Also, error checks for system and file operations are not included for brevity. You should add them in a production-level code. This code should give you a basic understanding and a starting point to create a more sophisticated maildir delivery program. 

Please replace "Test message" to the content you want. 

This program should be compiled with -lcrypto during linkage (due to openssl for md5)
Example: 
`g++ filename.cpp -lcrypto -o outputfile`
