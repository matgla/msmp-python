#include "msmp_api/tcp/tcp_host.hpp"
#include "msmp_api/i_connection.hpp"

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include <boost/python/call.hpp>

#include <iostream>

using namespace boost::python;

template <typename T>
std::vector<T> to_vector(const object& iterable)
{
    return std::vector<T>(stl_input_iterator<T>(iterable), stl_input_iterator<T>());
}


template <typename T>
boost::python::list vector_to_list(const std::vector<T>& v)
{
    boost::python::object get_iter = boost::python::iterator<std::vector<T>>();
    boost::python::object iter(v);
    boost::python::list l(iter);
    return l;
}

class IConnectionWrap : public msmp_api::IConnection, public wrapper<msmp_api::IConnection>
{
    void start()
    {
        this->get_override("start")();
    }

    void stop()
    {
        this->get_override("stop")();
    }

    void handlePeerConnected()
    {
        this->get_override("handlePeerConnected")();
    }

    void peerDisconnected()
    {
        this->get_override("peerDisconnected")();
    }

    void onData(const OnDataCallbackType& callback)
    {
        this->get_override("onData")(callback);
    }

    void send(const PayloadType& payload, const CallbackType& on_success, const CallbackType& on_failure)
    {
        this->get_override("send")(payload, on_success, on_failure);
    }

    void onConnected(const CallbackType& callback)
    {
        this->get_override("onConnected")(callback);
    }
};

BOOST_PYTHON_MODULE(msmp_core)
{
    class_<msmp_api::TcpHost>("TcpHost", init<std::string, uint16_t, std::string, uint16_t>())
        .def("start", &msmp_api::TcpHost::start)
        .def("onConnected", +[](msmp_api::TcpHost& self, object o) {
            self.onConnected(o);
        })
        .def("getConnection", &msmp_api::TcpHost::getConnection);

    class_<IConnectionWrap, boost::noncopyable>("IConnection")
        .def("start", pure_virtual(&msmp_api::IConnection::start))
        .def("stop", pure_virtual(&msmp_api::IConnection::stop))
        .def("handlePeerConnected", pure_virtual(&msmp_api::IConnection::handlePeerConnected))
        .def("peerDisconnected", pure_virtual(&msmp_api::IConnection::peerDisconnected))
        .def("onData", +[](msmp_api::IConnection& self, object o) {
            self.onData([o](uint8_t id, const std::vector<uint8_t>& payload) {
                std::cerr << "here" << std::endl;
                call(o, self, id, payload);
            });
        });

    register_ptr_to_python<std::shared_ptr<msmp_api::IConnection>>();
}