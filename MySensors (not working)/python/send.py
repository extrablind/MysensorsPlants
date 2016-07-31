import time
import serial
import string
from subprocess import *
import os


# Configure serial port
serialWrite = serial.Serial(
    port='/dev/ttyACM0',
)

count = 0
while True :
    if(serialWrite.writable):
        # mySensor protocol : node-id;child-sensor-id;message-type;ack;sub-type;payload\n
        messageToSend = "111;1;1;1;2;1;\n"
        print  str(count) +" - Python Send ON "+ messageToSend;
        serialWrite.write(messageToSend);
        time.sleep(3)
        # Off
        messageToSend = "111;1;1;1;2;0;\n"
        print  str(count) +" - Python Send OFF "+ messageToSend;
        serialWrite.write(messageToSend);
        time.sleep(3)
    
    if(count == 100):
        exit()
    
    count+=1
    
ser.close()
    
