#include <mmap_array.hh>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdexcept>
#include <string>
#include <string.h>

using namespace std;

char mmap_array::operator[](size_t index) const
{
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_.get()[index];
};

void mmap_array::mmap_deleter::operator()(char* ptr) const
{
  if (ptr != nullptr && ptr != MAP_FAILED) {
    ::munmap(ptr, size);
  }
}
mmap_array::mmap_array(const string &filename) 
  : data_(nullptr, mmap_deleter{0}), size_(0)
{
    // Open the file
    int fd = ::open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
      throw std::runtime_error("Failed to open file: " + filename);
    }

    // Get the file size
    struct stat st;
    if (::fstat(fd, &st) == -1) {
      ::close(fd);
      throw std::runtime_error("Failed to stat file: " + filename
          +": "+strerror(errno));
    }
    size_ = static_cast<size_t>(st.st_size);
    size_t msize=size_?size_:1;
    // Memory-map the file
    char* mapped_data = static_cast<char*>(
        ::mmap(nullptr, msize, PROT_READ, MAP_PRIVATE, fd, 0));
    if (mapped_data == MAP_FAILED) {
      ::close(fd);
      throw std::runtime_error("Failed to mmap file: " + filename);
    }

    // Close the file descriptor as it's no longer needed
    ::close(fd);

    // Initialize the shared_ptr with a custom deleter
    data_ = std::shared_ptr<char>(mapped_data, mmap_deleter{size_});
  }

