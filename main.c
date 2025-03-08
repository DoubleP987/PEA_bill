#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double Ft = 0.3672;

double menu();
double KVCharge(double kv, double kw);
void vat(double *cost, double sumFt); //vat 7% calculation
void getInput(char *msg, int *value);
void getdouble(char *msg, double *value);
void getOption(char *msg, int *choice, int option);
double residentialNormalRate(); //done
double residentialTOURate(); //done
double smallBusinessNormalRate(); //done
double smallBusinessTOURate(); //done
double mediumBusiness(); //done //option 6

double largeBusinessTODRate();

double nonProfitOrganization(); //done
double nonProfitOrganizationTOURate(); //coding
double agricultureWaterPumping(); //done
double agricultureWaterPumpingTOURate(); //done
double temporaryElectricity(); //done

int main(){
    int unit;
    double cost;

    cost = menu(); //test
    printf("cost price = %f\n", cost);
    double display_cost = round(cost * 100.0) / 100.0;
    printf("last price = %.2f\n", display_cost);

    return 0;
}
void getInput(char *msg, int *value){
    while(printf("%s", msg), scanf("%d", value) != 1){
        printf("ข้อมูลไม่ถูกต้อง\n");
        while(getchar() != '\n');
    }
}
void getdouble(char *msg, double *value){
    while(printf("%s", msg), scanf("%f", value) != 1){
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
        case 3:
        return smallBusinessNormalRate();
            break;
        case 4:
        return smallBusinessTOURate();
            break;
        case 5:
        return mediumBusiness();
            break;
        case 6:
        // return mediumBusinessTOURate();
            break;
        case 7:
        return largeBusinessTODRate();
            break;
        case 8:
        //return largeBusinessTOURate();
            break;
        case 9:
        //return specialBusinessNormalRate();
            break;
        case 10:
        //return specialBusinessTOURate();
            break;
        case 11:
        return nonProfitOrganization();
            break;
        case 12:
        return nonProfitOrganizationTOURate();
            break;
        case 13:
        return agricultureWaterPumping();
            break;
        case 14:
        return agricultureWaterPumpingTOURate();
            break;
        case 15:
        return temporaryElectricity();
            break;
    }
}
void vat(double *cost, double sumFt){
    *cost += ((*cost + sumFt) * 0.07);
}
double KVCharge(double kv, double kw){
    return (56.07 * round(fmax(0, (kv - (kw * 0.6197)))));
}
double residentialNormalRate(){ //ประเภทที่ 1.1 บ้านอยู่อาศัย (อัตราปกติ)
    double service_charge, sumFt, cost = 0;
    int choice, unit;
    getOption("1. ประเภทที่ 1.1.1 ใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n2. ประเภทที่ 1.1.2 ใช้พลังงานไฟฟ้าเกิน 150 หน่วยต่อเดือน\nEnter choice: ", &choice, 2);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    int unit_tmp = unit;
    switch(choice){
        case 1: 
        if(unit > 400) cost += (unit - 400) * 4.4217, unit = 400;
        if(unit > 150) cost += (unit - 150) * 4.2218, unit = 150;
        if(unit > 100) cost += (unit - 100) * 3.7171, unit = 100;
        if(unit > 35) cost += (unit - 35) * 3.6237, unit = 35;
        if(unit > 25) cost += (unit - 25) * 3.2405, unit = 25;
        if(unit > 15) cost += (unit - 15) * 2.9882, unit = 15;
        cost += unit * 2.3488;
        service_charge = 8.19;
        break;

        case 2:
        if(unit > 400) cost += (unit - 400) * 4.4217, unit = 400;
        if(unit > 150) cost += (unit - 150) * 4.2218, unit = 150;
        cost += unit * 3.2484;
        service_charge = 24.62;
        break;
    }
    cost += service_charge;
    sumFt = unit_tmp * Ft;
    vat(&cost, sumFt);
    cost += unit_tmp * Ft;

    return 0;
}
double residentialTOURate(){ //ประเภทที่ 1.2 บ้านอยู่อาศัย (อัตรา TOU)
    int choice, unit1, unit2, unit3;
    double onPeak, offPeak, holiday;
    double cost = 0;
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 2);
    
    switch(choice){
        case 1:
        onPeak = 5.1135;
        offPeak = 2.6037;
        holiday = 2.6037;
        cost += 312.24;
        break;
        case 2:
        onPeak = 5.7982;
        offPeak = 2.6369;
        holiday = 2.6369;
        cost += 24.62;
        break;
    }
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &unit1);
    cost += unit1 * onPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &unit2);
    cost += unit2 * offPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &unit3);
    cost += unit3 * holiday;
    int sumUnit = unit1 + unit2 + unit3;
    double sumFt = sumUnit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
