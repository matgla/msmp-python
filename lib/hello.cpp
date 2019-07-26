#include "hello.hpp"

Hello::Hello(std::string msg): msg(msg) {}
void Hello::set(std::string msg) { this->msg = msg; }
std::string Hello::greet() { return msg; }