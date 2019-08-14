from struct import unpack, calcsize, pack, error

import sys

from test_message import TestMessage


class TestMessageHandler(object):
    def match(self, id, payload):
        if id == 123:
            return True
        return False

    def handle(self, payload):
        msg = TestMessage.deserialize(payload)
        print(msg)