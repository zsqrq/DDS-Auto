#ifndef _FAST_DDS_EXAMPLE_HELLOWORLD_H_
#define _FAST_DDS_EXAMPLE_HELLOWORLD_H_

#include <array>
#include <bitset>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "fastcdr/cdr/fixed_size_string.hpp"
#include "fastcdr/xcdr/optional.hpp"

namespace eprosima::fastcdr {
class Cdr;
class CdrSizeCalculator;
}  // namespace eprosima::fastcdr

class HelloWorld {
 public:
  HelloWorld();

  ~HelloWorld();

  HelloWorld(const HelloWorld& x);

  HelloWorld(HelloWorld&& x) noexcept;

  HelloWorld& operator=(const HelloWorld& x);

  HelloWorld& operator=(HelloWorld&& x) noexcept;

  bool operator==(const HelloWorld& x) const;

  bool operator!=(const HelloWorld& x) const;

  void index(uint32_t _index);

  uint32_t index() const;

  uint32_t& index();

  void message(const std::string& _message);

  void message(std::string&& _message);

  const std::string& message() const;

  std::string& message();

 private:
  uint32_t m_index{0};
  std::string m_message;
};

#endif