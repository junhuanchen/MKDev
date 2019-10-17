
#include "..\Public\CH552.H"

#include "UsbDef.h"
#include "hid.h"
#include "UsbDescriptor.h"

/* device descriptor */
static UINT8C _DevDesc[] =
	{
		0x12,				  /*bLength */
		USB_DESCR_TYP_DEVICE, /*bDescriptorType*/
		0x10, 0x01,			  /*bcdUSB */
		0x00,				  /*bDeviceClass*/
		0x00,				  /*bDeviceSubClass*/
		0x00,				  /*bDeviceProtocol*/
		DEFAULT_ENDP0_SIZE,   /*bMaxPacketSize*/
		0x19, 0x20,			  /*idVendor = 0x2019*/
		0x69, 0x07,			  /*idProduct (0x0769)*/
		0x00, 0x00,			  /*bcdDevice rel. 0.00*/
		0x01,				  /*Index of string descriptor describing
                                                  manufacturer */
		0x02,				  /*Index of string descriptor describing
                                                 product*/
		0x03,				  /*Index of string descriptor describing the
                                                 device serial number */
		0x01				  /*bNumConfigurations*/
};

/* device descriptor */
const DescriptorData DevDesc =
	{
		_DevDesc,

		sizeof(_DevDesc)};

/* keyboard report descriptor */
static UINT8C _KeyRepDesc[] =
	{
		HID_UsagePage(HID_USAGE_PAGE_GENERIC),
		HID_Usage(HID_USAGE_GENERIC_KEYBOARD),
		HID_Collection(HID_Application),
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),
		HID_UsageMin(0xE0),
		HID_UsageMax(0xE7),

		HID_LogicalMin(0),
		HID_LogicalMax(1),
		HID_ReportSize(1),
		HID_ReportCount(8),

		HID_Input(HID_Data | HID_Variable | HID_Absolute),

		HID_ReportSize(8),
		HID_ReportCount(1),

		HID_Input(HID_Constant | HID_Variable | HID_Absolute),

		HID_ReportSize(1),
		HID_ReportCount(5),

		HID_UsagePage(HID_USAGE_PAGE_LED),
		HID_UsageMin(0x01),
		HID_UsageMax(0x05),

		HID_Output(HID_Data | HID_Variable | HID_Absolute),

		HID_ReportSize(3),
		HID_ReportCount(1),
		HID_Output(HID_Constant | HID_Variable | HID_Absolute),

		HID_ReportSize(8),
		HID_ReportCount(6),
		HID_LogicalMin(0),
		HID_LogicalMax(0xFF),
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),
		HID_UsageMin(0x00),
		HID_UsageMax(0x91),
		HID_Input(HID_Data | HID_Array | HID_Absolute),
		HID_EndCollection,
};

/* keyboard report descriptor */
const DescriptorData KeyRepDesc =
	{
		_KeyRepDesc,

		sizeof(_KeyRepDesc)};

/* mouse report descriptor */
static UINT8C _MouseRepDesc[] =
	{
		HID_UsagePage(HID_USAGE_PAGE_GENERIC),

		HID_Usage(HID_USAGE_GENERIC_MOUSE),

		HID_Collection(HID_Application),
		HID_Usage(HID_USAGE_GENERIC_POINTER),
		HID_Collection(HID_Physical),
		HID_UsagePage(HID_USAGE_PAGE_BUTTON),
		HID_UsageMin(0x01),
		HID_UsageMax(0x03),
		HID_LogicalMin(0),
		HID_LogicalMax(1),
		HID_ReportSize(1),
		HID_ReportCount(3),
		HID_Input(HID_Data | HID_Variable | HID_Absolute),

		HID_ReportSize(5),
		HID_ReportCount(1),
		HID_Input(HID_Constant | HID_Variable | HID_Absolute),

		HID_UsagePage(HID_USAGE_PAGE_GENERIC),
		HID_Usage(HID_USAGE_GENERIC_X),
		HID_Usage(HID_USAGE_GENERIC_Y),
		HID_Usage(HID_USAGE_GENERIC_WHEEL),
		HID_LogicalMin(0x81),
		HID_LogicalMax(0x7F),
		HID_ReportSize(8),
		HID_ReportCount(3),
		HID_Input(HID_Data | HID_Variable | HID_Relative),
		HID_EndCollection,
		HID_EndCollection,
};

