#!/usr/bin/python3

import msmp_python
from msmp_python import MessageBroker
from msmp_core import TcpHost
from message_a_handler import MessageAHandler

def connection_callback():
    print("Peer is connected!")

host = TcpHost("TcpHostA", 1236, "localhost", 1237)
broker = MessageBroker()

broker.add_connection(host.getConnection())
handler = MessageAHandler()
broker.add_handler(handler)

host.onConnected(connection_callback)

host.start()

