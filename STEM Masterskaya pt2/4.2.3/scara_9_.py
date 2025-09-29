from dynamixel_sdk import *     
import time
import os

PROTOCOL_VERSION = 1.0 

DXL_ID1 = 1
DXL_ID2 = 2
DXL_ID3 = 3
DXL_ID4 = 4
COLOR_ID = 5

BAUDRATE = 1000000
DEVICENAME = '/dev/ttyS2'

CW_ANGEL_LIMIT = 6
CCW_ANGEL_LIMIT = 8
GOAL_POSITION = 30
TORQUE_REG = 24
MOVING_SPEED = 32

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
    packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 1)
    packetHandler.write2ByteTxRx(portHandler, i, CW_ANGEL_LIMIT, 0)
    packetHandler.write2ByteTxRx(portHandler, i, CCW_ANGEL_LIMIT, 1023)
    packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 80)
    
time.sleep(3.0)    
try:
    while 1:

        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 524)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 807)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 556)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 484)
        time.sleep(4.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 502)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 816)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 532)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 193)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 502)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 816)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 532)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 476)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 762)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 528)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 258)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 476)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 762)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 528)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 557)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 547)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 551)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 225)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 557)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 547)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 551)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 522)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 528)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 561)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 240)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 522)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 528)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 561)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 514)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 486)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 464)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 240)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 514)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 486)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 464)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 498)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 453)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 368)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 253)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 498)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 453)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 368)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 518)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 346)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 394)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 239)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 518)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 346)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 394)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 538)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 206)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 491)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 239)
        time.sleep(4.0)
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, COLOR_ID, 42, 50)
        R, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 26)
        G, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 28)
        B, dxl_comm_result, dxl_error = packetHandler.read2ByteTxRx(portHandler, COLOR_ID, 30)
        print("R: " + str(R / 257.0) + "G: " + str(G / 257.0)+ "B: " + str(B / 257.0))
        packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 538)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 206)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 491)
        packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 480)
        time.sleep(2.0)
        
except KeyboardInterrupt:
    pass
finally:
    for i in range(1, 5, 1):
        packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 0)
    portHandler.closePort()          