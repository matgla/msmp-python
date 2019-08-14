#!/usr/bin/python3

import msmp_python
from msmp_python import MessageBroker
from msmp_core import UsartHost
from test_message_handler import TestMessageHandler
from test_message import TestMessage
import time

class Main():
    def __init__(self):
        self.host = UsartHost("TcpHostA", "Usart1")
        self.broker = MessageBroker()

        self.broker.add_connection(self.host.getConnection())
        handler = TestMessageHandler()
        self.broker.add_handler(handler)

        self.host.onConnected(self, self.connection_callback)

    def start(self):
        self.host.start()

    def connection_callback(self):
        print("Peer is connected!!!!")
        msg = TestMessage()
        msg.name = "PythonThere"
        self.broker.publish(msg)


m = Main()
m.start()

while True:
    try:
        pass
    except KeyboardInterrupt:
        break