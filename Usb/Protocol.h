
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define THIS_ENDP0_SIZE DEFAULT_ENDP0_SIZE
#define BUFFER_SIZE 64
#define DUAL_BUFFER_SIZE 128
#define UsbSetupBuf ((PUSB_SETUP_REQ)Ep0Buffer)
#define L_WIN 0X08
#define L_ALT 0X04
#define L_SHIFT 0X02
#define L_CTL 0X01
#define R_WIN 0X80
#define R_ALT 0X40
#define R_SHIFT 0X20
#define R_CTL 0X10

#define SPACE 0X2C
#define ENTER 0X28
#define CAPS_LOCK 0X39

#define CAPS_LOCK_ON 0x2
#define NUM_LOCK_ON 0x1

//packet id
#define ID_USB_KEYBOARD 0xA0
#define ID_USB_MOUSE 0xA1
#define ID_PS2_KEYBOARD 0xA2
#define ID_PS2_MOUSE 0xA3
#define ID_LED_STATUS 0xA4
#define ID_QUERY_ONLINE 0xA5
#define ID_SWITCH 0xA6

//data length
#define KEYBOARD_LEN 8
#define MOUSE_LEN 4
#define LED_LEN 1
#define ONLINE_LEN 1
#define SWITCH_LEN 1

//led status pos
#define NUM_LOCK_POS 0
#define CAP_LOCK_POS 1
#define SCROLL_LOCK_POS 2

//online
#define STATUS_ONLINE 1
#define STATUS_OFFLINE 0

//query type
#define QUERY_CURRENT_PORT 1
#define QUERY_OTHER_PORT 0

//switch
#define SWITCH_IN 1
#define SWITCH_OUT 0

#endif
