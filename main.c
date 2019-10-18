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
#include "crypt.h"							
#include ".\Usb\Usb.h"


void CheckUsbState()
{
  if (CheckPCReady() && CheckPCSleeped())
  {
    CH554USBDevWakeup();
  }
}

// int debug_state = 0;

static QueueArray xdata Array;

void main(void)
{
  static UINT8 Recv[MAX_PACKET_SIZE];
  
  CfgFsys();    // Configure sys
  mDelaymS(5);  //

  // mInitSTDIO(), LOG("main ready\r\n"); //  Init UART0
  
  if (CheckMKDevice() == FALSE) while(1);

  ControlEventInit(&Array);

  USBDeviceInit();
  
  CH554WDTModeSelect(1); // Start WDT

  HAL_ENABLE_INTERRUPTS();
  
  while (1)
  {
    CH554WDTFeed(0);

    CheckUsbState();

    UsbEventExec(&Array, Recv);
  }
}
