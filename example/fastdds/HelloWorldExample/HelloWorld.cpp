#include "example/fastdds/HelloWorldExample/HelloWorld.h"

#include <utility>

#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/BadParamException.h"

using namespace eprosima::fastcdr::exception;

HelloWorld::HelloWorld() {}

HelloWorld::~HelloWorld() {}

HelloWorld::HelloWorld(const HelloWorld& x) {
  m_index = x.m_index;
  m_message = x.m_message;
}

HelloWorld& HelloWorld::operator=(const HelloWorld& x) {
  m_index = x.m_index;
  m_message = x.m_message;
  return *this;
}


