#ifndef BYTE_BUFFER_H
#define BYTE_BUFFER_H

#include <concepts>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// Concepts
template <typename T>
concept Byte = sizeof(T) == 1 && std::is_trivial_v<T>;

template <typename T>
concept ByteSequence = requires(T t) {
  { t.data() } -> std::convertible_to<const std::byte *>;
  { t.size() } -> std::convertible_to<std::size_t>;
  requires std::contiguous_iterator<decltype(std::begin(t))>;
  requires std::same_as<std::byte,
                        std::remove_cvref_t<decltype(*std::begin(t))>>;
};

class ByteBuffer {
public:
  // Constructors
  ByteBuffer() = default;

  template <ByteSequence S> explicit ByteBuffer(const S &s);

  explicit ByteBuffer(const std::string &str);

  template <Byte B> ByteBuffer(const B *cstr, std::size_t length);

  ByteBuffer(std::size_t length);

  // Assignment operators
  ByteBuffer &operator=(const std::string &str);
  ByteBuffer &operator=(const ByteBuffer &) = default;
  ByteBuffer &operator=(ByteBuffer &&) noexcept = default;

  template <ByteSequence S> ByteBuffer &operator=(const S &s);

  template <std::size_t N> ByteBuffer &operator=(const char (&s)[N]);

  template <typename T, std::size_t N> ByteBuffer &operator=(const T (&s)[N]);

  // Assignment methods
  template <ByteSequence S> void assignTo(S &s) const;

  template <typename T, std::size_t N> void assignTo(T (&s)[N]) const;

  // Conversion operator
  explicit operator std::string() const;

  // Accessors
  std::byte &operator[](std::size_t i);
  const std::byte &operator[](std::size_t i) const;

  // Size and capacity
  [[nodiscard]] std::size_t size() const noexcept;
  [[nodiscard]] std::size_t capacity() const noexcept;
  void resize(std::size_t n);

  // Data access
  template <class T = std::byte *> T data() noexcept;

  template <class T = const std::byte *> T data() const noexcept;

  // Stream operators
  friend std::istream &operator>>(std::istream &is, ByteBuffer &bb);
  friend std::ostream &operator<<(std::ostream &os, const ByteBuffer &bb);

  // Utility methods
  [[nodiscard]] std::string hex() const;

private:
  std::vector<std::byte> data_;

  template <typename T> ByteBuffer &assign(const T *data, std::size_t size);
};

#include "ByteBuffer.inl"

#endif // BYTE_BUFFER_H
