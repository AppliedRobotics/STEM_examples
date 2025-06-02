from dynamixel_sdk import *     
import time
PROTOCOL_VERSION = 1.0 
DXL_ID1 = 1
DXL_ID2 = 2
DXL_ID3 = 3
DXL_ID4 = 4
DXL_ID5 = 5
LED_ID = 9
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


for i in range(1, 6, 1):
    packetHandler.write1ByteTxRx(portHandler, i, OPERATING_MODE_REG, POSITION_CONTROL_MODE)
    packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 1)
    packetHandler.write2ByteTxRx(portHandler, i, MOVING_SPEED, 80)

def firstMove():
    # движение в начальное положение
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(4.0)
    # наклон вперед
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9996)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(2.0)
    # сжатие
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9996)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(3.0)
    # светодиод загорается
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, LED_ID, 26, 250)
    # движение назад
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(2.0)
    # поворот
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(4.0)
    # наклон вперед
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9896)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(1.0)
    # расжатие
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9896)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    # светодиод гаснет
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, LED_ID, 26, 0)
    time.sleep(1.0)
    # движение назад
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(2.0)

def secondMove():
    # возвращение в начальную позицию
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(4.0)
    # опять поворот за кубиком
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(4.0)
    # наклон
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9896)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(1.0)
    # сжатие
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9896)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(3.0)
    # светодиод загорается
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, LED_ID, 26, 250)
    # движение назад
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(2.0)
    # поворот
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(4.0)
    # наклон вперед
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9996)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 6061)
    time.sleep(1.0)
    # расжатие
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9996)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11409)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    # светодиод гаснет
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, LED_ID, 26, 0)
    time.sleep(3.0)
    # движение назад
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 4152)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(2.0)
    # поворот 
    packetHandler.write4ByteTxRx(portHandler, DXL_ID1, GOAL_POSITION, 8304)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID2, GOAL_POSITION, 9365)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID3, GOAL_POSITION, 11670)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID4, GOAL_POSITION, 8201)
    packetHandler.write4ByteTxRx(portHandler, DXL_ID5, GOAL_POSITION, 7862)
    time.sleep(4.0)

try:
    while 1:

        firstMove()
        secondMove()
        

except KeyboardInterrupt:
    pass
finally:
    for i in range(1, 5, 1):
        packetHandler.write1ByteTxRx(portHandler, i, TORQUE_REG, 0)

    portHandler.closePort()  