#include <stdio.h>
#include <wchar.h>

int main(int argc, char const *argv[])
{
    printf("%s\n", "中国人民共和国万岁!");
    printf("%d\n", sizeof(char));
    wprintf("%ld\n", '中');
    return 0;
}
