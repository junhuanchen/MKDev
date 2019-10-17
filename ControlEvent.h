
#include ".\Public\CH552.h"	 
#include ".\Public\System.h"
#include ".\Public\Mcu.h"
#include ".\QueueArray.h"

extern void ControlEventInit(QueueArray *Array);

// extern void ControlEventIn(QueueArray *Array, UINT8 *Recv);

// extern void ControlEventOut(QueueArray *Array);

extern void UsbEventExec(QueueArray *Array, UINT8 *Recv);