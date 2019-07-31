from msmp_core import IConnection

def dummy():
    pass

class MessageBroker(object):
    def __init__(self):
        self.connections = []
        self.handlers = []

    def add_connection(self, connection):
        self.connections.append(connection)
        connection.onData(self.handle_data)

    def add_handler(self, handler):
        self.handlers.append(handler)

    def publish(self, message, on_success = dummy, on_failure = dummy):
        for connection in self.connections:
            connection.send(message, on_success, on_failure)

    def handle_data(self, id, payload):
        print("Received message with id: ")

