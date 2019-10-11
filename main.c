/********************************** (C) COPYRIGHT ******************************
* File Name          :Compound_Dev.C											
* Author             : WCH                                                      
* Version            : V1.0                                                     
* Date               : 2017/03/15                                               
* Description        : A demo for USB compound device created by CH554, support 
					   keyboard and mouse, and HID compatible device.           
********************************************************************************/

#include <stdio.h>
#include <string.h>

#include ".\Public\CH552.H"
#include ".\Public\System.h"
#include ".\Public\Mcu.h"

#include ".\Usb\Usb.h"
#include ".\Usb\Key.h"
#include ".\Usb\Mouse.h"

void InitMkDev()
{
  CfgFsys();             // Configure sys
  mDelaymS(5);           //
  mInitSTDIO();          //  Init UART0

  // CH554WDTModeSelect(1); // Start WDT

  USBDeviceInit();
  HAL_ENABLE_INTERRUPTS();
  LOG("InitMkDev\r\n");
}

void CheckUsbState()
{
  if (CheckPCReady() && CheckPCSleeped())
  {
    CH554USBDevWakeup();
  }
}

static void SendMouseToUsb(UINT8 *pData, UINT8 len)
{
  Enp2IntIn(pData, len);
}

void main(void)
{
  UINT8 pData[4];
  InitMkDev();

  // tmp = res & 0x1 == 0x1;
  // printf("main %d %c%c\r\n", tmp, HexToAscii((res >> 4) & 0x0f), HexToAscii(res & 0x0f));

  // usb_key_unit_test();

  while (1)
  {
    CheckUsbState();
    mDelaymS(500);

    memset(pData, 0, sizeof(pData));

    pData[0] = 01;
    pData[1] = 00;
    pData[2] = 01;
    pData[3] = 20;

    SendMouseToUsb(pData, MOUSE_LEN);
    disp_bytes((char *)pData, sizeof(pData));

    // continue;

    // CH554WDTFeed(0);
    // mDelaymS(100);  //
    // LOG("CH554WDTFeed\r\n");
  }
}
