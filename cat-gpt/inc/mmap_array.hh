#include <string>
#include <memory>
#ifndef mmap_array_hh
#define mmap_array_hh mmap_array_hh

class mmap_array {
private:
    struct mmap_deleter {
        size_t size;
        void operator()(char* ptr) const;
    };

    std::shared_ptr<char> data_; // Reference-counted pointer to mmap'd memory
    size_t size_;               // Size of the file

public:
    // Constructor: Opens the file, mmaps it, and closes the file descriptor
    explicit mmap_array(const std::string& filename);
    // Const access for element at a given index (bounds checking)
    char  operator[](size_t index) const;


    // Get the size of the array
    size_t size() const {
        return size_;
    }

    const char *data() const {
      return data_.get();
    };
    const char *begin() const {
      return data();
    };
    const char *end() const {
      return data()+size();
    };
    char front() {
      return (*this)[0];
    };
    char back() {
      return (*this)[size()-1];
    };

    // Enable copy and assignment (shared_ptr handles reference counting)
    mmap_array(const mmap_array&) = default;
    mmap_array& operator=(const mmap_array&) = default;

    // Move semantics (shared_ptr handles transfer of ownership)
    mmap_array(mmap_array&&) noexcept = default;
    mmap_array& operator=(mmap_array&&) noexcept = default;
};

#endif
