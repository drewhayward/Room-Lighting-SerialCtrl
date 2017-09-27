#import serial

class LightController:
    def __init__(self):
        self.lightmap = dict()
        self.commandmap = dict()
        #self.ser = serial.Serial()
        #self.ser.baudrate = 9600
        #self.ser.port = '/dev/ttyACM0'
        #self.ser.port.open()

    def getLightMap(self):
        f = open('lightmap.txt', 'r')
        for line in f:
            name, number = line.strip().split(':')
            self.lightmap[name] = number


    def getCommandMap(self):
        f = open('commandMapping.txt', 'r')
        for line in f:
            command, number = line.strip().split(':')
            self.commandmap[command] = number

        

light = LightController()

light.getCommandMap()
