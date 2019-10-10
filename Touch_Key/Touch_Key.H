
#define INTERRUPT_TouchKey   0   // ����TouchKey�жϷ�ʽ

/*******************************************************************************
* Function Name  : TouchKeyQueryCylSet(UINT8 cyl)
* Description    : ����������ѯ��������
* Input          : UINT8 cyl ʱ������                  								
                   1   2ms
                   0   1ms									 
* Output         : None 
* Return         : None
*******************************************************************************/
void TouchKeyQueryCylSet1Or2ms(UINT8 cyl);

/*******************************************************************************
* Function Name  : TouchKeyChanelSelect(UINT8 ch)
* Description    : ��������ͨ��ѡ��
* Input          : UINT8 ch ����ͨ��
* Output         : None
* Return         : �ɹ� SUCCESS
                   ʧ�� FAIL
*******************************************************************************/
UINT8 TouchKeyChanelSelect(UINT8 ch);

