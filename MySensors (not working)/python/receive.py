import time
import serial
import string
from subprocess import *
import os


# Configure serial port
serialRead = serial.Serial(
    port='/dev/ttyACM0',
)

count = 0
while serialRead.open :

    line = serialRead.readline()
    print str(count) + " Node says : " + line
   
    count+=1

ser.close()
    
