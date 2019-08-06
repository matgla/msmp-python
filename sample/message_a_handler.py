from struct import unpack, calcsize, pack, error

import sys

from message_a import MessageA


class MessageAHandler(object):
    def match(self, id, payload):
        if id == 1:
            return True
        return False

    def handle(self, payload):
        msg = MessageA.deserialize(payload)
        print(msg)