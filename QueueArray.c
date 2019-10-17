#include "QueueArray.h"
#include <string.h>

void QueueArrayInit(QueueArray *Array)
{
    Array->Size = 0;
    Array->Front = 1, Array->Tail = 0;
    Array->MaxSize = EventMaxSize;
}

BOOL QueueArrayMaxSize(QueueArray *Self)
{
    return Self->MaxSize;
}

QueueAarrayType QueueArraySize(QueueArray *Self)
{
    return Self->Size;
}

BOOL QueueArrayEmpty(QueueArray *Self)
{
    return 0 == Self->Size;
}

BOOL QueueArrayExist(QueueArray *Self)
{
    return !QueueArrayEmpty(Self);
}

BOOL QueueArrayFull(QueueArray *Self)
{
    return Self->Size == Self->MaxSize;
}

QueueAarrayValue *QueueArrayFront(QueueArray *Self)
{
    return QueueArrayEmpty(Self) ? NULL : &(Self->Array[Self->Front]);
}

#define QueueArrayMove(Pos, Max) Pos = (Pos + 1) % Max;

BOOL QueueArrayPush(QueueArray *Self, QueueAarrayValue *Value)
{
    if (FALSE == QueueArrayFull(Self))
    {
        QueueArrayMove(Self->Tail, Self->MaxSize);
        Self->Array[Self->Tail] = *Value;
        Self->Size++;
        return TRUE;
    }
    return FALSE;
}

void QueueArrayBreakPush(QueueArray *Self, QueueAarrayValue *Value)
{
    if (TRUE == QueueArrayFull(Self))
    {
        // 队列满得情况下将移除当前队头（向后移动）
        QueueArrayMove(Self->Front, Self->MaxSize);
    }
    else
    {
        Self->Size++;
    }
    QueueArrayMove(Self->Tail, Self->MaxSize);
    Self->Array[Self->Tail] = *Value;
}

void QueueArrayPop(QueueArray *Self)
{
    if (QueueArrayExist(Self))
    {
        memset(&Self->Array[Self->Front], 0, sizeof(Self->Array[Self->Front]));
        QueueArrayMove(Self->Front, Self->MaxSize);
        Self->Size--;
    }
}

#ifdef UNIT_TEST

#define _CRTDBG_MAP_ALLOC /**< VS 提供的 malloc 内存泄漏检测宏  */
#include <crtdbg.h>
#include <assert.h>
#include <stdlib.h>

void UnitTestQueueArray(void)
{
    // 初始化队列
    QueueArray *queue;
    queue = QueueArrayNew(3, malloc, free);
    // 队列为空
    assert(TRUE == QueueArrayEmpty(queue));
    assert(FALSE == QueueArrayExist(queue));
    assert(0 == QueueArraySize(queue));
    // 添加元素，测试队列
    QueueArrayPush(queue, (QueueAarrayValue)(1));
    assert((QueueAarrayValue)(1) == QueueArrayFront(queue));
    assert(1 == QueueArraySize(queue));
    QueueArrayPush(queue, (QueueAarrayValue)(2));
    assert((QueueAarrayValue)(1) == QueueArrayFront(queue));
    assert(2 == QueueArraySize(queue));
    QueueArrayPop(queue);
    assert((QueueAarrayValue)(2) == QueueArrayFront(queue));
    assert(1 == QueueArraySize(queue));
    // 添加元素，测试队列容量
    assert(TRUE == QueueArrayPush(queue, (QueueAarrayValue)(3)));
    assert(2 == QueueArraySize(queue));
    assert(TRUE == QueueArrayPush(queue, (QueueAarrayValue)(4)));
    assert(3 == QueueArraySize(queue));
    assert(FALSE == QueueArrayPush(queue, (QueueAarrayValue)(5))); // 失败
    assert(3 == QueueArraySize(queue));
    assert((QueueAarrayValue)(2) == QueueArrayFront(queue));
    QueueArrayPop(queue);
    assert(2 == QueueArraySize(queue));
    assert((QueueAarrayValue)(3) == QueueArrayFront(queue));
    QueueArrayPop(queue);
    assert(1 == QueueArraySize(queue));
    assert((QueueAarrayValue)(4) == QueueArrayFront(queue));
    QueueArrayPop(queue);
    assert(0 == QueueArraySize(queue));
    assert((QueueAarrayValue)(0) == QueueArrayFront(queue));
    // 添加元素，测试队列
    QueueArrayBreakPush(queue, (QueueAarrayValue)(1));
    assert((QueueAarrayValue)(1) == QueueArrayFront(queue));
    assert(1 == QueueArraySize(queue));
    QueueArrayBreakPush(queue, (QueueAarrayValue)(2));
    assert((QueueAarrayValue)(1) == QueueArrayFront(queue));
    assert(2 == QueueArraySize(queue));
    QueueArrayPop(queue);
    assert((QueueAarrayValue)(2) == QueueArrayFront(queue));
    // 添加元素，测试队列容量
    QueueArrayBreakPush(queue, (QueueAarrayValue)(3));
    assert(2 == QueueArraySize(queue));
    QueueArrayBreakPush(queue, (QueueAarrayValue)(4));
    assert(3 == QueueArraySize(queue));
    QueueArrayBreakPush(queue, (QueueAarrayValue)(5));
    assert(3 == QueueArraySize(queue));
    assert((QueueAarrayValue)(3) == QueueArrayFront(queue));
    QueueArrayPop(queue);
    assert(2 == QueueArraySize(queue));
    assert((QueueAarrayValue)(4) == QueueArrayFront(queue));
    QueueArrayPop(queue);
    assert(1 == QueueArraySize(queue));
    assert((QueueAarrayValue)(5) == QueueArrayFront(queue));
    QueueArrayPop(queue);
    assert(0 == QueueArraySize(queue));
    QueueArrayDel(queue);

    _CrtDumpMemoryLeaks();
}

#endif
