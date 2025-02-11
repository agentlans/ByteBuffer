#include "ByteBuffer.hpp"
#include <sstream>
#include <vector>

// Compile with g++ -std=c++20 *.cpp

int main() {

  {
    // From a string
    ByteBuffer bb1("Hello, World!");

    // From a byte array
    std::byte arr[] = {std::byte{0x48}, std::byte{0x65}, std::byte{0x6C},
                       std::byte{0x6C}, std::byte{0x6F}};
    ByteBuffer bb2(arr, sizeof(arr));

    // From a vector of bytes
    std::vector<std::byte> vec = {std::byte{0x57}, std::byte{0x6F},
                                  std::byte{0x72}, std::byte{0x6C},
                                  std::byte{0x64}};
    ByteBuffer bb3(vec);

    std::cout << bb3 << std::endl;
  }

  {
    ByteBuffer bb("Hello");
    std::byte b = bb[0];     // Access first byte
    bb[0] = std::byte{0x41}; // Modify first byte

    std::string str = static_cast<std::string>(bb); // Convert to string

    std::cout << str << std::endl;
  }

  {
    ByteBuffer bb(10); // Set up a buffer with 10 bytes
    std::cin >> bb;    // Read from input stream until the buffer is full
    std::cout << bb << std::endl; // Write to output stream
  }

  {
    ByteBuffer bb("Hello, World!");
    std::cout << bb.hex() << std::endl;  // Print hexadecimal representation
    std::cout << bb.size() << std::endl; // Print size of the buffer
  }
}