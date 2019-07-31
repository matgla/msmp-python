from struct import unpack, calcsize, pack, error

import sys


def unpack_asciiz(fmt, data):
    print("fupa")
    pos = fmt.find('z')
    print("crash")
    while pos >= 0:
        print (fmt[pos])
        start = calcsize(fmt[:pos])

        length = data[start:].find(0)
        fmt = '%s%dsx%s' % (fmt[:pos], length, fmt[pos+1:])
        pos = fmt.find('z')
        print (pos)
    return unpack(fmt, data)

class MessageAHandler(object):
    def match(self, id, payload):
        if id == 1:
            return True
        return False

    def handle(self, payload):
        l = []
        for byte in payload:
            print(byte, end='')
            l.append(l)
        print("")
        b = bytearray(payload)
        print(b)
        try:
            #print(pack('!BBi15c', 1, 1, 177, "TestingMessage"))
            #print(len(b))
            print(unpack_asciiz("!BBiz", b))
        except error as msg:
            print(msg)
        except:
            print(sys.exc_info()[0])