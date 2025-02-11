# ByteBuffer

## Description

ByteBuffer is a C++ class that provides a flexible and efficient way to handle byte sequences. It offers a variety of constructors, assignment operators, and utility methods for working with byte data. The class is designed with modern C++ features, including concepts and templates, to ensure type safety and performance.

## Features

- Supports various input types including ByteSequence concepts, std::string, and C-style strings
- Provides easy conversion to and from std::string
- Allows access to individual bytes using array subscript operator
- Supports resizing and capacity management
- Offers hex string representation of the byte data
- Compatible with input and output streams

## Requirements

- C++20 compatible compiler
- Standard C++ library

## Usage

### Including the Header

```
#include "ByteBuffer.hpp"
```

### Creating a ByteBuffer

```
// From a string
ByteBuffer bb1("Hello, World!");

// From a byte array
std::byte arr[] = {std::byte{0x48}, std::byte{0x65}, std::byte{0x6C},
                   std::byte{0x6C}, std::byte{0x6F}
                  };
ByteBuffer bb2(arr, sizeof(arr));

// From a vector of bytes
std::vector<std::byte> vec = {std::byte{0x57}, std::byte{0x6F},
                              std::byte{0x72}, std::byte{0x6C},
                              std::byte{0x64}
                             };
ByteBuffer bb3(vec);

std::cout << bb3;
```

### Accessing and Modifying Data

```
ByteBuffer bb("Hello");
std::byte b = bb[0];     // Access first byte
bb[0] = std::byte{0x41}; // Modify first byte

std::string str = static_cast<std::string>(bb); // Convert to string

std::cout << str << std::endl;
```

### Using with Streams

```
ByteBuffer bb(10); // Set up a buffer with 10 bytes
std::cin >> bb;    // Read from input stream until the buffer is full
std::cout << bb // Write to output stream
```

### Utility Methods

```
ByteBuffer bb("Hello, World!");
std::cout << bb.hex();  // Print hexadecimal representation
std::cout << bb.size(); // Print size of the buffer
```

## Author, Licence

Copyright :copyright: 2025 Alan Tseng

MIT Licence