/* mouse report descriptor */
const DescriptorData MouseRepDesc =
	{
		_MouseRepDesc,

		sizeof(_MouseRepDesc)};

static UINT8C _VendorRepDesc[] = {
	0x06, 0xA0, 0xFF, // Usage Page(FFA0h, vendor defined)
	0x09, 0x01,		  // Usage(vendor defined)
	0xA1, 0x01,		  // Collection(Application)
	0x09, 0x02,		  // Usage(vendor defined)
	0xA1, 0x00,		  // Collection(Physical)
	0x06, 0xA1, 0xFF, // Usage Page(vendor defined)

	// Input Report
	0x09, 0x03, // Usage(vendor defined)
	0x09, 0x04, // Usage(vendor defined)
	0x15, 0x80, // Logical Minimum(0x80 or -128)
	0x25, 0x7F, // Logical Maximum(0x7F or 127)
	0x35, 0x00, // Physical Minimum(0)
	0x45, 0xFF, // Physical Maximum(255)
	0x75, 0x08, // Report size(8 Bits, 1 Byte)
	0x95, 0x40, // Report count(64 fields)
	0x81, 0x02, // Input(data, variable, absolute)
	// Output Report
	0x09, 0x05, // Usage(vendor defined)
	0x09, 0x06, // Usage(vendor defined)
	0x15, 0x80, // Logical Minimum(0x80 or -128)
	0x25, 0x7F, // Logical Maximum(0x7F or 127)
	0x35, 0x00, // Physical Minimum(0)
	0x45, 0xFF, // Physical Maximum(255)
	0x75, 0x08, // Report size(8 Bits, 1 Byte)
	0x95, 0x40, // Report count(64 fields)
	0x91, 0x02, // Output(data, variable, absolute)
	0xC0,		//End Collection(Physical)
	0xC0		//End Collection(Application)
};

/* Vendor report descriptor */
const DescriptorData VendorRepDesc =
	{
		_VendorRepDesc,

		sizeof(_VendorRepDesc)};

#define TOTAL_CONFIG_DESCR_SIZE sizeof(USB_CFG_DESCR) +      \
									sizeof(USB_ITF_DESCR) +  \
									sizeof(USB_HID_DESCR) +  \
									sizeof(USB_ENDP_DESCR) + \
									sizeof(USB_ITF_DESCR) +  \
									sizeof(USB_HID_DESCR) +  \
									sizeof(USB_ENDP_DESCR) + \
									sizeof(USB_ITF_DESCR) +  \
									sizeof(USB_HID_DESCR) +  \
									sizeof(USB_ENDP_DESCR) +  \
									sizeof(USB_ENDP_DESCR)

#define KEYBOARD_REPORT_DESCR_SIZE sizeof(_KeyRepDesc)

#define MOUSE_REPORT_DESCR_SIZE sizeof(_MouseRepDesc)

#define VENDOR_REPORT_DESCR_SIZE sizeof(_VendorRepDesc)

