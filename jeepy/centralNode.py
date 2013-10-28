#!/usr/bin/python

#
# Needs pySerial: http://pythonhosted.org/pyserial/
# Install pySerial on Mac: $ sudo easy_install -U pyserial
#

import serial

ser = serial.Serial('/dev/tty.usbserial-A1014IM4', 57600)

def parseLine(line):
    print "Received: " + line.strip()

    # Example: OK 2 156 149 213 0
    #             ^ -------------
    #       node_id      ^
    #                data bytes
    #
    data = line.split(" ")

    if data[0] == 'OK':
        result = { }

        result['node_id'] = str(int(data[1]) & 0x1f)

        dataByte1 = int(data[2])
        dataByte2 = int(data[3])
        dataByte3 = int(data[4])
        dataByte4 = int(data[5])

        temperature = ((256 * (dataByte4 & 3)) + dataByte3)
        if temperature > 512:
            # negative value
            temperature = temperature - 1024

        result['light']       = (dataByte1 * 100) / 255
        result['motion']      = dataByte2 & 1
        result['humidity']    = dataByte2 >> 1
        result['low_battery'] = (dataByte4 >> 2) & 1
        result['temperature'] = float(temperature) / 10

        return result
    else:
        return

def handleData(data):
    print "Decoded: "
    print "  node_id: " + data['node_id']
    print "  temperature: " + str(data['temperature'])
    print "  humidity: " + str(data['humidity'])
    print "  light: " + str(data['light'])
    print "  motion: " + str(data['motion'])
    print "  low_battery: " + str(data['low_battery'])

while(True):
    line = ser.readline()

    data = parseLine(line)

    if data:
        handleData(data)
