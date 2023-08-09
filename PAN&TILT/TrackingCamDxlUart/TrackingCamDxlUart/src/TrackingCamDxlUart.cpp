#include <TrackingCamDxlUart.h>

#define nTRACKINGCAMI2C_DEBUG
#define TRACKINGCAMI2C_DEBUG_BAUD 115200
#ifdef TRACKINGCAMI2C_DEBUG
#  define dbg_print Serial.print
#  define dbg_println Serial.println
#else
#  define dbg_print
#  define dbg_println
#endif

static uint8_t TrackingCamDxl_GetCRC(uint8_t *bufData, uint8_t sizeData);

void TrackingCamDxlUart::init(uint8_t cam_id, uint8_t serial_port, uint32_t baud_rate, uint8_t timeout)
{
	this->cam_id = cam_id;
	this->serial = &Serial;

#if defined (__AVR_ATmega2560__)
	if(serial_port == 1)
		serial = &Serial1;
	if(serial_port == 2)
		serial = &Serial2;
	if(serial_port == 3)
		serial = &Serial3;
#endif

#ifdef TRACKINGCAMI2C_DEBUG
	Serial.begin(TRACKINGCAMI2C_DEBUG_BAUD);  // start serial for output
#endif

	serial->begin(baud_rate);
	delay(100);

	//Read cam ID
	uint8_t resp[10];
	if(!readData(cam_id, 0x00, 2, resp))
	{
		dbg_println("");
		dbg_print("Tracking cam ID: ");
		dbg_print(resp[5], HEX);
		dbg_println(resp[6], HEX);
	}   

	delay(100);
	Serial.setTimeout(30);
	delay(100);
	serial->setTimeout(timeout);
	delay(100);
}

uint8_t TrackingCamDxlUart::readBlobs(uint8_t max_blob_n)
{
	const int blobs_per_block_n = 3;
	uint8_t resp[64];
	uint8_t n = 0;
	uint8_t idx = 5;
	uint8_t lines = max_blob_n > 10? 10: max_blob_n;

	if(lines == 0)
		lines = 1;

	for(int i = 0; i < lines; i++)
	{
		if(!(i % blobs_per_block_n))
		{
			idx = 5;
			if(readData(cam_id, 16 + i*16, blobs_per_block_n*16, resp)) //Line by line reading
				return n; 
		}

		blob[i].type = resp[idx++];
		if(blob[i].type == 0xFF)
			return n;
		else
			n++;

		blob[i].dummy = resp[idx++];
		blob[i].cx = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		blob[i].cy = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		blob[i].area = (uint32_t)((((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8))) * 4;
		idx += 2;
		blob[i].left = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		blob[i].right = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		blob[i].top = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		blob[i].bottom = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
	}
	return n;
}

uint8_t TrackingCamDxlUart::readObjects(uint8_t max_obj_n)
{
	const int obj_per_block_n = 4;
	uint8_t resp[64];
	uint8_t n = 0;
	uint8_t idx = 5;
	uint8_t lines = max_obj_n > 10? 10: max_obj_n;

	if(lines == 0)
		lines = 1;

	for(int i = 0; i < lines; i++)
	{
		if(!(i % obj_per_block_n))
		{
			idx = 5;
			if(readData(cam_id, 16 + i*10, obj_per_block_n*10, resp)) //Line by line reading
				return n; 
		}
		obj[i].type = resp[idx++];
		if(obj[i].type == 0xFF)
			return n;
		else
			n++;
		obj[i].dummy = resp[idx++];
		obj[i].cx = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		obj[i].cy = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		obj[i].angle = ((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8);
		idx += 2;
		obj[i].obj_size = (uint32_t)((((uint16_t)resp[idx]) + (((uint16_t)resp[idx + 1]) << 8))) * 4;
		idx += 2;
	}
	return n;
}

/* Reads specified number of bytes from camera control registers (dxl API)
* Do not forget to disable debug prints!!!
*/
uint8_t TrackingCamDxlUart::readData(uint8_t cam_id, uint8_t addr, uint8_t len, uint8_t* resp) 
{

	uint8_t buf[255];
	uint8_t idx = 0;

	serial->flush();

	serial->readBytes(buf, serial->available()); //Clear port

	buf[idx++] = 0xff;    //Sync byte
	buf[idx++] = 0xff;    //Sync byte
	buf[idx++] = cam_id; 
	buf[idx++] = 4;       //Dxl length
	buf[idx++] = 0x02;    //Dxl read cmd
	buf[idx++] = addr;
	buf[idx++] = len;
	buf[idx++] = TrackingCamDxl_GetCRC(buf + 2, 5);


	serial->write(buf, idx); 

	bool is_resp = false;
	for(int i = 0; i < 20; i++)
	{
		resp[0] = resp[1];
		resp[1] = resp[2];

		if(!serial->readBytes(resp + 2, 1))
			return 0xFF;

		if(resp[0] == 0xFF && resp[1] == 0xFF && resp[2] == cam_id)
		{
			is_resp = true;
			break;
		}
	}

	if(!is_resp)
	{
		dbg_println("No packet sync!");
		//dbg_print("Packet: ");
		//for(int i = 0; i < len + 6; i++)
		//  dbg_print(resp[i], HEX);
		//dbg_print("");
		return 0xFF;
	}

	if(serial->readBytes(resp + 3, len + 3) != len + 3)
	{
		dbg_println("No response!");
		return 0xFF;
	}

	if(TrackingCamDxl_GetCRC(resp + 2, len + 3) != resp[len + 5])
	{
		dbg_println("Bad CRC!");
		//dbg_print("Packet: ");
		//for(int i = 0; i < len + 6; i++)
		//  dbg_print(resp[i], HEX);
		//dbg_println("");
		return 0xFF;
	}  
	return 0;
}

static uint8_t TrackingCamDxl_GetCRC(uint8_t *bufData, uint8_t sizeData) 
{
	uint32_t crc32 = 0;
	for(uint16_t i = 0; i < sizeData; i++)
		crc32 += bufData[i];
	return (uint8_t)((~crc32) & 0xFF);
}