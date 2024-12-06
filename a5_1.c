#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int major(int,int,int);
int xx(int);

int main()
{
    int key[64] = {0, };
    int x_r[19] = {0, };
    int y_r[22] = {0, };
    int z_r[23] = {0, };
    
    printf("키를 입력하시오(64비트): ");
    for(int i=0; i<64; i++)
    {
        scanf("%1d",&key[i]);
        if(key[i] != 0 && key[i] != 1)
        {
            printf("키의 값을 0 또는 1로 이루어진 숫자로 입력하십시오");
            return 0;
        }
    }

    for(int i=0; i<19; i++)
    {
        x_r[i] = key[i];
    }
    for(int i=0; i<22; i++)
    {
        y_r[i] = key[i+19];
    }
    for(int i=0; i<23; i++)
    {
        z_r[i] = key[i+41];
    }

    printf("\nkey값: ");
    for(int i=0; i<64; i++)
    {
        printf("%d",key[i]);
    }
    printf("\nX 레지스터 초기값: ");
    for(int i=0; i<19; i++)
    {
        printf("%d",x_r[i]);
    }
    printf("\nY 레지스터 초기값: ");  
    for(int i=0; i<22; i++)
    {
        printf("%d",y_r[i]);
    }
    printf("\nZ 레지스터 초기값: ");  
    for(int i=0; i<23; i++)
    {
        printf("%d",z_r[i]);
    }

    char plain_text[]={0, };   
    int plain_s[999] = {0, };

    printf("\n\n평문을 입력하시오: ");
    scanf(" %[^\n]s",plain_text);

    printf("\nplainstream: ");
    for(int j=0; j<strlen(plain_text); j++)
    {
        for (int k = 7; k >= 0; --k)
        {
            int bit_8 = plain_text[j] >> k & 1; 
            plain_s[8*j+7-k] = bit_8;           
            printf("%d", bit_8);
        }
    }

    int keystream[999] = {0, };

    printf("\n\nkeystream: ");
    for(int i=0; i<strlen(plain_text)*8; i++)
    {
        int m = major(x_r[8],y_r[10],z_r[10]);
        if(x_r[8] == m)
        {
            int x = x_r[13] ^ x_r[16] ^ x_r[17] ^ x_r[18];
            for(int i=18; i>0; i--)
            {
                x_r[i] = x_r[i-1];
            }
            x_r[0] = x;         
        }
        if(y_r[10] == m)
        {
            int y = y_r[20] ^ y_r[21];
            for(int i=21; i>0; i--)
            {
                y_r[i] = y_r[i-1];
            }
            y_r[0] = y;           
        }
        if(z_r[10] == m)
        {
            int z = z_r[7] ^ z_r[20] ^ z_r[21] ^ z_r[22];
            for(int i=22; i>0; i--)
            {
                z_r[i] = z_r[i-1];
            }
            z_r[0] = z;
        }

        keystream[i] = x_r[18] ^ y_r[21] ^ z_r[22];
        printf("%d",keystream[i]);
    }

    printf("\n\ncipherstream: ");

    int AA = strlen(plain_text);
    int BB = strlen(plain_text)*8;
    
    int cipher_s[BB];
    char cipher_text[AA];

    for(int i=0; i<strlen(plain_text)*8; i++)
    {
        cipher_s[i] = plain_s[i] ^ keystream[i];
        printf("%d",cipher_s[i]);
    }
    
    printf("\n\n암호문은: ");
    for(int i=0; i<strlen(plain_text); i++)
    {
        int temp = 0;
        for(int j=0; j<8; j++)
        {
            temp = temp + (cipher_s[i*8+7-j] * xx(j));
        }
        cipher_text[i] = temp;
        printf("%c",cipher_text[i]);
    }

    int key_1[64] = {0, };
    int x_r_1[19] = {0, };
    int y_r_1[22] = {0, };
    int z_r_1[23] = {0, };
    
    printf("\n\n");
    printf("\n키를 입력하시오(64비트) / 동일 키 입력: ");
    for(int i=0; i<64; i++)
    {
        scanf("%1d",&key_1[i]);
        if(key_1[i] != 0 && key_1[i] != 1)
        {
            printf("키의 값을 0 또는 1로 이루어진 숫자로 입력하십시오");
            return 0;
        }
    }

    for(int i=0; i<19; i++)
    {
        x_r_1[i] = key_1[i];
    }
    for(int i=0; i<22; i++)
    {
        y_r_1[i] = key_1[i+19];
    }
    for(int i=0; i<23; i++)
    {
        z_r_1[i] = key_1[i+41];
    }

    int keystream_1[999] = {0, };

    printf("\nkeystream_1: ");
    for(int i=0; i<sizeof(cipher_s)/sizeof(int); i++)
    {
        int m = major(x_r_1[8],y_r_1[10],z_r_1[10]);

        if(x_r_1[8] == m)
        {
            int x = x_r_1[13] ^ x_r_1[16] ^ x_r_1[17] ^ x_r_1[18];
            for(int i=18; i>0; i--)
            {
                x_r_1[i] = x_r_1[i-1];
            }
            x_r_1[0] = x;         
        }
        if(y_r_1[10] == m)
        {
            int y = y_r_1[20] ^ y_r_1[21];
            for(int i=21; i>0; i--)
            {
                y_r_1[i] = y_r_1[i-1];
            }
            y_r_1[0] = y;           
        }
        if(z_r_1[10] == m)
        {
            int z = z_r_1[7] ^ z_r_1[20] ^ z_r_1[21] ^ z_r_1[22];
            for(int i=22; i>0; i--)
            {
                z_r_1[i] = z_r_1[i-1];
            }
            z_r_1[0] = z;
        }
        keystream_1[i] = x_r_1[18] ^ y_r_1[21] ^ z_r_1[22];

        printf("%d",keystream_1[i]);
    }

    printf("\n\nplainstream_1: ");

    int CC = sizeof(cipher_s)/sizeof(int);
    int DD = (sizeof(cipher_s)/sizeof(int))/8;

    int plain_s_1[CC];
    char plain_text_1[DD];

    for(int i=0; i<sizeof(cipher_s)/sizeof(int); i++)
    {
        plain_s_1[i] = cipher_s[i] ^ keystream_1[i];
        printf("%d",plain_s_1[i]);
    }
    
    printf("\n\n복호화된 평문은: ");
    for(int i=0; i<(sizeof(cipher_s)/sizeof(int))/8; i++)
    {
        int temp = 0;
        for(int j=0; j<8; j++)
        {
            temp = temp + (plain_s_1[i*8+7-j] * xx(j));
        }
        plain_text_1[i] = temp;
        printf("%c",plain_text[i]);
    }

    printf("\n\n");
    return 0;
}

int major(int x,int y,int z)
{
    int m;
    if(x + y + z >= 2)
    {
        m = 1;
    }
    if(x + y + z < 2)
    {
        m = 0;
    }
    return m;
}

int xx(int j)
{
    int z=1;
    for(int i=0; i<j; i++)
    {
        z = z*2;
    }
    return z;
}