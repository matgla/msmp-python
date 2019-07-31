#include "msmp_api/tcp/tcp_host.hpp"
#include "msmp_api/i_connection.hpp"

#include <boost/python.hpp>

using namespace boost::python;

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
        });

    class_<IConnectionWrap, boost::noncopyable>("IConnection")
        .def("start", pure_virtual(&msmp_api::IConnection::start))
        .def("stop", pure_virtual(&msmp_api::IConnection::stop))
        .def("handlePeerConnected", pure_virtual(&msmp_api::IConnection::handlePeerConnected))
        .def("peerDisconnected", pure_virtual(&msmp_api::IConnection::peerDisconnected));
}