#!/usr/bin/python3

import msmp_python
from msmp_python import MessageBroker
from msmp_core import TcpHost
from message_a_handler import MessageAHandler
from message_a import MessageA

class Main():
    def __init__(self):
        self.host = TcpHost("TcpHostA", 1236, "localhost", 1237)
        self.broker = MessageBroker()

        self.broker.add_connection(self.host.getConnection())
        handler = MessageAHandler()
        self.broker.add_handler(handler)

        self.host.onConnected(self, self.connection_callback)

    def start(self):
        self.host.start()

    def connection_callback(self):
        msg = MessageA()
        msg.value = 1902
        msg.name = "PythonThere"
        self.broker.publish(msg)


m = Main()
m.start()

