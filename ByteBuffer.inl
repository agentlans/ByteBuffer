// Inline implementations

template <ByteSequence S>
ByteBuffer::ByteBuffer(const S &s)
    : data_(reinterpret_cast<const std::byte *>(s.data()),
            reinterpret_cast<const std::byte *>(s.data()) + s.size()) {}

template <Byte B>
ByteBuffer::ByteBuffer(const B *cstr, std::size_t length)
    : data_(reinterpret_cast<const std::byte *>(cstr),
            reinterpret_cast<const std::byte *>(cstr) + length) {}

template <ByteSequence S> ByteBuffer &ByteBuffer::operator=(const S &s) {
  return assign(s.data(), s.size());
}

template <std::size_t N> ByteBuffer &ByteBuffer::operator=(const char (&s)[N]) {
  return assign(s, N - 1); // Exclude null terminator
}

template <typename T, std::size_t N>
ByteBuffer &ByteBuffer::operator=(const T (&s)[N]) {
  return assign(s, N);
}

template <ByteSequence S> void ByteBuffer::assignTo(S &s) const {
  if (s.size() != size()) {
    throw std::length_error("ByteSequence size mismatch");
  }
  std::copy(data_.begin(), data_.end(),
            reinterpret_cast<std::byte *>(s.data()));
}

template <typename T, std::size_t N>
void ByteBuffer::assignTo(T (&s)[N]) const {
  if (N != size()) {
    throw std::length_error("Array size mismatch");
  }
  std::copy(data_.begin(), data_.end(), reinterpret_cast<std::byte *>(s));
}

template <class T> T ByteBuffer::data() noexcept {
  return reinterpret_cast<T>(data_.data());
}

template <class T> T ByteBuffer::data() const noexcept {
  return reinterpret_cast<T>(data_.data());
}

template <typename T>
ByteBuffer &ByteBuffer::assign(const T *data, std::size_t size) {
  data_.assign(reinterpret_cast<const std::byte *>(data),
               reinterpret_cast<const std::byte *>(data) + size);
  return *this;
}
