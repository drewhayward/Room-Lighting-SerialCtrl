import serial

class LightController:
    def __init__(self):
        self.lightmap = dict()
        self.commandmap = dict()

        # Reads local files for serial command mapping
        self._getLightMap()
        self._getCommandMap()
        self.ser = serial.Serial()
        self.ser.baudrate = 9600
        self.ser.port = '/dev/ttyACM0'
        self.ser.open()

    def setLightState(self, light, state):
        # Build serial command from arguments
        hexString = ""
        if(state):
            hexString += self.commandmap['on']
        else:
            hexString += self.commandmap['off']
        hexString += self.lightmap[light]

        # Cast hex to bytes and send command
        command = bytes.fromhex(hexString)
        self.ser.write(command)

    def setStripColor(self, strip, color):
        # Build serial command from arguments
        hexString = ""
        hexString += self.commandmap['color']
        hexString += self.lightmap[strip]
        hexString += color.strip('# \t\n')

        # Cast hex to bytes and send command
        command = bytes.fromhex(hexString)
        self.ser.write(command)

    def _getLightMap(self):
        f = open('lightmap.txt', 'r')
        for line in f:
            name, number = line.strip().split(':')
            self.lightmap[name] = number

        print(self.lightmap)

    def _getCommandMap(self):
        f = open('commandMapping.txt', 'r')
        for line in f:
            command, number = line.strip().split(':')
            self.commandmap[command] = number
