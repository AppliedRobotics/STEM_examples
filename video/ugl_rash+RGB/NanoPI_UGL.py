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
CW_ANGEL_LIMIT = 6
CCW_ANGEL_LIMIT = 8
GOAL_POSITION = 30
TORQUE_REG = 24
MOVING_SPEED = 32
error = '0'

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
    packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 1)
    packetHandler.write2ByteTxRx(portHandler, i, CW_ANGEL_LIMIT, 0)
    packetHandler.write2ByteTxRx(portHandler, i, CCW_ANGEL_LIMIT, 1023)
    packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 70)
    
print("Setting the starting position")
packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 501)
packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 462)
packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
time.sleep(3.0)

def firstMove():
    # наклон вперед
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 501)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 420)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 549)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 706)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
    time.sleep(2.0)
    # сжатие
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 501)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 420)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 549)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 706)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 680)
    time.sleep(2.0)
    # движение назад
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 501)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 680)
    time.sleep(2.0)
    # поврот
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 680)
    time.sleep(3.0)
    # наклон вперед
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 420)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 549)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 706)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 680)
    time.sleep(2.0)
    # расжатие
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 420)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 549)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 706)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
    time.sleep(2.0)
    # движение назад
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
    time.sleep(2.0)
    
def secondMove():
    # возвращение в начальную позицию
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 501)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
    time.sleep(4.0)
    # опять поворот за кубиком
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
    time.sleep(3.0)
    # наклон
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 420)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 549)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 706)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
    time.sleep(2.0)
    # сжатие
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 420)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 549)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 706)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 700)
    time.sleep(2.0)
    # движение назад
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 162)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 700)
    time.sleep(2.0)
    # поворот
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 400)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 700)
    time.sleep(2.0)

    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, 0)
    for i in range(1, 7, 1):
        packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 120)    
    
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 400)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 430)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 128)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 700)
    time.sleep(1.0)
  
def stop_crazy():
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 27, 0)
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, 200)
    print("Switch to manual mode")
    print("Return to the starting position")
    for i in range(1, 7, 1):
        packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 70)
    time.sleep(3.0)
    
    packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 501)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 452)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 468)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
    packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
    time.sleep(3.0)
 

def crazy():
    while 1:
        try:
            packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 487)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 556)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 300)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 300)
            time.sleep(1.0)
        
            packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 487)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 556)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 387)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 375)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 200)
            time.sleep(1.0)
            
            for i in range(1, 7, 1):
                packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 150)
        
            packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 687)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 431)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 287)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 749)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
            time.sleep(1.0)

            packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 562)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 431)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 387)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 562)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 600)
            time.sleep(1.0)

            for i in range(1, 7, 1):
                packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 120)

            packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 624)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 431)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 387)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 375)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 600)
            time.sleep(1.0)

            packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 712)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 431)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 287)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 562)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 749)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
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
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 26, 50)
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
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, RGB_ID, 28, 200)
            error = '0'
            
            print("Switch to manual mode")
            print("Return to the starting position")
            for i in range(1, 7, 1):
                packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 70)
            time.sleep(5.0)
        
            packetHandler.write2ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 501)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 462)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 511)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 749)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 511)
            packetHandler.write2ByteTxRx(portHandler, DXL_ID6, GOAL_POSITION, 511)
            time.sleep(3.0)

except KeyboardInterrupt:
    pass
finally:
    for i in range(1, 7, 1):
        packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 0)
    portHandler.closePort()  
