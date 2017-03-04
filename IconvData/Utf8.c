/*****************************************************************************************************
* FileName     :    Utf8.c
*
* Reference    :    GNU C Library
*
* Description  :    Utf8�������ģ��
*
* History      :
*       <AUTHOR>        <DATA>        <VERSION>        <DESCRIPTION>
*      YanDengxue     2009-12-19        *.**              Created
*
*****************************************************************************************************/
//====================================================================================================
// ���ļ�ʹ�õ�ͷ�ļ�
//====================================================================================================
#include "IconvBase.h"
#include "IconvData.h"

//====================================================================================================
// ����ʵ��
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//   Function: Utf8ToUcs4
//      Input: int8 *const source: ��ת��utf8�ַ����׵�ַ
//             int32 source_str_length: ��ת��utf8���ַ�������
//     Output: int32 *destination:  ת�����ucs4�ĵ�ַ
//     Return: int32: ��ǰutf8�ַ�����,����-1����ִ��ʧ��
//Description: utf8ת����unicode,�4�ֽ�
//    <AUTHOR>        <MODIFYTIME>            <REASON>
//   YanDengxue     2009-12-19 17:00          Created
//----------------------------------------------------------------------------------------------------
#pragma CODE_SECTION(Utf8ToUcs4, USER_SLOWCODE)
int32 Utf8ToUcs4(int8 const *source, int32 source_char_length, Uint32 *destination)
{
    int32  i;
    int32  lv_char_length;
    Uint32 lv_unicode_wchar;
    Uint8  lv_inital_char;

    if ((NULL == source) || (NULL == destination))
    {
        return -1;
    }

    lv_inital_char = source[0];
    if (0 == (lv_inital_char & 0x80))// ���ַ�С��0x80,��ֱ�ӿ���
    {
        lv_unicode_wchar = lv_inital_char;
        lv_char_length = 1;
    }
    else// ���ַ�����0x80,ת����Unicode
    {
        // ����UTF-8������ַ�����
        lv_char_length = 0;
        while (0 != (lv_inital_char & 0x80))
        {
            lv_char_length++;
            lv_inital_char = lv_inital_char << 1;
        }

        // ֻ����UTF-8���볤��С��6�ֽڵ��ַ�
        if ((source_char_length < lv_char_length) || (lv_char_length > 6) )
        {
            return -1;
        }

        // UTF-8����Ϊunsigned int
        lv_unicode_wchar = ((Uint32)lv_inital_char) >> lv_char_length;// lv_inital_char����Ϊuchar
        for (i = 1; i < lv_char_length; i++)
        {
            if (0x80 != (source[i] & 0xc0))// ǰ��λ����Ϊ10
            {
                return -1;
            }
            lv_unicode_wchar = (lv_unicode_wchar << 6) + (source[i] & 0x3f);
        }
    }

    *destination = lv_unicode_wchar;
    return lv_char_length;
}

