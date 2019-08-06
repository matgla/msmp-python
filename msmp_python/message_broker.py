from msmp_core import IConnection
import sys

def dummy():
    pass

class MessageBroker(object):
    def __init__(self):
        self.connections = []
        self.handlers = []

    def add_connection(self, connection):
        self.connections.append(connection)
        self.connections[-1].onData(self, self.handle_data)

    def add_handler(self, handler):
        self.handlers.append(handler)

    def publish(self, message, on_success = dummy, on_failure = dummy):
        for connection in self.connections:
            data = message.serialize()
            try:
                connection.send(list(data), on_success, on_failure)
            except:
                print("Unexpected error:", sys.exc_info()[0])

    def handle_data(self, id, payload):
        for handler in self.handlers:
            if handler.match(id, payload):
                handler.handle(payload[1:])

