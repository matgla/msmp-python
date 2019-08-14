from msmp_python import MessageDeserializer
from msmp_python import SerializedMessage

from struct import error

import sys

class MessageA():
    def __init__(self):
        self.id = 1
        self.value = 0
        self.name = ""

    def serialize(self):
        try:
            message = SerializedMessage()
            serialized = message.compose_u8(self.id).compose_u32(self.value).compose_string(self.name)
        except TypeError as err:
            print(err)
        except:
            print("Unexpected error:", sys.exc_info()[0])
        return serialized.build()

    def deserialize(payload):
        reader = MessageDeserializer(payload)
        msg = MessageA()
        try:
            reader.drop_u8()
            msg.value = reader.decompose_i32()
            msg.name = reader.decompose_string()

        except error as err:
            print (err)
        return msg

    def __repr__(self):
        return str("MessageA -> { value: " + str(self.value) + ", name: " + str(self.name) + " }")