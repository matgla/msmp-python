#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
using namespace boost::python;

struct Hello
{
    Hello(std::string msg): msg(msg) {}
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

BOOST_PYTHON_MODULE(pylib)
{
    class_<Hello>("Hello", init<std::string>())
        .def("greet", &Hello::greet)
        .def("set", &Hello::set);
}