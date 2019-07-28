#include "msmp_api/tcp/tcp_host.hpp"

#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(msmp_core)
{
    class_<msmp_api::TcpHost>("TcpHost", init<std::string, uint16_t, std::string, uint16_t>())
        .def("start", &msmp_api::TcpHost::start)
        .def("onConnected", +[](msmp_api::TcpHost& self, object o) {
            self.onConnected(o);
        });
}