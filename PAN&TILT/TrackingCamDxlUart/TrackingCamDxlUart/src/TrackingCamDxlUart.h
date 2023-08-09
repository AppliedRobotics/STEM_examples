#include "Arduino.h"

#ifndef TrackingCamDxlUart_h 
#define TrackingCamDxlUart_h 

struct TrackingCamObjInfo_t
{
  uint8_t type;
  uint8_t dummy;
  uint16_t cx;
  uint16_t cy;
  uint16_t angle;
  uint32_t obj_size;
};

struct TrackingCamBlobInfo_t
{
  uint8_t type;
  uint8_t dummy;
  uint16_t cx;
  uint16_t cy;
  uint32_t area;
  uint16_t left;
  uint16_t right;
  uint16_t top;
  uint16_t bottom;
};

class TrackingCamDxlUart
{
  uint8_t cam_id;
  HardwareSerial* serial;
public:
  void init(uint8_t cam_id, uint8_t serial_port, uint32_t baud_rate, uint8_t timeout);
  uint8_t readBlobs(uint8_t max_blob_n = 5);
  uint8_t readObjects(uint8_t max_obj_n = 5);
  uint8_t readData(uint8_t cam_id, uint8_t addr, uint8_t len, uint8_t* resp);
  TrackingCamBlobInfo_t blob[10];
  TrackingCamObjInfo_t obj[10];
};

#endif