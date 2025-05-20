
from dynamixel_sdk import *     
import time

PROTOCOL_VERSION = 1.0 
DXL_ID1 = 1
DXL_ID2 = 2
DXL_ID3 = 3
DXL_ID4 = 4
DXL_ID5 = 5
DXL_ID6 = 6
RGB_ID = 21
BAUDRATE = 1000000
DEVICENAME = '/dev/ttyS2'
OPERATING_MODE_REG = 11
POSITION_CONTROL_MODE = 3
GOAL_POSITION = 116
TORQUE_REG = 64
MOVING_SPEED = 112

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
    
print("Setting the starting position")

packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)

time.sleep(3.0)

error = '0'

    
def firstMove():
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7020)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8800)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 11300)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
    
    time.sleep(2.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7020)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8800)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 11300)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(2.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(2.0)

    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(3.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7020)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8800)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 11300)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(2.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7020)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8800)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 11300)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
    
    time.sleep(2.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
    
    time.sleep(2.0)
    
    
def secondMove():
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
    
    time.sleep(3.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
    
    time.sleep(3.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7020)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8800)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 11300)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
    
    time.sleep(2.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7020)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8800)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 11300)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(2.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4200)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(2.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 6400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(2.0)
    
    for i in range(1, 7, 1):
        packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 200)
        
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, 0)

    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 6400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7020)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 1000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
    
    time.sleep(1.0)
  
    
def stop_crazy():


    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, 0)
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, 200)
    print("Switch to manual mode")
    print("Return to the starting position")
    for i in range(1, 7, 1):
        packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 100)
    time.sleep(3.0)
    
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
    
    time.sleep(3.0)
 

def crazy():


    while 1:
        
        try:
            packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 7800)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8900)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 2600)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
        
            time.sleep(1.0)
        
            packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 7800)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8900)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 4600)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)

            time.sleep(1.0)
            
        
            for i in range(1, 7, 1):
                packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 230)
        
            packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 11000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 6900)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 4600)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 12000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
        
            time.sleep(1.0)

            packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 9000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 6900)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 4600)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 9000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
        
            time.sleep(1.0)

            for i in range(1, 7, 1):
                packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 230)

        
            packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 10000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 6900)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 4600)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 6000)
        
            time.sleep(1.0)

            packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 13000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 6900)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 4600)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 9000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 12000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
        
            time.sleep(1.0)

        except KeyboardInterrupt:
            break
        
        

try:
    while 1:
        
        
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, 0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, 200)
        print("The manipulator is ready for operation. To get started, enter the 'start' command")
        
        mode = input()
        error = '0'
        
        if mode == "start":
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, 200)
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, 100)
            firstMove()
            secondMove()
            
            print("ERROR")
            print("Press ctrl + C")
            crazy()
            stop_crazy()

        else:
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, 0)
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, 200)
            while error != 'manual':
                print("ERROR")
                print("To switch to manual mode, enter the 'manual' command")
                error = input()
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, 0)
            error = '0'

            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, 200)
            
            for i in range(1, 7, 1):
                packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 100)

            print("Switch to manual mode")
            print("Return to the starting position")
            time.sleep(5.0)
        
            packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8192)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 7400)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7500)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 12000)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 8192)
            packetHandler.write4ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 8192)
            
            time.sleep(3.0)

except KeyboardInterrupt:
    pass
finally:
    for i in range(1, 7, 1):
        packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 0)

    portHandler.closePort()  
