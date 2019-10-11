
#include "Usb.h"
#include ".\Public\Protocol.h"

static void SendMouseToUsb(UINT8 *pData, UINT8 len)
{
  Enp2IntIn(pData, len);
}

// BYTE1 --
//        |--bit7:   1   ��ʾ   Y   ����ı仯��������256   ~   255�ķ�Χ,0��ʾû�����
//        |--bit6:   1   ��ʾ   X   ����ı仯��������256   ~   255�ķ�Χ��0��ʾû�����
//        |--bit5:   Y   ����仯�ķ���λ��1��ʾ����������������ƶ�
//        |--bit4:   X   ����仯�ķ���λ��1��ʾ����������������ƶ�
//        |--bit3:     ��Ϊ1
//        |--bit2:     1��ʾ�м�����
//        |--bit1:     1��ʾ�Ҽ�����  0��ʾ�Ҽ�̧��
//        |--bit0:     1��ʾ�������  0��ʾ���̧��
// BYTE2 -- X����仯������byte��bit4���9λ������,������ʾ�����ƣ����������ơ��ò����ʾ�仯��
// BYTE3 -- Y����仯������byte��bit5���9λ��������������ʾ�����ƣ����������ơ��ò����ʾ�仯��
// BYTE4 -- ���ֱ仯��0x01��ʾ������ǰ����һ��0xFF��ʾ����������һ��0x80�Ǹ��м�ֵ����������

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

void MouseMove(UINT8 Bytes, UINT8 X, UINT8 Y) // ����ĻΪ׼����������ϵ
{
  Bytes[1] += X;
  Bytes[2] += Y;
  SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
  disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));
}

void MouseScroll(UINT8 Bytes, UINT8 Value) // �� 0x01 �� �� 0xFF��ֹͣ 0x80
{
  Bytes[3] += Value;
  SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
  disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));
}
