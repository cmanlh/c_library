#include "utf8.h"

int8_t utf8CodePoint(const char utf8[], Utf8CodePoint *info)
{
    uint8_t byte = utf8[0];
    if ((byte & 0x80) == 0)
    {
        info->size = 1;
        info->codePoint = byte;
    }
    else if ((byte & 0xE0) == 0xC0)
    {
        info->size = 2;
        info->codePoint = byte & 0x1F;
    }
    else if ((byte & 0xF0) == 0xE0)
    {
        info->size = 3;
        info->codePoint = byte & 0x0F;
    }
    else if ((byte & 0xF8) == 0xF0)
    {
        info->size = 4;
        info->codePoint = byte & 0x07;
    }
    else
    {
        return -1;
    }

    if (info->size > 1)
    {
        for (int i = 1; i < info->size; i++)
        {
            byte = utf8[i];

            if ((byte & 0xC0) != 0x80)
            {
                return -1;
            }
            else
            {

                info->codePoint = (info->codePoint << 6) | (byte & 0x3F);
            }
        }
    }

    return 1;
}

int8_t utf8Char(const uint32_t codePoint, Utf8CharInfo *info)
{
    if (codePoint < 0x80) // 0b0xxxxxxx
    {
        info->size = 1;
        info->point[0] = (uint8_t)codePoint;
        info->point[1] = '\0';
        info->point[2] = '\0';
        info->point[3] = '\0';
    }
    else if (codePoint < 0x800) // 0b110xxxxx 10xxxxxx
    {
        info->size = 2;
        info->point[0] = (uint8_t)(0xC0 | (codePoint >> 6));
        info->point[1] = (uint8_t)(0x80 | (codePoint & 0x3F));
        info->point[2] = '\0';
        info->point[3] = '\0';
    }
    else if (codePoint < 0x10000) // 0b1110xxxx 10xxxxxx 10xxxxxx
    {
        info->size = 3;
        info->point[0] = (uint8_t)(0xE0 | (codePoint >> 12));
        info->point[1] = (uint8_t)(0x80 | ((codePoint >> 6) & 0x3F));
        info->point[2] = (uint8_t)(0x80 | (codePoint & 0x3F));
        info->point[3] = (uint8_t)'\0';
    }
    else if (codePoint < 0x200000) // 0b11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    {
        info->size = 4;
        info->point[0] = (uint8_t)(0xF0 | (codePoint >> 18));
        info->point[1] = (uint8_t)(0x80 | ((codePoint >> 12) & 0x3F));
        info->point[2] = (uint8_t)(0x80 | ((codePoint >> 6) & 0x3F));
        info->point[3] = (uint8_t)(0x80 | (codePoint & 0x3F));
    }
    else
    {
        return -1;
    }

    return 1;
}