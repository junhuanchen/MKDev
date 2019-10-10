/********************************** (C) COPYRIGHT ******************************
* File Name          :Compound_Dev.C											
* Author             : WCH                                                      
* Version            : V1.0                                                     
* Date               : 2017/03/15                                               
* Description        : A demo for USB compound device created by CH554, support 
					   keyboard and mouse, and HID compatible device.           
********************************************************************************/
#include ".\Public\CH552.H"
#include ".\Public\debug.h"

#include "stdio.h"

void setup()
{
  CfgFsys();    // Configure sys
  mDelaymS(5);  //
  mInitSTDIO(); //  Init UART0
  printf("main.\r\n");
}

void main(void)
{

  while (1)
  {
    continue;
  }
}
