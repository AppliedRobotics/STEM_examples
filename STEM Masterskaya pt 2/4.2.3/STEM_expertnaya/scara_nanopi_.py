from dynamixel_sdk import * 
import os
import time
PROTOCOL_VERSION = 1.0 
DXL_ID1 = 1
DXL_ID2 = 2
DXL_ID3 = 3
DXL_ID4 = 4
RGB_ID = 21
COLOR_ID = 5
BAUDRATE = 1000000
DEVICENAME = '/dev/ttyS2'
OPERATING_MODE_REG = 11
POSITION_CONTROL_MODE = 3
TORQUE_REG = 64
MOVING_SPEED = 112
GOAL_POSITION = 116

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


for i in range(1, 5, 1):
    packetHandler.write1ByteTxRx(portHandler, i, OPERATING_MODE_REG, POSITION_CONTROL_MODE)
    packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 1)
    packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 100)
    
try:
    while 1:

        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8200)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8200)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8200)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8200)
        time.sleep(3.0)

        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 11449)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 4887)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 4234)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 4125)
        
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 11453)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 4884)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 4225)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8058)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)

        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 7708)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8128)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8831)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 7924)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257) + "G: " + str(G / 257)+ "B: " + str(B / 257))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 7706)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8134)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8830)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 4728)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 7708)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 8128)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8831)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 7924)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 9221)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 3416)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7974)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8512)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 9272)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 3410)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7974)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 4600)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257) 
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 9306)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 3407)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 7972)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8310)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)
        
        packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 12517)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 3449)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 8652)
        packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8310)
        
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, G // 257)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, R // 257)  
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, B // 257)
        time.sleep(4.0)

       
except KeyboardInterrupt:
    pass
finally:
    for i in range(1, 5, 1):
        packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 0)

    portHandler.closePort()  