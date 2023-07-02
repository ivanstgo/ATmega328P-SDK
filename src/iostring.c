#include "iostring.h"

const char *int2string(int a)
{
    static char s[7];
    for (int i = 0; i < 7; i++)
        s[i] = 0x00;
    if (a < 0)
    {
        a *= -1;
        s[0] = '-';
    }
    char digits[5];
    int i = 0;
    while (a / 10)
    {
        digits[i++] = '0' + a % 10;
        a /= 10;
    }
    digits[i] = '0' + a;
    for (int j = (s[0] == '-' ? ++i : i); j >= (s[0] == '-' ? 1 : 0); j--)
    {
        s[j] = digits[i - j];
    }
    return s;
}

const char *uint2string(unsigned int a)
{
    static char s[6];
    for (int i = 0; i < 6; i++)
        s[i] = 0x00;
    char digits[5];
    int i = 0;
    while (a / 10)
    {
        digits[i++] = '0' + a % 10;
        a /= 10;
    }
    digits[i] = '0' + a;
    for (int j = i; j >= 0; j--)
    {
        s[j] = digits[i - j];
    }
    return s;
}

const char *byte2hstring(unsigned char a)
{
    static char s[5];
    s[0] = '0';
    s[1] = 'x';
    s[2] = a / 16 < 10 ? '0' + a / 16 : '7' + a / 16;
    s[3] = a % 16 < 10 ? '0' + a % 16 : '7' + a % 16;
    s[4] = 0x00;
    return s;
}

const char *float2string(float a, unsigned char n)
{
    static char s[12];
    for (int i = 0; i < 12; i++)
        s[i] = 0x00;
    if (a < 0)
    {
        a *= -1;
        s[0] = '-';
    }
    unsigned int bp = (unsigned int)a;
    a -= bp;
    for (int i = 0; i < n; i++)
        a *= 10.0f;
    unsigned int ap = (unsigned int)a;
    const char *temp = uint2string(bp);
    int i = s[0] == '-' ? 1 : 0;
    int j = 0;
    while (*(temp + j))
    {
        s[i++] = temp[j++];
    }
    j = 0;
    s[i++] = '.';
    temp = uint2string(ap);
    while (*(temp + j))
    {
        s[i++] = temp[j++];
    }
    return s;
}