/* configuration descriptor */
static UINT8C _CfgDesc[] =
	{
		0x09,																   /* bLength: Configuation Descriptor size */
		USB_DESCR_TYP_CONFIG,												   /* bDescriptorType: Configuration */
		TOTAL_CONFIG_DESCR_SIZE & 0xff, (TOTAL_CONFIG_DESCR_SIZE >> 8) & 0xff, /* wTotalLength: Bytes returned */
		USB_INTERFACES,																   /*bNumInterfaces: 3 interface*/
		0x01,																   /*bConfigurationValue: Configuration value*/
		0x00,																   /*iConfiguration: Index of string descriptor describing
                                     the configuration*/
		0x80 | (1 << 6) | (1 << 5),											   /*bmAttributes: self powered, remote wakeup */
		0x32,															   /*MaxPower 100 mA: this current is used for detecting Vbus*/

		/************** Descriptor of keyboard interface ****************/
		0x09,				  /*bLength: Interface Descriptor size*/
		USB_DESCR_TYP_INTERF, /*bDescriptorType: Interface descriptor type*/
		0x00,				  /*bInterfaceNumber: Number of Interface*/
		0x00,				  /*bAlternateSetting: Alternate setting*/
		0x01,				  /*bNumEndpoints*/
		0x03,				  /*bInterfaceClass: HID*/
		0x01,				  /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
		0x01,				  /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
		0x00,				  /*iInterface: Index of string descriptor*/

		/******************** Descriptor of keyboard HID ********************/
		0x09,																		 /*bLength: HID Descriptor size*/
		USB_DESCR_TYP_HID,															 /*bDescriptorType: HID*/
		0x11, 0x01,																	 /*bcdHID: HID Class Spec release number*/
		0x00,																		 /*bCountryCode: Hardware target country*/
		0x01,																		 /*bNumDescriptors: Number of HID class descriptors to follow*/
		USB_DESCR_TYP_REPORT,														 /*bDescriptorType*/
		KEYBOARD_REPORT_DESCR_SIZE & 0xff, (KEYBOARD_REPORT_DESCR_SIZE >> 8) & 0xff, /*wItemLength: Total length of Report descriptor*/

		/******************** Descriptor of keyboard endpoint ********************/
		0x07,												   /*bLength: Endpoint Descriptor size*/
		USB_DESCR_TYP_ENDP,									   /*bDescriptorType:*/
		0x81,												   /*bEndpointAddress: Endpoint Address (IN)*/
		0x03,												   /*bmAttributes: Interrupt endpoint*/
		MAX_PACKET_SIZE & 0xff, (MAX_PACKET_SIZE >> 8) & 0xff, /*wMaxPacketSize: 32 Byte max */
		0x0a,												   /*bInterval: Polling Interval (10 ms)*/

		/************** Descriptor of mousse interface ****************/
		0x09,				  /*bLength: Interface Descriptor size*/
		USB_DESCR_TYP_INTERF, /*bDescriptorType: Interface descriptor type*/
		0x01,				  /*bInterfaceNumber: Number of Interface*/
		0x00,				  /*bAlternateSetting: Alternate setting*/
		0x01,				  /*bNumEndpoints*/
		0x03,				  /*bInterfaceClass: HID*/
		0x01,				  /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
		0x02,				  /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
		0x00,				  /*iInterface: Index of string descriptor*/

		/******************** Descriptor of mouse HID ********************/
		0x09,																   /*bLength: HID Descriptor size*/
		USB_DESCR_TYP_HID,													   /*bDescriptorType: HID*/
		0x10, 0x01,															   /*bcdHID: HID Class Spec release number*/
		0x00,																   /*bCountryCode: Hardware target country*/
		0x01,																   /*bNumDescriptors: Number of HID class descriptors to follow*/
		USB_DESCR_TYP_REPORT,												   /*bDescriptorType*/
		MOUSE_REPORT_DESCR_SIZE & 0xff, (MOUSE_REPORT_DESCR_SIZE >> 8) & 0xff, /*wItemLength: Total length of Report descriptor*/

		/******************** Descriptor of mouse endpoint ********************/
		0x07,												   /*bLength: Endpoint Descriptor size*/
		USB_DESCR_TYP_ENDP,									   /*bDescriptorType:*/
		0x82,												   /*bEndpointAddress: Endpoint Address (IN)*/
		0x03,												   /*bmAttributes: Interrupt endpoint*/
		MAX_PACKET_SIZE & 0xff, (MAX_PACKET_SIZE >> 8) & 0xff, /*wMaxPacketSize: 64 Byte max */
		0x0a,												   /*bInterval: Polling Interval (10 ms)*/

		/************** Descriptor of vendor interface ****************/
		// Interface descriptor (Vendor-defined)
		0x09,				  // Length of the descriptor
		USB_DESCR_TYP_INTERF, // Type: Interface Descriptor
		0x02,				  // Interface ID
		0x00,				  // Alternate setting
		0x02,				  // Number of Endpoints
		0x03,				  // Interface class code
		0x01,				  // Subclass code 0=No subclass, 1=Boot Interface subclass
		0x00,				  // Protocol code 0=None, 1=Keyboard, 2=Mouse
		0x00,				  // Index of corresponding string descriptor (On Windows, it is called "Bus reported device description")

		/******************** Descriptor of Vendor HID ********************/
		// HID descriptor (Vendor-defined)
		0x09,			   // Length of the descriptor
		USB_DESCR_TYP_HID, // Type: HID Descriptor
		0x10, 0x01,		   // bcdHID: HID Class Spec release number
		0x00,			   // bCountryCode: Hardware target country
		0x01,			   // bNumDescriptors: Number of HID class descriptors to follow
		0x22,			   // bDescriptorType
		// wItemLength: Total length of Report descriptor
		VENDOR_REPORT_DESCR_SIZE & 0xff, (VENDOR_REPORT_DESCR_SIZE >> 8) & 0xff,

		// Endpoint descriptor (Vendor-defined)	// EP3, IN
		0x07,		// Length of the descriptor
		0x05,		// Type: Endpoint Descriptor
		0x83,		// Endpoint: D7: 0-Out 1-In, D6-D4=0, D3-D0 Endpoint number
		0x03,		// Attributes:
					// D1:0 Transfer type: 00 = Control 01 = Isochronous 10 = Bulk 11 = Interrupt
					// 			The following only apply to isochronous endpoints. Else set to 0.
					// D3:2 Synchronisation Type: 00 = No Synchronisation 01 = Asynchronous 10 = Adaptive 11 = Synchronous
					// D5:4	Usage Type: 00 = Data endpoint 01 = Feedback endpoint 10 = Implicit feedback Data endpoint 11 = Reserved
					// D7:6 = 0
		0x40, 0x00, // Maximum packet size can be handled
		0x18,		// Interval for polling, in units of 1 ms for low/full speed

		// Endpoint descriptor (Vendor-defined)	// EP3, OUT
		0x07,		// Length of the descriptor
		0x05,		// Type: Endpoint Descriptor
		0x03,		// Endpoint: D7: 0-Out 1-In, D6-D4=0, D3-D0 Endpoint number
		0x03,		// Attributes:
					// D1:0 Transfer type: 00 = Control 01 = Isochronous 10 = Bulk 11 = Interrupt
					// 			The following only apply to isochronous endpoints. Else set to 0.
					// D3:2 Synchronisation Type: 00 = No Synchronisation 01 = Asynchronous 10 = Adaptive 11 = Synchronous
					// D5:4	Usage Type: 00 = Data endpoint 01 = Feedback endpoint 10 = Implicit feedback Data endpoint 11 = Reserved
					// D7:6 = 0
		0x40, 0x00, // Maximum packet size can be handled
		0x18,		// Interval for polling, in units of 1 ms for low/full speed

};

