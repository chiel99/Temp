#include <stdio.h>
#include <string.h>

void reverse_str(char* str)
{
    int i, j;
    char c;
    int len = strlen(str);
    for (i = 0, j = len-1 ; i < len/2 ; i++ , j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

int main()
{
    char str[128];
    memset(str, 0, sizeof(str));
    scanf("%s", str);
    printf("Your input is [%s]\n", str);
    reverse_str(str);
    printf("After reversing: [%s]\n", str);
    return 0;
}
