#include <stdio.h>
#include <string.h>
/*
    for(int i=0;i<31;i++)
    {
        if(i%2==0)
        {
            flag[i*2]=((flag[i*2]&0xf0)>>4)|((flag[i*2]&0xf)<<4);
            flag[i*2]^=a;
            a=flag[i*2];
            flag[(i*2)+1]^=b;
            b=flag[(i*2)+1];
        }
        else
        {
            flag[i*2]^=b;
            b=flag[i*2];
            flag[(i*2)+1]=((flag[(i*2)+1]&0xf0)>>4)|((flag[(i*2)+1]&0xf)<<4);
            flag[(i*2)+1]^=a;
            a=flag[(i*2)+1];
        }
    }

make:
for i in range(31):
    if i%2==0:
        print('flag[%d]=((flag[%d]&0xf0)>>4)|((flag[%d]&0xf)<<4);'%(i*2,i*2,i*2))
        print('flag[%d]^=a;'%(i*2))
        print('a=flag[%d];'%(i*2))
        print('flag[%d]^=b;'%((i*2)+1))
        print('b=flag[%d];'%((i*2)+1))
    else:
        print('flag[%d]^=b;'%(i*2))
        print('b=flag[%d];'%(i*2))
        print('flag[%d]=((flag[%d]&0xf0)>>4)|((flag[%d]&0xf)<<4);'%((i*2)+1,(i*2)+1,(i*2)+1))
        print('flag[%d]^=a;'%((i*2)+1))
        print('a=flag[%d];'%((i*2)+1))


*/
int encrypt(unsigned char *flag)
{
    //n1ctf{ThE_X64_StRuCtUrEd_eXcEpTiOn_hAnDlInG_Is_sO_InTeReStInG.}
    unsigned char a = 'N', b = '1';

    // for (int i = 3; i < 31; i++)
    // {
    //     if (i % 2 == 0)
    //     {
    //         flag[i * 2] = ((flag[i * 2] & 0xf0) >> 4) | ((flag[i * 2] & 0xf) << 4);
    //         flag[i * 2] ^= a;
    //         a = flag[i * 2];
    //         flag[(i * 2) + 1] ^= b;
    //         b = flag[(i * 2) + 1];
    //     }
    //     else
    //     {
    //         flag[i * 2] ^= b;
    //         b = flag[i * 2];
    //         flag[(i * 2) + 1] = ((flag[(i * 2) + 1] & 0xf0) >> 4) | ((flag[(i * 2) + 1] & 0xf) << 4);
    //         flag[(i * 2) + 1] ^= a;
    //         a = flag[(i * 2) + 1];
    //     }
    // }
    flag[6]^=b;
    b=flag[6];
    flag[7]=((flag[7]&0xf0)>>4)|((flag[7]&0xf)<<4);
    flag[7]^=a;
    a=flag[7];
    flag[8]=((flag[8]&0xf0)>>4)|((flag[8]&0xf)<<4);
    flag[8]^=a;
    a=flag[8];
    flag[9]^=b;
    b=flag[9];
    flag[10]^=b;
    b=flag[10];
    flag[11]=((flag[11]&0xf0)>>4)|((flag[11]&0xf)<<4);
    flag[11]^=a;
    a=flag[11];
    flag[12]=((flag[12]&0xf0)>>4)|((flag[12]&0xf)<<4);
    flag[12]^=a;
    a=flag[12];
    flag[13]^=b;
    b=flag[13];
    flag[14]^=b;
    b=flag[14];
    flag[15]=((flag[15]&0xf0)>>4)|((flag[15]&0xf)<<4);
    flag[15]^=a;
    a=flag[15];
    flag[16]=((flag[16]&0xf0)>>4)|((flag[16]&0xf)<<4);
    flag[16]^=a;
    a=flag[16];
    flag[17]^=b;
    b=flag[17];
    flag[18]^=b;
    b=flag[18];
    flag[19]=((flag[19]&0xf0)>>4)|((flag[19]&0xf)<<4);
    flag[19]^=a;
    a=flag[19];
    flag[20]=((flag[20]&0xf0)>>4)|((flag[20]&0xf)<<4);
    flag[20]^=a;
    a=flag[20];
    flag[21]^=b;
    b=flag[21];
    flag[22]^=b;
    b=flag[22];
    flag[23]=((flag[23]&0xf0)>>4)|((flag[23]&0xf)<<4);
    flag[23]^=a;
    a=flag[23];
    flag[24]=((flag[24]&0xf0)>>4)|((flag[24]&0xf)<<4);
    flag[24]^=a;
    a=flag[24];
    flag[25]^=b;
    b=flag[25];
    flag[26]^=b;
    b=flag[26];
    flag[27]=((flag[27]&0xf0)>>4)|((flag[27]&0xf)<<4);
    flag[27]^=a;
    a=flag[27];
    flag[28]=((flag[28]&0xf0)>>4)|((flag[28]&0xf)<<4);
    flag[28]^=a;
    a=flag[28];
    flag[29]^=b;
    b=flag[29];
    flag[30]^=b;
    b=flag[30];
    flag[31]=((flag[31]&0xf0)>>4)|((flag[31]&0xf)<<4);
    flag[31]^=a;
    a=flag[31];
    flag[32]=((flag[32]&0xf0)>>4)|((flag[32]&0xf)<<4);
    flag[32]^=a;
    a=flag[32];
    flag[33]^=b;
    b=flag[33];
    flag[34]^=b;
    b=flag[34];
    flag[35]=((flag[35]&0xf0)>>4)|((flag[35]&0xf)<<4);
    flag[35]^=a;
    a=flag[35];
    flag[36]=((flag[36]&0xf0)>>4)|((flag[36]&0xf)<<4);
    flag[36]^=a;
    a=flag[36];
    flag[37]^=b;
    b=flag[37];
    flag[38]^=b;
    b=flag[38];
    flag[39]=((flag[39]&0xf0)>>4)|((flag[39]&0xf)<<4);
    flag[39]^=a;
    a=flag[39];
    flag[40]=((flag[40]&0xf0)>>4)|((flag[40]&0xf)<<4);
    flag[40]^=a;
    a=flag[40];
    flag[41]^=b;
    b=flag[41];
    flag[42]^=b;
    b=flag[42];
    flag[43]=((flag[43]&0xf0)>>4)|((flag[43]&0xf)<<4);
    flag[43]^=a;
    a=flag[43];
    flag[44]=((flag[44]&0xf0)>>4)|((flag[44]&0xf)<<4);
    flag[44]^=a;
    a=flag[44];
    flag[45]^=b;
    b=flag[45];
    flag[46]^=b;
    b=flag[46];
    flag[47]=((flag[47]&0xf0)>>4)|((flag[47]&0xf)<<4);
    flag[47]^=a;
    a=flag[47];
    flag[48]=((flag[48]&0xf0)>>4)|((flag[48]&0xf)<<4);
    flag[48]^=a;
    a=flag[48];
    flag[49]^=b;
    b=flag[49];
    flag[50]^=b;
    b=flag[50];
    flag[51]=((flag[51]&0xf0)>>4)|((flag[51]&0xf)<<4);
    flag[51]^=a;
    a=flag[51];
    flag[52]=((flag[52]&0xf0)>>4)|((flag[52]&0xf)<<4);
    flag[52]^=a;
    a=flag[52];
    flag[53]^=b;
    b=flag[53];
    flag[54]^=b;
    b=flag[54];
    flag[55]=((flag[55]&0xf0)>>4)|((flag[55]&0xf)<<4);
    flag[55]^=a;
    a=flag[55];
    flag[56]=((flag[56]&0xf0)>>4)|((flag[56]&0xf)<<4);
    flag[56]^=a;
    a=flag[56];
    flag[57]^=b;
    b=flag[57];
    flag[58]^=b;
    b=flag[58];
    flag[59]=((flag[59]&0xf0)>>4)|((flag[59]&0xf)<<4);
    flag[59]^=a;
    a=flag[59];
    flag[60]=((flag[60]&0xf0)>>4)|((flag[60]&0xf)<<4);
    flag[60]^=a;
    a=flag[60];
    flag[61]^=b;
    b=flag[61];
    int f = 1;
    
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] != 700)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] - flag[7] != 500)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] != 1056)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] - flag[9] != 998)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] != 1212)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] != 1467)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] - flag[12] != 1279)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] - flag[13] != 1594)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] - flag[14] != 1606)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] != 2077)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] != 2299)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] != 2326)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] - flag[18] != 2238)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] - flag[19] != 2261)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] - flag[20] != 2363)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] != 2813)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] != 2924)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] - flag[23] != 2786)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] - flag[24] != 2935)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] - flag[25] != 3179)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] != 3281)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] != 3354)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] - flag[28] != 3325)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] != 3417)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29]+ flag[30] != 3535)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] - flag[31] != 3396)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] - flag[32] != 3547)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] != 3825)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] - flag[34] != 3754)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] != 4145)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] != 4382)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] != 4423)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] != 4532)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] - flag[39] != 4489)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] != 4766)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] != 4769)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] - flag[42] != 4701)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] != 4911)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] != 5133)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] - flag[45] != 5078)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] - flag[46] != 5084)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] - flag[47] != 5059)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] - flag[48] != 5496)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] - flag[49] != 5499)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] - flag[50] != 5483)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] - flag[51] != 5484)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] != 6176)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] != 6203)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] != 6276)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] - flag[55] != 6044)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] + flag[55] + flag[56] != 6729)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] + flag[55] + flag[56] - flag[57] != 6668)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] + flag[55] + flag[56] + flag[57] + flag[58] != 6906)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] + flag[55] + flag[56] + flag[57] + flag[58] + flag[59] != 6965)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] + flag[55] + flag[56] + flag[57] + flag[58] + flag[59] - flag[60] != 6886)
        f = 0;
    if (flag[0] + flag[1] + flag[2] + flag[3] + flag[4] + flag[5] + flag[6] + flag[7] + flag[8] + flag[9] + flag[10] + flag[11] + flag[12] + flag[13] + flag[14] + flag[15] + flag[16] + flag[17] + flag[18] + flag[19] + flag[20] + flag[21] + flag[22] + flag[23] + flag[24] + flag[25] + flag[26] + flag[27] + flag[28] + flag[29] + flag[30] + flag[31] + flag[32] + flag[33] + flag[34] + flag[35] + flag[36] + flag[37] + flag[38] + flag[39] + flag[40] + flag[41] + flag[42] + flag[43] + flag[44] + flag[45] + flag[46] + flag[47] + flag[48] + flag[49] + flag[50] + flag[51] + flag[52] + flag[53] + flag[54] + flag[55] + flag[56] + flag[57] + flag[58] + flag[59] + flag[60] + flag[61] != 7134)
        f = 0;
    
    return f;
}

int main(int argc, char const *argv[])
{
    char flag[100] = "n1ctf{ThE_X64_StRuCtUrEd_eXcEpTiOn_hAnDlInG_Is_sO_InTeReStInG.}";
    int lens = strlen(flag);
    printf("%s\n", flag);
    if(encrypt((unsigned char *)&flag))
    {
        printf("Yes!\n");
    }
    else
    {
        printf("No!\n");
    }
    
    for (int i = 0; i < lens; i++)
    {
        printf("0x%02x,", flag[i] & 0xff);
    }
    putchar('\n');
    for (int i = 0; i < lens; i++)
        printf("%c ", flag[i]);
    return 0;
}
