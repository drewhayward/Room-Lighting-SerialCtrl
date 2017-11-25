from time import sleep
import serial
import json

class LightController:
    def __init__(self):
        self.lightmap = dict()
        self.commandmap = dict()

        # Reads local files for serial command mapping
        self._getLightMap()
        self._getCommandMap()

        # Load saved light states
        self._getState()
        self.loadFromState()

        self.ser = serial.Serial()
        self.ser.baudrate = 9600
        self.ser.port = '/dev/ttyACM0'
        try:
            self.ser.open()
        except:
            print('Failed to open serial port')


    def fadeStrip(self,strip):
        for i in range (256):
            hexString = ""
            hexString += self.commandmap['color']
            hexString += self.lightmap[strip]

            levelCommand = bytearray.fromhex(hexString)
            level = i.to_bytes(1, byteorder='big')

            levelCommand.join(level)
            levelCommand.join(level)
            levelCommand.join(level)
            self.ser.write(levelCommand)
            sleep(.05)


    def setLightState(self, light, state):
        # Update the state
        if light in self.lightmap:
            if state:
                self.state['lights'][light] = 1
            else:
                self.state['lights'][light] = 0
        self._saveState()

        # Build serial command from arguments
        hexString = ""
        if(state):
            hexString += self.commandmap['on']
        else:
            hexString += self.commandmap['off']
        hexString += self.lightmap[light]

        # Cast hex to bytes and send command
        command = bytearray.fromhex(hexString)
        try:
            self.ser.write(command)
        except:
            print('Write failed. Serial port isn\'t open')


    def setStripColor(self, strip, color):
        # Update the state
        if(strip in self.lightmap):
            self.state['strips'][strip] = color
        self._saveState()

        # Build serial command from arguments
        hexString = ""
        hexString += self.commandmap['color']
        hexString += self.lightmap[strip]
        hexString += color.strip('# \t\n')

        # Cast hex to bytes and send command
        command = bytearray.fromhex(hexString)
        print(command)
        try:
            self.ser.write(command)
        except:
            print('Write failed. Serial port isn\'t open')


    def loadFromState(self):
        # Load strip colors
        for strip, color in self.state['strips'].items():
            self.setStripColor(strip,color)

        # Load light states
        for light, state in self.state['lights'].items():
            self.setLightState(light,state)


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

    def _saveState(self):
        try:
            f = open('state.json','w')
            json.dump(self.state, f, sort_keys=True, indent=4)
        except:
            print('Error writing state')

    def _getState(self):
        # Load state saved light state
        self.state = dict()
        self.state['lights'] = dict()
        self.state['strips'] = dict()
        try:
            fp = open('state.json', 'r')
            self.state = json.load(fp)
        except:
            print('State file not found, loading defaults')
            try:
                fp = open('default.json', 'r')
                self.state = json.load(fp)
            except:
                print('Default state not found, arduino defaults will be loaded')
