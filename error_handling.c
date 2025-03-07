#include <stdio.h>
int main(){
    int n;
    printf("ป้อนตัวเลขอะไรก็ได้ (1 - 100)\n");
    while(printf("Enter The Value: "), scanf("%d", &n) != 1 || n < 1 || n > 100){
        printf("ผิด\n");
        while(getchar() != '\n');
    }
    printf("Your Number is %d", n);

    return 0;
}