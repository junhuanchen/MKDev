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
						   
#include "ControlEvent.h"
							
#include ".\Usb\Usb.h"

void InitMkDev()
{
  CfgFsys();    // Configure sys
  mDelaymS(5);  //
  mInitSTDIO(); //  Init UART0

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

// int debug_state = 0;

#include <assert.h>

static QueueArray xdata Array;

void main(void)
{
  static UINT8 Recv[MAX_PACKET_SIZE];

  int i = 0;
  UINT16 ontimer = 0;

  InitMkDev();

  // return;

  // UINT8 pData[4];

  ControlEventInit(&Array);

  // tmp = res & 0x1 == 0x1;
  // printf("main %d %c%c\r\n", tmp, HexToAscii((res >> 4) & 0x0f), HexToAscii(res & 0x0f));

  // usb_key_unit_test();

  // memset(pData, 0, sizeof(pData));

  // MouseBYTE[3] = 1;
  
  while (1)
  {
    CheckUsbState();

    UsbEventExec(&Array, Recv);

    // mDelaymS(1000);

    // unit_test_hid_data();

    // LOG("debug_state %d\r\n", debug_state);

    // MouseBYTE[1] += 1;
    // MouseBYTE[2] += 1;

    // MouseBYTE[0] = 1;
    // SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
    // disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));

    // mDelaymS(100);

    // MouseBYTE[0] = 0;
    // SendMouseToUsb((char *)&MouseBYTE, MOUSE_LEN);
    // disp_bytes((char *)&MouseBYTE, sizeof(MouseBYTE));

    // continue;

    // CH554WDTFeed(0);
    // mDelaymS(100);  //
    // LOG("CH554WDTFeed\r\n");
  }
}
