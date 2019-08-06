from struct import unpack, calcsize, error

def unpack_asciiz(fmt, data):
    pos = fmt.find('z')
    while pos >= 0:
        start = calcsize(fmt[:pos])
        length = data[start:].find(0)
        fmt = '%s%dsx%s' % (fmt[:pos], length, fmt[pos+1:])
        pos = fmt.find('z')
    return unpack(fmt, data)

class MessageDeserializer():
    def __init__(self, data):
        self.deserializing_format = "!"
        self.data = bytearray(data)

    def drop_u8(self):
        self.data = self.data[1:]

    def drop_u16(self):
        self.data = self.data[2:]

    def drop_u32(self):
        self.data = self.data[4:]

    def decompose_u8(self):
        byte = self.data[0]
        self.data = self.data[1:]
        return byte

    def decompose_i8(self):
        byte = self.data[0]
        self.data = self.data[1:]
        return byte

    def decompose_u16(self):
        value = unpack("!H", self.data[:2])[0]
        self.data = self.data[2:]
        return value

    def decompose_i16(self):
        value = unpack("!h", self.data[:2])[0]
        self.data = self.data[2:]
        return value

    def decompose_u32(self):
        value = unpack("!I", self.data[:4])[0]
        self.data = self.data[4:]
        return value

    def decompose_i32(self):
        value = unpack("!i", self.data[:4])[0]
        self.data = self.data[4:]
        return value

    def decompose_string(self):
        termination_position = self.data.find(0)
        if termination_position < 0:
            return ""
        termination_position += 1
        value = unpack_asciiz("!z", self.data[:termination_position])[0]

        self.data = self.data[:termination_position]
        return value.decode("utf-8")

    def decompose_float(self):
        value = unpack("!f", self.data[:4])[0]
        return value