double smallBusinessNormalRate(){
    int choice, unit;
    double cost = 0;
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 2);
    switch(choice){
        case 1:
        cost += 312.24;
        break;
        case 2:
        cost += 46.16;
        break;
    }
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    int unit_tmp = unit;
    if(choice == 1){
        cost += unit * 3.9086;
    }else if(choice == 2){
        if(unit > 400) cost += (unit - 400) * 4.4217, unit = 400;
        if(unit > 150) cost += (unit - 150) * 4.2218, unit = 150;
        cost += unit * 3.2484;
    }
    double sumFt = Ft * unit_tmp;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
double smallBusinessTOURate(){ //done
    int choice, unit1, unit2, unit3;
    double onPeak, offPeak, holiday, cost = 0;
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 2);
    
    switch(choice){
        case 1:
        onPeak = 5.1135;
        offPeak = 2.6037;
        holiday = 2.6037;
        cost += 312.24;
        break;
        case 2:
        onPeak = 5.7982;
        offPeak = 2.6369;
        holiday = 2.6369;
        cost += 46.16;
        break;
    }
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &unit1);
    cost += unit1 * onPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &unit2);
    cost += unit2 * offPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &unit3);
    cost += unit3 * holiday;
    int sumUnit = unit1 + unit2 + unit3;
    double sumFt = sumUnit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
double mediumBusiness(){
    int choice, kw, kv, unit;
    double kw_price, unit_price, service_charge = 312.24, cost = 0;
    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    
    switch(choice){
        case 1:
        kw_price = 175.70;
        unit_price = 3.1097;
        break;
        case 2:
        kw_price = 196.26;
        unit_price = 3.1471;
        break;
        case 3:
        kw_price = 221.50;
        unit_price = 3.1751;
        break;
    }
    getInput("ความต้องการพลังงานไฟฟ้าสูงสุด (กิโลวัตต์): ", &kw);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &kv);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    cost += kw_price * kw;
    cost += unit_price * unit;
    cost += service_charge;
    double kvtmp = KVCharge(kv, kw);
    cost += kvtmp;

    double sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;


    return cost;
}
// double mediumBusinessTOURate(){
//     int choice, kw, kv, unit;
//     double kw_price, unit_price, service_charge = 312.24, cost = 0;
//     printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
//     getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    
//     switch(choice){
//         case 1:
//         kw_price = 175.70;
//         unit_price = 3.1097;
//         break;
//         case 2:
//         kw_price = 196.26;
//         unit_price = 3.1471;
//         break;
//         case 3:
//         kw_price = 221.50;
//         unit_price = 3.1751;
//         break;
//     }
//     getInput("ความต้องการพลังงานไฟฟ้าสูงสุด (กิโลวัตต์): ", &kw);
//     cost += kw_price * kw;
//     getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &kv);
//     cost += unit_price * kv;
//     getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
//     cost += service_charge;
//     cost += KVCharge(kv, kw);
//     double sumFt = unit * Ft;
//     vat(&cost, sumFt);
//     cost += sumFt;


