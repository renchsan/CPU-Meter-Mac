# Matt Rencher
# www.renchtech.com

# Print CPU percent to Serial
# Formatted output as a String
# Delay 3s
# TODO: should be synced with Arduino code

import time
import serial
import psutil

# ser = serial.Serial(port='/dev/cu.usbserial-1410',baudrate=115200,parity=serial.PARITY_ODD,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS)
arduino = serial.Serial('/dev/cu.usbserial-1420', 9600)

command = ""

def writeFunction():
	# command = raw_input("Type something..: ");
	time.sleep(.5)
	command = str(psutil.cpu_percent(interval=None, percpu=False))
	
	if command != "0.0":
		print command + "%"
		time.sleep(.5)
		arduino.write(command)
		writeFunction()
		
	else:
		print "Sorry...!"
		writeFunction()

time.sleep(2) #waiting the initialization...

writeFunction()