/* configure descriptor */
const DescriptorData CfgDesc =
	{
		_CfgDesc,

		sizeof(_CfgDesc)};

/* USB Device Qualifier */
static UINT8C _USB_DeviceQualifier[] =
	{
		10,					  /* bLength */
		USB_DESCR_TYP_QUALIF, /* bDescriptorType */

		0x00, 0x02, /*bcdUSB */

		0x00, /* bDeviceClass */
		0x00, /* bDeviceSubClass */
		0x00, /* bDeviceProtocol */

		DEFAULT_ENDP0_SIZE, /* bMaxPacketSize0 */
		0x00,				/* bNumOtherSpeedConfigurations */
		0x00				/* bReserved */
};

/* device qualifier descriptor */
const DescriptorData DeviceQualifierCfg =
	{
		_USB_DeviceQualifier,

		sizeof(_USB_DeviceQualifier)};

#define STRING_LANGID_SIZE 4
#define STRING_VENDOR_SIZE 12
#define STRING_PRODUCT_SIZE 22
#define STRING_SERIAL_SIZE 18

static UINT8C StringLangID[STRING_LANGID_SIZE] =
	{
		STRING_LANGID_SIZE,
		USB_DESCR_TYP_STRING,
		0x09, 0x04};

static UINT8C StringVecdor[STRING_VENDOR_SIZE] =
	{
		STRING_VENDOR_SIZE,
		USB_DESCR_TYP_STRING,

		/* vendor */
		'J', 0,
		'u', 0,
		'w', 0,
		'a', 0,
		'n', 0};

static UINT8C StringProduct[STRING_PRODUCT_SIZE] =
	{
		STRING_PRODUCT_SIZE,
		USB_DESCR_TYP_STRING,

		/* product */
		'M', 0,
		'K', 0,
		' ', 0,
		'D', 0,
		'e', 0,
		'v', 0,
		'i', 0,
		'c', 0,
		'e', 0};

UINT8X StringSerial[STRING_SERIAL_SIZE] =
	{
		STRING_SERIAL_SIZE,
		USB_DESCR_TYP_STRING,

		/* serial */
		'0', 0,
		'0', 0,
		'0', 0,
		'0', 0,
		'0', 0,
		'0', 0,
		'0', 0,
		'0', 0};

const DescriptorData StringDescriptors[4] =
	{
		{StringLangID, sizeof(StringLangID)},
		{StringVecdor, sizeof(StringVecdor)},
		{StringProduct, sizeof(StringProduct)},
		{StringSerial, sizeof(StringSerial)}};
