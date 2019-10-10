/********************************** (C) COPYRIGHT ******************************
* File Name          :Compound_Dev.C											
* Author             : WCH                                                      
* Version            : V1.0                                                     
* Date               : 2017/03/15                                               
* Description        : A demo for USB compound device created by CH554, support 
					   keyboard and mouse, and HID compatible device.           
********************************************************************************/
#include ".\Public\CH552.H"
#include ".\Public\System.h"
#include ".\Public\Mcu.h"

#include ".\Usb\Usb.h"

#include "stdio.h"

void InitMkDev()
{
  CfgFsys();    // Configure sys
  mDelaymS(5);  //
  mInitSTDIO(); //  Init UART0
  CH554WDTModeSelect(1); // WDT
  USBDeviceInit();
  HAL_ENABLE_INTERRUPTS();
  LOG("InitMkDev\r\n");
}

void CheckUsb()
{
  if (CheckPCReady() && CheckPCSleeped())
  {
    CH554USBDevWakeup();
  }
}

void main(void)
{

  // UINT8 id = packet[0];
  // UINT8 *pData = &packet[1];
  // SendKeyboardToUsb(pData, KEYBOARD_LEN);
  // SendMouseToUsb(pData, MOUSE_LEN);
  
  InitMkDev();

  while (1)
  {
	  CH554WDTFeed(0);
    // mDelaymS(100);  //
    // LOG("CH554WDTFeed\r\n");
  }
}
