#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float Ft = 0.3672;

float menu();
float KVCharge(float kv, float kw);
void vat(float *cost, float sumFt); //vat 7% calculation
void getInput(char *msg, int *value);
void getFloat(char *msg, float *value);
void getOption(char *msg, int *choice, int option);
float residentialNormalRate(); //done
float residentialTOURate(); //done
float smallBusinessNormalRate(); //done
float smallBusinessTOURate(); //done
float mediumBusiness(); //done

float nonProfitOrganization(); //done
float nonProfitOrganizationTOURate();
float agricultureWaterPumping(); //done
float agricultureWaterPumpingTOURate(); //need to fix the demicals summary price. and ensure the priority is correct.
float temporaryElectricity(); //done

int main(){
    int unit;
    float cost;

    cost = menu(); //test
    printf("cost price = %f\n", cost);
    float display_cost = round(cost * 100.0) / 100.0;
    printf("last price = %.2f\n", display_cost);

    return 0;
}
void getInput(char *msg, int *value){
    while(printf("%s", msg), scanf("%d", value) != 1){
        printf("ข้อมูลไม่ถูกต้อง\n");
        while(getchar() != '\n');
    }
}
void getFloat(char *msg, float *value){
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
float menu(){
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
        //return mediumBusinessTOURate();
            break;
        case 7:
        //return largeBusinessTODRate();
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
void vat(float *cost, float sumFt){
    *cost += ((*cost + sumFt) * 0.07);
}
float KVCharge(float kv, float kw){
    return (56.07 * round(fmax(0, (kv - (kw * 0.6197)))));
}
float residentialNormalRate(){ //ประเภทที่ 1.1 บ้านอยู่อาศัย (อัตราปกติ)
    float sumFt, cost = 0;
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
        cost += 8.19;
        break;

        case 2:
        if(unit > 400) cost += (unit - 400) * 4.4217, unit = 400;
        if(unit > 150) cost += (unit - 150) * 4.2218, unit = 150;
        cost += unit * 3.2484;
        cost += 24.62;
        break;
    }
    sumFt = unit_tmp * Ft;
    vat(&cost, sumFt);
    cost += unit_tmp * Ft;

    return cost;
}
float residentialTOURate(){ //ประเภทที่ 1.2 บ้านอยู่อาศัย (อัตรา TOU)
    int choice, unit1, unit2, unit3;
    float onPeak, offPeak, holiday;
    float cost = 0;
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
    float sumFt = sumUnit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
float smallBusinessNormalRate(){
    int choice, unit;
    float cost = 0;
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
    float sumFt = Ft * unit_tmp;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
float smallBusinessTOURate(){ //done
    int choice, unit1, unit2, unit3;
    float onPeak, offPeak, holiday, cost = 0;
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
    float sumFt = sumUnit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
float mediumBusiness(){
    int choice, kw, kv, unit;
    float kw_price, unit_price, service_charge = 312.24, cost = 0;
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
    float kvtmp = KVCharge(kv, kw);
    cost += kvtmp;

    float sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;


    return cost;
}
float mediumBusinessTOURate(){
    int choice, kw, kv, unit;
    float kw_price, unit_price, service_charge = 312.24, cost = 0;
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
    cost += kw_price * kw;
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &kv);
    cost += unit_price * kv;
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    cost += service_charge;
    cost += KVCharge(kv, kw);
    float sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;


    return cost;
}
float nonProfitOrganization(){
    int choice, unit;
    float cost = 0, service_charge = 312.24;
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
        float tmp = unit;
        if(tmp > 10) cost += (tmp - 10) * 3.8919, tmp = 10;
        cost += tmp * 2.8013;
        cost += 20;
        break;
    }
    float sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
float nonProfitOrganizationTOURate(){ //hardy
    int choice, NeedOnPeak, NeedOffPeak, NeedHoliday, Peak, OffPeak, Holiday;
    float NeedRateOn, RateOn, RateOff, service_charge = 204.07;
    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (กิโลวัตต์): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &Peak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &OffPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &Holiday);

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
    float NeedPower = round(NeedOnPeak * NeedRateOn);
    float Power = round((Peak * RateOn) + ((OffPeak + Holiday) * RateOff));
    float Base = round(NeedPower + Power + service_charge);
    float FT = round((Peak + OffPeak + Holiday) * Ft);
    float VAT = round((Base + FT) * 0.07);
    float Summary = Base + FT + VAT;
    return Summary;
}
float agricultureWaterPumping(){
    int unit;
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    float cost, tmp = unit;
    if(tmp > 100) cost += (tmp - 100) *  3.2405, tmp = 100;
    cost += tmp * 2.0889;
    cost += 115.16;
    float sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}
float agricultureWaterPumpingTOURate(){
    int choice, NeedOnPeak, NeedOffPeak, NeedHoliday, Peak, OffPeak, Holiday;
    float NeedRateOn, RateOn, RateOff, service_charge = 204.07;
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
        RateOn = 4.1893;
        RateOff = 2.6037;
        break;
        case 2:
        NeedRateOn = 210;
        RateOn =  4.3297;
        RateOff = 2.6369;
        break;
    }
    float NeedPower = round(NeedOnPeak * NeedRateOn);
    float Power = round((Peak * RateOn) + ((OffPeak + Holiday) * RateOff));
    float Base = round(NeedPower + Power + service_charge);
    float FT = round((Peak + OffPeak + Holiday) * Ft);
    float VAT = round((Base + FT) * 0.07);
    float Summary = Base + FT + VAT;
    return Summary;
}
float temporaryElectricity(){
    int unit;
    float cost = 0;
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    cost += unit * 6.8025;
    float sumFt = unit * Ft;
    vat(&cost, sumFt);
    cost += sumFt;

    return cost;
}