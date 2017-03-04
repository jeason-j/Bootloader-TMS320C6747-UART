/*****************************************************************************************************
* FileName:                    Spi.c
*
* Description:                 Spi���ú���
*
* Author:                      YanDengxue, Fiberhome-Fuhua
*
* Rev History:
*       <Author>        <Data>        <Hardware>     <Version>        <Description>
*     YanDengxue   2011-03-29 15:30       --           1.00             Create
*****************************************************************************************************/
//====================================================================================================
// ���ļ�ʹ�õ�ͷ�ļ�
//====================================================================================================
// �Զ���ͷ�ļ�
#include "UserTypesDef.h"
#include "Debug.h"
#include "C6747Register.h"
#include "SystemBase.h"
#include "Spi.h"

//====================================================================================================
// ����ʵ��
//====================================================================================================
//----------------------------------------------------------------------------------------------------
// �ӿں���
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//   Function: SPIXferOneByte
//      Input: SPI_REGS *pSPI: ������SPI
//             Uint32 data_tx: ���������
//             Uint8 flags: �Ƿ�������ʶ
//     Output: void
//     Return: Uint8: SPI����
//Description: SPI���������������
//    <AUTHOR>        <MODIFYTIME>            <REASON>
//   YanDengxue     2011-03-21 16:30           Create
//----------------------------------------------------------------------------------------------------
Uint8 SPIXferOneByte(SPI_REGS *pSPI, Uint8 data_tx, Uint8 flags)
{
    VUint32 lv_temp;

    // do an empty read to clear the current contents
    lv_temp = pSPI->SPIBUF;

    lv_temp = data_tx;
    if (0 == flags)
    {
        lv_temp |= (1 << 28);
    }

    while (0 != (pSPI->SPIBUF & 0x20000000));
    pSPI->SPIDAT1 = lv_temp;
    while (0 != (pSPI->SPIBUF & 0x80000000));
    lv_temp = pSPI->SPIBUF;

    return (Uint8)lv_temp;

}


//----------------------------------------------------------------------------------------------------
//   Function: SPIXferOneByte
//      Input: SPI_REGS *pSPI: ������SPI
//             Uint32 length: ��������������
//             const Uint8 *dout: �������buffer
//             Uint8 flags: �Ƿ�������ʶ
//     Output: Uint8 *din: ��������buffer
//     Return: Uint8: SPI����
//Description: ����ִ�����
//    <AUTHOR>        <MODIFYTIME>            <REASON>
//   YanDengxue     2011-03-21 16:30           Create
//----------------------------------------------------------------------------------------------------
int32 SPIXferBytes(SPI_REGS *pSPI, int32 length, const Uint8 *dout, Uint8 *din, Uint8 flags)
{
    Uint32      i;
    VUint32 lv_temp;
    const Uint8 *lv_p_tx_buffer;
    Uint8       *lv_p_rx_buffer;

    if (0 == length)
    {
        if (0 != flags)
        {
            while (0 != (pSPI->SPIBUF & 0x20000000));
            pSPI->SPIDAT1 = 0;
            while (0 != (pSPI->SPIBUF & 0x80000000));
        }

        return NORMAL_SUCCESS;
    }

    // do an empty read to clear the current contents
    lv_temp = pSPI->SPIBUF;

    lv_p_tx_buffer = dout;
    lv_p_rx_buffer = din;

    for (i = 0; i < length - 1; i++)
    {
        lv_temp = (1 << 28);
        if (NULL != lv_p_tx_buffer)
        {
            lv_temp |= *lv_p_tx_buffer;
            lv_p_tx_buffer++;
        }

        while (0 != (pSPI->SPIBUF & 0x20000000 ));
        pSPI->SPIDAT1 = lv_temp;
        while (0 != (pSPI->SPIBUF & 0x80000000));
        lv_temp = pSPI->SPIBUF;

        if (NULL != lv_p_rx_buffer)
        {
            *lv_p_rx_buffer = lv_temp;
            lv_p_rx_buffer++;
        }
    }

    if (0 != flags)
    {
        lv_temp = 0;
    }
    else
    {
        lv_temp = (1 << 28);
    }

    if (NULL != lv_p_tx_buffer)
    {
        lv_temp |= *lv_p_tx_buffer;
    }

    while (0 != (pSPI->SPIBUF & 0x20000000 ));
    pSPI->SPIDAT1 = lv_temp;
    while (0 != (pSPI->SPIBUF & 0x80000000));
    lv_temp = pSPI->SPIBUF;

    if (NULL != lv_p_rx_buffer)
    {
        *lv_p_rx_buffer = lv_temp;
    }

    return NORMAL_SUCCESS;
}

