
#include "Usb.h"
#include ".\Public\Protocol.h"

typedef struct  _HID_Device_Button{
 unsigned char Usage_min;
 unsigned char Usage_max;
 unsigned char Logical_min;
 unsigned char Logical_max;
 unsigned char Size_bit;
 unsigned char Size_reserved;
}BUTTON;

typedef struct  _HID_Device_XY{
 unsigned short Logical_min;
 unsigned short Logical_max;
 unsigned char Size_bit;
 unsigned char Size_reserved;
}XY;

typedef struct  _HID_Device_Wheel{
 unsigned char Logical_min;
 unsigned char Logical_max;
 unsigned char Size_bit;
 unsigned char Size_reserved;
}WHEEL;

typedef struct  _HID_Device_Mouse{
	unsigned short  X;
	unsigned short  Y;
	unsigned char  Left;
	unsigned char  Right;
	unsigned char  Middle;
	char  Wheel;
	//------------------------------
  BUTTON Button;
  XY X_Y;
  WHEEL Wheel_;
} MOUSE;
