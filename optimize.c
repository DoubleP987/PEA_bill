#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double Ft = 0.3672;
const double VAT = 0.07;

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
void vat(double *cost, double sumFt){
    *cost += ((*cost + sumFt) * 0.07);
}
double KVCharge(double kv, double kw){
    return (56.07 * round(fmax(0, (kv - (kw * 0.6197)))));
}
double residentialNormalRate(){ //ประเภทที่ 1.1 บ้านอยู่อาศัย (อัตราปกติ)
    double base, base_tariff, vat_charge, ft_charge, service_charge, cost = 0;
    int choice, unit, unit_tmp;
    getOption("1. ประเภทที่ 1.1.1 ใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n2. ประเภทที่ 1.1.2 ใช้พลังงานไฟฟ้าเกิน 150 หน่วยต่อเดือน\nEnter choice: ", &choice, 2);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    unit_tmp = unit;
    switch(choice){
        case 1: 
        if(unit_tmp > 400) cost += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
        if(unit_tmp > 150) cost += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
        if(unit_tmp > 100) cost += (unit_tmp - 100) * 3.7171, unit_tmp = 100;
        if(unit_tmp > 35) cost += (unit_tmp - 35) * 3.6237, unit_tmp = 35;
        if(unit_tmp > 25) cost += (unit_tmp - 25) * 3.2405, unit_tmp = 25;
        if(unit_tmp > 15) cost += (unit_tmp - 15) * 2.9882, unit_tmp = 15;
        cost += unit_tmp * 2.3488;
        service_charge = 8.19; //service charge
        break;

        case 2:
        if(unit_tmp > 400) cost += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
        if(unit_tmp > 150) cost += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
        cost += unit_tmp * 3.2484;
        service_charge = 24.62; //service charge
        break;
    }
    base_tariff = cost + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;

    return cost;
}
double menu(){
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
    getOption("เลือกประเภทไฟฟ้า(1 - 15): ", &choice, 15);
    switch(choice){
        case 1:
        return residentialNormalRate();
            break;
        // case 2:
        // return residentialTOURate();
            // break;
        // case 3:
        // return smallBusinessNormalRate();
            // break;
        // case 4:
        // return smallBusinessTOURate();
            // break;
        // case 5:
        // return mediumBusiness();
            // break;
        // case 6:
        // return mediumBusinessTOURate();
            // break;
        // case 7:
        // return largeBusinessTODRate();
            // break;
        // case 8:
        // return largeBusinessTOURate();
            // break;
        // case 9:
        // return specialBusinessNormalRate();
            // break;
        // case 10:
        // return specialBusinessTOURate();
            // break;
        // case 11:
        // return nonProfitOrganization();
            // break;
        // case 12:
        // return nonProfitOrganizationTOURate();
            // break;
        // case 13:
        // return agricultureWaterPumping();
            // break;
        // case 14:
        // return agricultureWaterPumpingTOURate();
            // break;
        // case 15:
        // return temporaryElectricity();
            // break;
    }
}
int main(){
    int unit;
    double cost;

    cost = menu();
    printf("cost price = %f\n", cost);
    double display_cost = floor(cost * 100.0) / 100.0;
    printf("last price = %.2f\n", display_cost);

    return 0;
}