
#include <string.h>

#include "Usb.h"

#include "Protocol.h"

/*******************************************************************************
* Function Name  : static SendKey( char *p)
* Description    : ASCII to key code
* Input          : char *p
* Output         : None
* Return         : None
*******************************************************************************/

static void SetSendKey(char *HIDKey, char c)
{

  if ((c >= 'a') && (c <= 'z'))
  {
    c = c - 'a' + 'A';
  }

  if ((c >= 'A') && (c <= 'Z'))
  {
    HIDKey[2] = c - 'A' + 4;
  }
  else if (c >= '1' && c <= '9')
    HIDKey[2] = c - '1' + 0X1E;
  else
  {
    switch (c)
    {
    case '`':
      HIDKey[0] = 0X08;
      HIDKey[2] = 0X15;
      break;
    case '\\':
      HIDKey[2] = 0x31;
      break;
    case ' ':
      HIDKey[2] = L_SHIFT;
      break;
    case '\r':
      HIDKey[2] = ENTER;
      break;
    case ':':
      HIDKey[0] = 0x02;
      HIDKey[2] = 0x33;
      break;
    case '+':
      HIDKey[0] = 0x000;
      HIDKey[2] = 0x57;
      break;
    case '_':
      HIDKey[0] = 0X02;
      HIDKey[2] = 0X2D;
      break;
    case '/':
      HIDKey[0] = L_CTL + L_ALT;
      HIDKey[2] = 0X16;
      break;
    case '0':
      HIDKey[2] = 0X27;
      break;
    case '.':
      HIDKey[2] = 0X37;
      break;
    case '~':
      HIDKey[0] = L_ALT;
      HIDKey[2] = 0X05;
      break;
    case '!':
      HIDKey[0] = L_ALT;
      HIDKey[2] = 0X08;
      break;
    default:
      HIDKey[0] = 0X00;
      HIDKey[2] = 0X00;
      break;
    }
  }
}

static void SetNullKey(char *HIDKey)
{
  HIDKey[0] = 0X00;
  HIDKey[2] = 0X00;
}

static void SetCustomKey(char *HIDKey, char FuncKey)
{
  HIDKey[0] = 0X00;
  HIDKey[2] = FuncKey;
}

static void SendKeyboardToUsb(UINT8 *pData, UINT8 len)
{
  Enp1IntIn(pData, len);
}

void ClickKey(char key)
{
  UINT8 pData[KEYBOARD_LEN];
  memset(pData, 0, sizeof(pData));
  // disp_bytes(pData, sizeof(pData));
  mDelaymS(20);

  SetSendKey(pData, key);
  SendKeyboardToUsb(pData, sizeof(pData));
  // disp_bytes((char *)pData, sizeof(pData));
  mDelaymS(20);

  SetNullKey(pData);
  SendKeyboardToUsb(pData, sizeof(pData));
  // disp_bytes((char *)pData, sizeof(pData));
  mDelaymS(20);
}

void ClickCustom(char key)
{
  UINT8 pData[KEYBOARD_LEN];
  memset(pData, 0, sizeof(pData));
  // disp_bytes(pData, sizeof(pData));
  mDelaymS(20);

  SetCustomKey(pData, key);
  SendKeyboardToUsb(pData, sizeof(pData));
  // disp_bytes((char *)pData, sizeof(pData));
  mDelaymS(20);

  SetNullKey(pData);
  SendKeyboardToUsb(pData, sizeof(pData));
  // disp_bytes((char *)pData, sizeof(pData));
  mDelaymS(20);
}

static UINT8 isCapsLock()
{
  int tmp = 0;
  UINT8 res = 0;

  res = GetKeyboardLedStatus();
  // // LOG("GetKeyboardLedStatus() %c%c \r\n", HexToAscii((res >> 4) & 0x0f), HexToAscii(res & 0x0f));

  tmp = res & CAPS_LOCK_ON;
  // printf("res %d %c%c\r\n", tmp, HexToAscii((res >> 4) & 0x0f), HexToAscii(res & 0x0f));

  return (tmp == CAPS_LOCK_ON);
}

static UINT8 isNumLock()
{
  int tmp = 0;
  UINT8 res = 0;

  res = GetKeyboardLedStatus();
  // // LOG("GetKeyboardLedStatus() %c%c \r\n", HexToAscii((res >> 4) & 0x0f), HexToAscii(res & 0x0f));

  tmp = res & NUM_LOCK_ON;
  // printf("res %d %c%c\r\n", tmp, HexToAscii((res >> 4) & 0x0f), HexToAscii(res & 0x0f));

  return (tmp == NUM_LOCK_ON);
}

static void usb_key_unit_test()
{
  int i = 0;
  mDelaymS(1000);

  // // LOG("GetKeyboardLedStatus %X \r\n", GetKeyboardLedStatus());

  if (1 == isCapsLock())
  {
    ClickCustom(CAPS_LOCK);
  }

  for (i = '0'; i <= '9'; i++)
  {
    ClickKey(i);
  }
  for (i = 'a'; i <= 'z'; i++)
  {
    ClickKey(i);
  }
  
  if (0 == isCapsLock())
  {
    ClickCustom(CAPS_LOCK);
  }
  
  for (i = 'A'; i <= 'Z'; i++)
  {
    ClickKey(i);
  }
  
}
