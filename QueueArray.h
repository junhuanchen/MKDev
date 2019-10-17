#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#include "Public/CH552.H"

#include "QueueArray.h"

#define EventMaxSize 32
#define EventMaxLen 16

typedef UINT8 QueueAarrayType; /** < 队列结点的数据索引类型  */

typedef struct usb_event
{

    UINT8 event[EventMaxLen];

} QueueAarrayValue; /** < 队列结点的数据域  */

typedef struct queue_array
{
    QueueAarrayType Front, Tail, Size, MaxSize;
    QueueAarrayValue Array[EventMaxSize];
} QueueArray;

void QueueArrayInit(QueueArray *Array);

BOOL QueueArrayMaxSize(QueueArray *Self);

QueueAarrayType QueueArraySize(QueueArray *Self);

BOOL QueueArrayEmpty(QueueArray *Self);

BOOL QueueArrayExist(QueueArray *Self);

BOOL QueueArrayFull(QueueArray *Self);

QueueAarrayValue * QueueArrayFront(QueueArray *Self);

QueueAarrayValue * QueueArrayBack(QueueArray *Self);

BOOL QueueArrayPush(QueueArray *Self, QueueAarrayValue *Value);

void QueueArrayBreakPush(QueueArray *Self, QueueAarrayValue *Value);

void QueueArrayPop(QueueArray *Self);

#endif // QUEUE_ARRAY_H
