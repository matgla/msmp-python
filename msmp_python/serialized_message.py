from struct import pack

class SerializedMessage():
    def __init__(self):
        self.data = bytearray()

    def compose_u8(self, value):
        self.data.append(value)
        return self

    def compose_u16(self, value):
        serialized = pack("!H", value)
        self.data += serialized
        return self

    def compose_u32(self, value):
        serialized = pack("!I", value)
        self.data += serialized
        return self

    def compose_string(self, string):
        self.data.extend(string.encode("utf-8"))
        self.data.append(0)
        return self

    def decompose_float(self, value):
        serialized = pack("!f", value)
        self.data += serialized
        return self

    def build(self):
        return self.data