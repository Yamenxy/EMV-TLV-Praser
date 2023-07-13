#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    char* Tag;
    char* Length;
    char* Value;
} TLVEntry;

int hexToDec(char* hex) {
    int len = 0;
    int dec = 0;
    int c=0;
    len = strlen(hex);

    for (int i = 0; i < len; i++) {
        int digitValue;

        if (hex[i] >= '0' && hex[i] <= '9')
        {
            digitValue = hex[i] - '0';
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            digitValue = hex[i] - 'A' + 10;
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f')
        {
            digitValue = hex[i] - 'a' + 10;
        }
        else
        {
            printf("INVALID INPUT!\a\n");
            return -1;
        }

        dec += digitValue * pow(16, len - i - 1);
    }
    return dec;
    }

TLVEntry* parseTLV(char* data, int count)
{
    int c,dec,x=0 ;
    TLVEntry* tlv = malloc(count * sizeof(TLVEntry));

    int index = 0;
    for (int i = 0; i < count; i++)
    {
        tlv[i].Tag = malloc(3 * sizeof(char));
        tlv[i].Length = malloc(3 * sizeof(char));

        strncpy(tlv[i].Tag, data + index, 2);
        tlv[i].Tag[2] = '\0';

        strncpy(tlv[i].Length, data + index + 2, 2);
        tlv[i].Length[2] = '\0';

        int dec = hexToDec(tlv[i].Length)*2;
        if (dec!=-1)
        {
            int u=tlv[i].Value = malloc((dec + 1) * sizeof(char));
            strncpy(tlv[i].Value, data + index + 4, dec);
            c=count-4;
            if(c!=dec)
            {
                printf("INVALIDE Length!\a\n");
                return -1;
                break;
            }
            tlv[i].Value[dec] = '\0';
        }
}
  return tlv;
}

void printTLVEntries(TLVEntry* tlv, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Tag: %s\n", tlv[i].Tag);
        printf("Length: %s\n", tlv[i].Length);
        printf("Value: %s\n\n ", tlv[i].Value);
        break;
    }
}

int main()
{
    char data2[1000];
    int c = 0,x=0;
r:
    y:
    c = 0;
    x=0;
    printf("Enter The Data(WITHOUT SPACE): ");
    gets(data2);
    for (int i = 0; data2[i] != '\0'; i++)
    {
        if(data2[i]==' ')
        {
            printf("INVALID INPUT!\a\n");
            goto r;
        }
    }

    for (int i = 0; data2[i] != 0; i++)
    {
        c++;
    }

     for (int i = 0; i <= 2; i++) {
    if (data2[i] != 'A' && data2[i] != 'B' && data2[i] != 'C' && data2[i] != 'D' && data2[i] != 'E' && data2[i] != 'F' && data2[i] != 'a' && data2[i] != 'b' && data2[i] != 'c' && data2[i] != 'd' && data2[i] != 'e' && data2[i] != 'f' && data2[i] > '9')
    {
        x++;
    }
    }
    if (x != 0) {
        printf("THE TAG MUST BE HEX NUMBER!\a\n");
        goto r;
    }

    for (int i = 3; i <= 4; i++) {
    if (data2[i] != 'A' && data2[i] != 'B' && data2[i] != 'C' && data2[i] != 'D' && data2[i] != 'E' && data2[i] != 'F' && data2[i] != 'a' && data2[i] != 'b' && data2[i] != 'c' && data2[i] != 'd' && data2[i] != 'e' && data2[i] != 'f' && data2[i] > '9')
    {
        x++;
    }
    }
    if (x != 0) {
        printf("THE LENGTH MUST BE HEX NUMBERS!\a\n");
        goto r;
    }

    for (int i = 5; i <= c; i++) {
    if (data2[i] != 'A' && data2[i] != 'B' && data2[i] != 'C' && data2[i] != 'D' && data2[i] != 'E' && data2[i] != 'F' && data2[i] != 'a' && data2[i] != 'b' && data2[i] != 'c' && data2[i] != 'd' && data2[i] != 'e' && data2[i] != 'f' && data2[i] > '9')
    {
        x++;
    }
    }

    if (x != 0) {
        printf("THE VALUE MUST BE HEX NUMBERS!\a\n");
        goto r;
    }

     else
    {
        if (c % 2 != 0)
    {
        printf("INVALID DATA!\a\n");
        goto r;
    }
    else
    {
        TLVEntry* tlv = parseTLV(data2, c );
        if (tlv==-1)
        {
            goto y;
        }
        printTLVEntries(tlv, c );

        for (int i = 0; i < c / 2; i++)
        {
            free(tlv[i].Tag);
            free(tlv[i].Length);
            free(tlv[i].Value);
        }
        free(tlv);

    }
    }
    return 0;
}
