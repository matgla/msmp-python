#!/usr/bin/python3

from msmp_core import TcpHost
from msmp_python import MessageBroker

dir(msmp_python)

host = TcpHost("TcpHostA", 1236, "localhost", 1237)
#broker = MessageBroker()