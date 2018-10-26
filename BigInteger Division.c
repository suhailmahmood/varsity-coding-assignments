#include <stdio.h>
#include <string.h>

void trim(char *str)
{
    int i=0, len = strlen(str);
    char *temp = (char*)malloc(len+1);
    strcpy(temp, str);
    while(str[i] == '0')
        i++;
    if(len == i)
    {
        strcpy(str, "0");
        return;
    }
    strncpy(str, temp+i, len-i);
    str[len-i] = 0;
}

int main()
{
    char num[] = "1100000", quot[30];
    int n = 100000, div, rem, pquot, index = 0, i;
    short flag = 0;
    div = 0;
    for(i=0; num[i]!=0; i++)
    {
        div = div * 10 + num[i] - '0';
        if(div < n)
        {
            if(flag)
                quot[index++] = '0';
            flag = 1;
            if(num[i+1] == 0)
                rem = div % n;
            continue;
        }
        else
        {
            rem = div % n;
            pquot = div / n;
            quot[index++] = pquot + '0';
            div = rem;
            flag = 0;
        }
    }
    quot[index] = 0;
    trim(quot);
    printf("Quotient: %s\nRemainder: %d", quot, rem);
    return 0;
}
