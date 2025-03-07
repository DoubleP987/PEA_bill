#include <stdio.h>
int main(){
    int n;
    while(printf("Enter The Value: "), scanf("%d", &n)){
        printf("ผิด\n");
        while(getchar() != '\n');
    }
    printf("Your Number is %d", n);

    return 0;
}