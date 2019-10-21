#include ".\public\CH552.H"
#include ".\Public\System.h"

#include <stdio.h>
#include <string.h>

#define LenUUID 4
UINT8 *GetUUID()
{
    static UINT8 ID[LenUUID];
    ID[0] = *(PUINT8C)(0x3FFC);
    ID[1] = *(PUINT8C)(0x3FFD);
    ID[2] = *(PUINT8C)(0x3FFE);
    ID[3] = *(PUINT8C)(0x3FFF);
    return ID;
}

UINT8 DataFlashRead(UINT16 Addr, UINT8 *Read)
{
    ROM_ADDR = DATA_FLASH_ADDR | (Addr << 1);
    if ((ROM_STATUS ^ bROM_ADDR_OK) & 0x7F)
    {
        ROM_CTRL = ROM_CMD_READ;
        if ((ROM_STATUS ^ bROM_CMD_ERR) & 0x7F)
        {
            *Read = ROM_DATA_L;
            return TRUE;
        }
    }

    return FALSE;
}

void IntoSafeWrite()
{
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;        /*���밲ȫģʽ*/
    GLOBAL_CFG |= bDATA_WE; /*Dataflashдʹ��*/
}

void ExitSafeWrite()
{
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    GLOBAL_CFG &= ~bDATA_WE; /*Dataflashдʹ�ܹر�*/
    SAFE_MOD = 0xFF;         /*�˳���ȫģʽ*/
}

// ��Ҫ�� IntoSafeWrite Ȼ�����м���ִ�� DataFlashWrite��������˳� ExitSafeWrite
UINT8 DataFlashWrite(UINT16 Addr, UINT8 Data)
{
    ROM_ADDR = DATA_FLASH_ADDR + (Addr << 1);
    ROM_DATA_L = Data;
    if (ROM_STATUS & bROM_ADDR_OK) // ������ַ��Ч
    {
        ROM_CTRL = ROM_CMD_WRITE;
        return ((ROM_STATUS ^ bROM_CMD_ERR) & 0x7F);
    }
    else
        return (bROM_ADDR_OK);
}

BOOL CheckMKDevice()
{
    UINT8 i = 0, flash[16], *ID = GetUUID();
    const UINT8 *Key = "MKDEVICE20190769";
    
    // DebugBytes("GetUUID", ID, 4);

    for (i = 0; i < sizeof(flash); i++)
    {
        if (0 == DataFlashRead(i, &flash[i]))
        {
            return FALSE;
        }
    }

    if (0 == memcmp(Key, flash, 8))
    {
        // �ǳ�ʼ����Կ�����оƬ ID һ��
        // LOG("device init\r\n");

        // ���� �� ^ - ^ + 
        flash[0x0] ^= ID[0], flash[0x1] ^= ID[1], flash[0x2] ^= ID[2], flash[0x3] ^= ID[3];
        flash[0x4] -= ID[0], flash[0x5] -= ID[1], flash[0x6] -= ID[2], flash[0x7] -= ID[3];
        flash[0x8] ^= ID[0], flash[0x9] ^= ID[1], flash[0xa] ^= ID[2], flash[0xb] ^= ID[3];
        flash[0xc] += ID[0], flash[0xd] += ID[1], flash[0xe] += ID[2], flash[0xf] += ID[3];

        // ����д�� 
            
        IntoSafeWrite();
        for (i = 0; i < sizeof(flash); i++)
        {
            if (0 == DataFlashWrite(i, flash[i]))
            {
                return FALSE;
            }
        }
        ExitSafeWrite();
    }
    else
    {
        // LOG("device ready\r\n");
        // ���ǳ�ʼ���ܳף�������豸 ID ��ԭ
        flash[0x0] ^= ID[0], flash[0x1] ^= ID[1], flash[0x2] ^= ID[2], flash[0x3] ^= ID[3];
        flash[0x4] += ID[0], flash[0x5] += ID[1], flash[0x6] += ID[2], flash[0x7] += ID[3];
        flash[0x8] ^= ID[0], flash[0x9] ^= ID[1], flash[0xa] ^= ID[2], flash[0xb] ^= ID[3];
        flash[0xc] -= ID[0], flash[0xd] -= ID[1], flash[0xe] -= ID[2], flash[0xf] -= ID[3];
        
        if (0 == memcmp(Key, flash, 8))
        {
            // LOG("device pass\r\n");
            // �Ǳ�оƬ������
            return TRUE;
        }
        else
        {
            // LOG("device other\r\n");
            // ���ǣ��������ط�����ģ������ܳ�
            IntoSafeWrite();
            for (i = 0; i < sizeof(flash); i++)
            {
                if (0 == DataFlashWrite(i, 0xFF))
                {
                    return FALSE;
                }
            }
            ExitSafeWrite();
            return FALSE;
        }
    }
    return FALSE;
}
