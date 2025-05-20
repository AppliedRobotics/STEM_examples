
from dynamixel_sdk import *     
import time
import os

PROTOCOL_VERSION = 1.0 
DXL_ID1 = 1
DXL_ID2 = 2
DXL_ID3 = 3
DXL_ID4 = 4
DXL_ID5 = 5
DXL_ID6 = 6
MOD_ID = 23

BAUDRATE = 1000000
DEVICENAME = '/dev/ttyS2'
OPERATING_MODE_REG = 11
POSITION_CONTROL_MODE = 3
GOAL_POSITION = 116
TORQUE_REG = 64
MOVING_SPEED = 112

os.system("rs485 /dev/ttyS2 1")

portHandler = PortHandler(DEVICENAME)
packetHandler = PacketHandler(PROTOCOL_VERSION)

if portHandler.openPort():
    print("Succeeded to open the port")
else:
    print("Failed to open the port")
    quit()

if portHandler.setBaudRate(BAUDRATE):
    print("Succeeded to change the baudrate")
else:
    print("Failed to change the baudrate")
    quit()


for i in range(1, 7, 1):
    packetHandler.write1ByteTxRx(portHandler, i, OPERATING_MODE_REG, POSITION_CONTROL_MODE)
    packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 1)
    packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 100)
 
time.sleep(3.0)


def button():
    data, dxl_comm_result, dxl_error = packetHandler.read1ByteTxRx(portHandler, MOD_ID, 27)
    print(data)
    time.sleep(0.1)
    if data == 1:
        for i in range(1, 7, 1):
            packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 0)
        while data == 1:
            data, dxl_comm_result, dxl_error = packetHandler.read1ByteTxRx(portHandler, MOD_ID, 27)
            print(data)
            time.sleep(0.5)
            if data == 0:
                for i in range(1, 7, 1):
                    packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 100)
                time.sleep(0.5)
                break
                
                   
try:
    while 1:

        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 9000)
        time.sleep(3.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9800)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 9471)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 6049)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8354)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 9000)
        time.sleep(3.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9800)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 9471)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 6049)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8354)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 5200)
        time.sleep(1.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8800)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 9471)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 6049)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8354)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 5200)
        time.sleep(1.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4188)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8310)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 12466)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8312)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 16113)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 5200)
        time.sleep(1.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 16383)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 16383)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 5200)
        time.sleep(1.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 6584)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 15104)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 10335)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 16221)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 5200)
        time.sleep(3.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 6584)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 15104)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 10335)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 16221)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 9000)
        time.sleep(2.0)
        
        button()

        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7584)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 15104)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 10335)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 16221)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 9000)
        time.sleep(1.0)
        
        button()
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4177)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8310)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 12466)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8312)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 16113)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 9000)
        time.sleep(1.0)
        
        button()
        
except KeyboardInterrupt:
    pass
finally:
    for i in range(1, 7, 1):
        packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 0)
    portHandler.closePort()  
