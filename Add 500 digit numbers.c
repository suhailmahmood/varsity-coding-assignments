#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{

    char num1[501], num2[501], *sum, ch;
    int len1, len2, bigger_len, i, nm1, nm2, temp, carry=0;
    while(scanf("%s %s", num1, num2) != EOF)
    {
        len1= strlen(num1);
        len2= strlen(num2);
        i= (len1>len2) ? len1 : len2;
        bigger_len=i;
        sum=(char *)malloc((bigger_len+2)*sizeof(char));                     /* Making size of 'sum' 1 greater than the bigger number */

        for (i; i>=0; i--)
        {
            nm1= (len1<=0) ? 0 : (num1[len1-1]-48);                            /* Using ASCII value of character to get corresponding Number, eg. from 55 (ASCII of 7) we get 7 */
            nm2= (len2<=0) ? 0 : (num2[len2-1]-48);
            temp= carry+nm1+nm2;
            carry=temp/10;
            ch= temp%10 + 48;                                                             /* Using ASCII value to get corresponding Character, eg. from 7 we get 55 (ASCII of 7)*/
            sum[i+1]= ch;                                                                      /* Storing the ones of addition into sum  from back forward */
            len1--;
            len2--;
        }
        sum[bigger_len+2]=0;
        strrev(sum);
        if (sum[bigger_len]=='0')                                                           /* If first digit is a zero, putting null in its place after it has been reversed */
            sum[bigger_len]=0;
        else
            sum[bigger_len+1]=0;                                                            /* If not zero, putting null after if */
        strrev(sum);
        printf("%s\n", sum);
    }

    return 0;
}
