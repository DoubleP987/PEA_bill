#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

const float Ft = 0.3672;

void menu();
void vat(); //vat 7% calculation
double residentialNormalRate(int unit);
double residentialTOURate();
void getInput(char *msg, int *value);
void getOption(char *msg, int *choice, int option);

int main(){
    int unit;
    double cost;
    // menu();
    // printf("Enter units: ");
    // scanf("%d", &unit);
    cost = residentialTOURate();
    printf("%.2lf", cost);

    return 0;
}
void getInput(char *msg, int *value){
    while(printf("%s", msg), scanf("%d", value) != 1){
        printf("ข้อมูลไม่ถูกต้อง\n");
        while(getchar() != '\n');
    }
}
void getOption(char *msg, int *choice, int option){
    while(printf("%s", msg), scanf("%d", choice) != 1 || *choice < 1 || *choice > option){
        printf("ตัวเลือกไม่ถูกต้อง\n");
        while(getchar() != '\n');
    }
}
void menu(){
    int choice;
    printf("(1) 1.1 บ้านอยู่อาศัย (อัตราปกติ)\n");
    printf("(2) 1.2 บ้านอยู่อาศัย (อัตรา TOU)\n");
    printf("(3) 2.1 กิจการขนาดเล็ก (อัตราปกติ)\n");
    printf("(4) 2.2 กิจการขนาดเล็ก (อัตรา TOU)\n");
    printf("(5) 3.1 กิจการขนาดกลาง\n");
    printf("(6) 3.2 กิจการขนาดกลาง (อัตรา TOU)\n");
    printf("(7) 4.1 กิจการขนาดใหญ่ (อัตรา TOD)\n");
    printf("(8) 4.2 กิจการขนาดใหญ่ (อัตรา TOU)\n");
    printf("(9) 5.1 กิจการเฉพาะอย่าง (อัตราปกติ)\n");
    printf("(10) 5.2 กิจการเฉพาะอย่าง (อัตรา TOU)\n");
    printf("(11) 6.1 องค์กรที่ไม่แสวงหากำไร\n");
    printf("(12) 6.2 องค์กรที่ไม่แสวงหากำไร (อัตรา TOU)\n");
    printf("(13) 7.1 สูบน้ำเพื่อการเกษตร\n");
    printf("(14) 7.2 สูบน้ำเพื่อการเกษตร (อัตรา TOU)\n");
    printf("(15) 8. ไฟฟ้าชั่วคราว\n");
    printf("เลือกประเภทไฟฟ้า(1 - 15):\n");
    scanf("%d", &choice);
    // switch(choice){
    //     case '1':
    //         break;
    //     case '2':
    //         break;
    //     case '3':
    //         break;
    //     case '4':
    //         break;
    //     case '5':
    //         break;
    //     case '6':
    //         break;
    //     case '7':
    //         break;
    //     case '8':
    //         break;
    //     case '9':
    //         break;
    //     case '10':
    //         break;
    //     case '11':
    //         break;
    //     case '12':
    //         break;
    //     case '13':
    //         break;
    //     case '14':
    //         break;
    //     case '15':
    //         break;
    // }
}
void vat(double *cost){
    *cost += ((*cost + Ft) / 100 * 7);
}
double residentialNormalRate(int unit){ //ประเภทที่ 1.1 บ้านอยู่อาศัย (อัตราปกติ)
    double cost = 0, unit_tmp = unit;
    int choice;
    getOption("1. ประเภทที่ 1.1.1 ใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n2. ประเภทที่ 1.1.2 ใช้พลังงานไฟฟ้าเกิน 150 หน่วยต่อเดือน\nEnter choice: ", &choice, 2);
    switch(choice){
        case 1:
        if(unit > 400) cost += (unit - 400) * 4.4217, unit = 400;
        if(unit > 150) cost += (unit - 150) * 4.2218, unit = 150;
        if(unit > 100) cost += (unit - 100) * 3.7171, unit = 100;
        if(unit > 35) cost += (unit - 35) * 3.6237, unit = 35;
        if(unit > 25) cost += (unit - 25) * 3.2405, unit = 25;
        if(unit > 15) cost += (unit - 15) * 2.9882, unit = 15;
        cost += unit * 2.3488;
        cost += unit_tmp * Ft;
        cost += 8.19;
        vat(&cost);
        break;

    case 2:
        if(unit > 400) cost += (unit - 400) * 4.4217, unit = 400;
        if(unit > 150) cost += (unit - 150) * 4.2218, unit = 150;
        cost += unit * 3.2482;
        cost += unit_tmp * Ft; 
        cost += 24.62;
        vat(&cost);
        break;
    }
    return cost;
}
double residentialTOURate(){ //ประเภทที่ 1.2 บ้านอยู่อาศัย (อัตรา TOU)
    int choice, unit;
    float onPeak, offPeak, holiday, unit_price;
    double cost = 0;
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 2);
    
    switch(choice){
        case 1:
        onPeak = 5.1135;
        offPeak = 2.6037;
        holiday = 2.6037;
        unit_price = 3.9086;
        cost += 312.24;
        break;
        case 2:
        onPeak = 5.7982;
        offPeak = 2.6369;
        holiday = 2.6369;
        cost += 24.62;
        break;
    }
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &unit);
    cost += unit * onPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &unit);
    cost += unit * offPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &unit);
    cost += unit * holiday;
    vat(&cost);
    cost += Ft;
    
    return cost;
}