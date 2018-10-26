#include <stdio.h>
#include <stdlib.h>
#define max(x,y) (((x) > (y)) ? (x) : (y))


char* lcs(char *str1, char *str2)
{
    char *LCSstr = (char*)malloc(100);
    int i, j, l, n1, n2;
    int LCS[100][100];

    for(n1=0; str1[n1]!=0; n1++);
    for(n2=0; str2[n2]!=0; n2++);

    for (i=0; i<=n1; i++)
    {
        for (j=0; j<=n2; j++)
        {
            if (i == 0 || j == 0)
                LCS[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                LCS[i][j] = LCS[i-1][j-1] + 1;
            else
                LCS[i][j] = max(LCS[i][j-1], LCS[i-1][j]);
        }
    }

    i = n1, j = n2;
    l = LCS[n1][n2];
    LCSstr[l--] = 0;
    while (i>=0 && j>=0)
    {
        if (str1[i-1] == str2[j-1])
        {
            LCSstr[l--] = str1[i-1];
            i--;
            j--;
        }
        else if (LCS[i-1][j] == LCS[i][j])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    return LCSstr;
}


int main() {
    char str1[101], str2[101];

    printf("Enter 1st string: ");
    scanf("%[^\n]", str1);
    getchar();

    printf("Enter 2nd string: ");
    scanf("%[^\n]", str2);

    char *LCSstr = lcs(str1, str2);
    printf("%s\n", LCSstr);
    free(LCSstr);

    return 0;
}