//     return cost;
// }
double largeBusinessTODRate(){
    int choice, NeedOnPeak, NeedOffPeak, NeedPartialPeak, NeedReactive, Unit;
    double cost = 0, NeedRateOn, NeedRateOff, NeedRatePartial, RateOn, RateOff, service_charge = 312.24;
    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Partial Peak (กิโลวัตต์): ", &NeedPartialPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedPartialPeak);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &Unit);

    switch(choice){
        case 1:
        NeedRateOn = 224.3;
        NeedRatePartial = 29.91;
        RateOn = 3.1097;
        break;
        case 2:
        NeedRateOn = 285.05;
        NeedRatePartial = 58.88;
        RateOn = 3.1471;
        break;
        case 3:
        NeedRateOn = 332.71;
        NeedRatePartial = 68.22;
        RateOn = 3.1751;
        break;
    }
    // double NeedPower = round(NeedOnPeak * NeedRateOn) + round((NeedPartialPeak - NeedOnPeak) * NeedRatePartial);
    // double Power = round(Unit * RateOn);
    // double Base = NeedPower + 
    // double Summary = Base + FT + VAT;
    // return Summary;
    cost += (NeedOnPeak * NeedRateOn) + ((NeedPartialPeak * NeedOnPeak) * NeedPartialPeak);
}
double nonProfitOrganization(){
    int choice, unit;
    double cost = 0, service_charge = 312.24;
    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    switch(choice){
        case 1:
        cost += unit * 3.4149;
        cost += service_charge;
        break;
        case 2:
        cost += unit * 3.5849;
        cost += service_charge;
        break;
        case 3:
        double tmp = unit;
        if(tmp > 10) cost += (tmp - 10) * 3.8919, tmp = 10;
        cost += tmp * 2.8013;
        cost += 20;
        break;
    }
    double sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
double nonProfitOrganizationTOURate(){
    int NeedOnPeak, NeedOffPeak, NeedHoliday, NeedReactive, Peak, OffPeak, Holiday, choice;
    double sumFt, cost = 0, NeedRateOn, RateOn, RateOff, service_charge = 204.07;
    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (กิโลวัตต์): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &Peak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &OffPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &Holiday);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);


    switch(choice){
        case 1:
        NeedRateOn = 74.14;
        RateOn = 4.1025;
        RateOff = 2.5849;
        break;
        case 2:
        NeedRateOn = 132.93;
        RateOn = 4.1839;
        RateOff = 2.6037;
        break;
        case 3:
        NeedRateOn = 210.00;
        RateOn = 4.3297;
        RateOff = 2.6369;
        break;
    }
    // cost += NeedOnPeak * NeedRateOn;
    // cost += Peak * RateOn;
    // cost += (OffPeak + Holiday) * RateOff;
    // cost += service_charge;
    // cost += KVCharge(NeedReactive, fmax(NeedOnPeak, NeedOffPeak));
    // sumFt = (Peak + OffPeak + Holiday) * Ft;
    // vat(&cost, sumFt);
    // cost += sumFt;
    cost += (NeedOnPeak * NeedRateOn);
    cost += (Peak * RateOn) + (OffPeak * RateOff) + (Holiday * RateOff);
    sumFt = (Peak + OffPeak + Holiday) * Ft;
    cost += service_charge;
    if(NeedOnPeak < NeedOffPeak){
        NeedOnPeak = NeedOffPeak;
    }
    double kvtmp = (56.07 * fmax(0, (NeedReactive - (NeedOnPeak * 0.6197))));
    cost += kvtmp;
    vat(&cost, sumFt);
    cost += sumFt;
    return cost;
}
double agricultureWaterPumping(){
    int unit;
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    double cost, tmp = unit;
    if(tmp > 100) cost += (tmp - 100) *  3.2405, tmp = 100;
    cost += tmp * 2.0889;
    cost += 115.16;
    double sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
double agricultureWaterPumpingTOURate(){
    int choice, NeedOnPeak, NeedOffPeak, NeedHoliday, Peak, OffPeak, Holiday;
    double sumFt, cost = 0, NeedRateOn, RateOn, RateOff, service_charge = 204.07;
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 2);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (กิโลวัตต์): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &Peak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &OffPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &Holiday);

    switch(choice){
        case 1:
        NeedRateOn = 132.93;
        RateOn = 4.1839;
        RateOff = 2.6037;
        break;
        case 2:
        NeedRateOn = 210;
        RateOn =  4.3297;
        RateOff = 2.6369;
        break;
    }
    cost += (NeedOnPeak * NeedRateOn);
    cost += (Peak * RateOn) + (OffPeak * RateOff) + (Holiday * RateOff);
    sumFt = (Peak + OffPeak + Holiday) * Ft;
    cost += service_charge;
    vat(&cost, sumFt);
    cost += sumFt;
    
    return cost;
}
double temporaryElectricity(){
    int unit;
    double cost = 0;
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    cost += unit * 6.8025;
    double sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}