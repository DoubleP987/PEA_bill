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
    double base_tariff, vat_charge, ft_charge, service_charge, cost, base = 0;
    int choice, unit, unit_tmp;
    getOption("1. ประเภทที่ 1.1.1 ใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n2. ประเภทที่ 1.1.2 ใช้พลังงานไฟฟ้าเกิน 150 หน่วยต่อเดือน\nEnter choice: ", &choice, 2);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    unit_tmp = unit;
    switch(choice){
        case 1: 
        if(unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
        if(unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
        if(unit_tmp > 100) base += (unit_tmp - 100) * 3.7171, unit_tmp = 100;
        if(unit_tmp > 35) base += (unit_tmp - 35) * 3.6237, unit_tmp = 35;
        if(unit_tmp > 25) base += (unit_tmp - 25) * 3.2405, unit_tmp = 25;
        if(unit_tmp > 15) base += (unit_tmp - 15) * 2.9882, unit_tmp = 15;
        base += unit_tmp * 2.3488;
        service_charge = 8.19;
        break;

        case 2:
        if(unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
        if(unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
        base += unit_tmp * 3.2484;
        service_charge = 24.62;
        break;
    }
    base_tariff = base + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;

    printf("อัตราปกติ ปริมาณการใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n\n");
    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n");
    printf("\t\tค่าพลังงานไฟฟ้า %28.2f บาท\n", base);
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base_tariff);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);
}
double residentialTOURate(){ //ประเภทที่ 1.2 บ้านอยู่อาศัย (อัตรา TOU)
    int choice, unit1, unit2, unit3;
    double cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 2);
    
    switch(choice){
        case 1:
        onPeak = 5.1135;
        offPeak = 2.6037;
        holiday = 2.6037;
        service_charge = 312.24;
        break;
        case 2:
        onPeak = 5.7982;
        offPeak = 2.6369;
        holiday = 2.6369;
        service_charge = 24.62;
        break;
    }
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &unit1);
    base += unit1 * onPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &unit2);
    base += unit2 * offPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &unit3);
    base += unit3 * holiday;
    int sumUnit = unit1 + unit2 + unit3;
    base_tariff = base + service_charge;
    ft_charge = sumUnit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;

    printf("อัตราปกติ ปริมาณการใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n\n");
    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n");
    printf("\t\tค่าพลังงานไฟฟ้า %28.2f บาท\n", base);
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base_tariff);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);
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
        case 2:
        return residentialTOURate();
            break;
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