
#include "Usb.h"
#include ".\Public\Protocol.h"

static void SendMouseToUsb(UINT8 *pData, UINT8 len)
{
  Enp2IntIn(pData, len);
}

// BYTE1 --
//        |--bit7:   1   表示   Y   坐标的变化量超出－256   ~   255的范围,0表示没有溢出
//        |--bit6:   1   表示   X   坐标的变化量超出－256   ~   255的范围，0表示没有溢出
//        |--bit5:   Y   坐标变化的符号位，1表示负数，即鼠标向下移动
//        |--bit4:   X   坐标变化的符号位，1表示负数，即鼠标向左移动
//        |--bit3:     恒为1
//        |--bit2:     1表示中键按下
//        |--bit1:     1表示右键按下  0表示右键抬起
//        |--bit0:     1表示左键按下  0表示左键抬起
// BYTE2 -- X坐标变化量，与byte的bit4组成9位符号数,负数表示向左移，正数表右移。用补码表示变化量
// BYTE3 -- Y坐标变化量，与byte的bit5组成9位符号数，负数表示向下移，正数表上移。用补码表示变化量
// BYTE4 -- 滚轮变化。0x01表示滚轮向前滚动一格；0xFF表示滚轮向后滚动一格；0x80是个中间值，不滚动。

UINT8 MouseBYTE[] = {0x00, 0x00, 0x00, 0x00};

void MouseLeftClick(UINT8 Bytes, UINT8 interval)
{
  Bytes[0] = 1;
  SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
  // disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));
  mDelaymS(100);

  Bytes[0] = 0;
  SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
  // disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));
  mDelaymS(100);
}

void MouseMove(UINT8 Bytes, UINT8 X, UINT8 Y) // 以屏幕为准的正常坐标系
{
  Bytes[1] += X;
  Bytes[2] += Y;
  SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
  disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));
}

void MouseScroll(UINT8 Bytes, UINT8 Value) // 上 0x01 ， 下 0xFF，停止 0x80
{
  Bytes[3] += Value;
  SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
  disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));
}
