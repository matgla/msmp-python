#include "msmp_api/tcp/tcp_host.hpp"
#include "msmp_api/i_connection.hpp"

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include <boost/python/list.hpp>
#include <boost/python/call.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace boost::python;

template<typename T>
std::vector<T> list_to_vector(const object& iterable)
{
    return std::vector<T>(stl_input_iterator<T>(iterable),
                            stl_input_iterator<T>());
}

class IConnectionWrap : public msmp_api::IConnection, public wrapper<msmp_api::IConnection>
{
    public:
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
    class_<std::vector<uint8_t>>("MyList")
        .def(vector_indexing_suite<std::vector<uint8_t>>() );

    class_<msmp_api::TcpHost>("TcpHost", init<std::string, uint16_t, std::string, uint16_t>())
        .def("start", &msmp_api::TcpHost::start)
        .def("onConnected", +[](msmp_api::TcpHost& self, object o, object callback) {
            self.onConnected([o, callback] {
                call<void>(callback.ptr());
            });
        })
        .def("getConnection", &msmp_api::TcpHost::getConnection);

    class_<IConnectionWrap, boost::noncopyable>("IConnection")
        .def("start", pure_virtual(&msmp_api::IConnection::start))
        .def("stop", pure_virtual(&msmp_api::IConnection::stop))
        .def("handlePeerConnected", pure_virtual(&msmp_api::IConnection::handlePeerConnected))
        .def("peerDisconnected", pure_virtual(&msmp_api::IConnection::peerDisconnected))
        .def("onData", +[](msmp_api::IConnection& self, object o, object callback) {
            self.onData([o, callback](uint8_t id, const std::vector<uint8_t>& payload) {
                call<void>(callback.ptr(), id, payload);
            });
        })
        .def("onConnected", +[](msmp_api::IConnection& self, object o, object callback) {
            self.onConnected([o, callback] {
                call<void>(callback.ptr());
            });
        })
        .def("send", +[](msmp_api::IConnection& self, list data, object on_success, object on_failure) {
            self.send(list_to_vector<uint8_t>(data), on_success, on_failure);
        });

    register_ptr_to_python<std::shared_ptr<msmp_api::IConnection>>();
}