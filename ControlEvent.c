

#include "ControlEvent.h" 

#include ".\Usb\Usb.h"
#include ".\Usb\Key.h"
#include ".\Usb\Mouse.h"

#include <string.h>
#include <stdio.h>

void ControlEventInit(QueueArray *Array)
{
    QueueArrayInit(Array);
}

// 在 EP3 的 接收 入口执行，这将转移数据进入缓冲队列数组
void ControlEventIn(QueueArray *Array, UINT8 *Recv)
{
    QueueAarrayValue Value;
    UINT8 i = 0;
    int tmp = 0;

    if (Enp3IntOut(Recv))
    {
        // DebugBytes("Enp3IntOut", Recv, MAX_PACKET_SIZE);
        for (i = 0; i < MAX_PACKET_SIZE; i += 16)
        {
            if (0xBD == Recv[i])
            {
                memcpy(Value.event, &Recv[i], sizeof(Value.event));

                // DebugBytes("1 Value.event", Value.event, sizeof(Value.event));

                // DebugBytes("2 Array.Size", &Array->Size, 1);
                // DebugBytes("2 Array.MaxSize", &Array->MaxSize, 1);

                QueueArrayBreakPush(Array, &Value);

                // DebugBytes("3 Array.Size", &Array->Size, 1);
                // DebugBytes("3 Array.MaxSize", &Array->MaxSize, 1);
            }
        }
    }
}

void report(QueueArray *Array, UINT8 *Recv)
{
    const UINT8 VERSION = 0x11;

    memset(Recv, 0, MAX_PACKET_SIZE);
    Recv[0] = VERSION;
    Recv[1] = 4;
    Recv[2] = GetKeyboardLedStatus();
    Recv[3] = isNumLock();
    Recv[4] = isCapsLock();
    Recv[5] = QueueArraySize(Array);
    Enp3IntIn(Recv, MAX_PACKET_SIZE);
}

// 处理缓冲队列的数组
void ControlEventOut(QueueArray *Array, UINT8 *Recv)
{
    QueueAarrayValue *value, tmp;

    value = QueueArrayFront(Array);
    if (value != NULL)
    {
        tmp = *value;
        // DebugBytes("tmp.event", tmp.event, sizeof(tmp.event));
        switch (tmp.event[1])
        {
        case 0x01:
            switch (tmp.event[2])
            {
            case 0x00:
                Enp1IntIn(&tmp.event[3], KEYBOARD_LEN);
                break;
            case 0x01:
                ClickKey(tmp.event[3]);
                break;
            case 0x02:
                ClickCustom(tmp.event[3]);
                break;
            }
            break;
        case 0x02:
            switch (tmp.event[2])
            {
            case 0x00:
                Enp2IntIn(&tmp.event[3], MOUSE_LEN);
                break;
            case 0x01:
                MouseMove(tmp.event[3], tmp.event[4], tmp.event[5]);
                break;
            case 0x02:
                MouseScroll(tmp.event[3]);
                break;
            }
            break;
        case 0x03:
            report(Array, Recv);
            break;
        default:
            break;
        }
        QueueArrayPop(Array);
    }
}

void UsbEventExec(QueueArray *Array, UINT8 *Recv)
{
    ControlEventIn(Array, Recv);

    ControlEventOut(Array, Recv);
}
