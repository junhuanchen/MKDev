
#ifndef USB_DESCRIPTOR_H_
#define USB_DESCRIPTOR_H_

#define USB_INTERFACES 3

typedef struct
{
	PUINT8 descr;
	UINT8 size;
} DescriptorData;

/* device descriptor */
extern const DescriptorData DevDesc;

/* configure descriptor */
extern const DescriptorData CfgDesc;

/* device qualifier descriptor */
extern const DescriptorData DeviceQualifierCfg;

/* keyboard report descriptor */
extern const DescriptorData KeyRepDesc;

/* mouse report descriptor */
extern const DescriptorData MouseRepDesc;

/* Vendor report descriptor */
extern const DescriptorData VendorRepDesc;

/* string descriptors */
extern const DescriptorData StringDescriptors[4];

extern UINT8X StringSerial[];

#endif
