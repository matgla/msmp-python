#include <string>

struct Hello
{
    Hello(std::string msg);
    void set(std::string msg);
    std::string greet();
    std::string msg;
};