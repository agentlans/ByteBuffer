#include "ByteBuffer.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

ByteBuffer::ByteBuffer(const std::string &str)
    : ByteBuffer(str.data(), str.size()) {}

ByteBuffer::ByteBuffer(std::size_t length)
    : data_(std::vector<std::byte>(length)) {}

ByteBuffer &ByteBuffer::operator=(const std::string &str) {
  return assign(str.data(), str.size());
}

ByteBuffer::operator std::string() const {
  return std::string(reinterpret_cast<const char *>(data_.data()),
                     data_.size());
}

std::byte &ByteBuffer::operator[](std::size_t i) { return data_[i]; }

const std::byte &ByteBuffer::operator[](std::size_t i) const {
  return data_[i];
}

std::size_t ByteBuffer::size() const noexcept { return data_.size(); }

std::size_t ByteBuffer::capacity() const noexcept { return data_.capacity(); }

void ByteBuffer::resize(std::size_t n) { data_.resize(n); }

std::istream &operator>>(std::istream &is, ByteBuffer &bb) {
  bb.data_.clear();
  std::byte b;
  while (bb.size() < bb.capacity() &&
         is.read(reinterpret_cast<char *>(&b), 1)) {
    bb.data_.push_back(b);
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, const ByteBuffer &bb) {
  return os.write(reinterpret_cast<const char *>(bb.data()), bb.size());
}

std::string ByteBuffer::hex() const {
  std::ostringstream oss;
  oss << std::hex << std::setfill('0');
  for (const auto &b : data_) {
    oss << std::setw(2) << static_cast<int>(b);
  }
  return oss.str();
}
