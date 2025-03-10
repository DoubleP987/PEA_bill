#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double Ft = 0.3672;
const double VAT = 0.07;

void getInput(char *msg, double *value){
    while(1){
        char ch;
        printf("%s", msg);
        if(scanf("%lf", value) == 1){
            if(scanf("%c", &ch) == 1 && ch != '\n'){
                printf("ข้อมูลไม่ถูกต้อง\n");
                while(getchar() != '\n');
            }else{
                break;
            }
        }else{
            printf("ข้อมูลไม่ถูกต้อง\n");
            while(getchar() != '\n');
        }
    }
}
void getOption(char *msg, int *choice, int option){
    while(printf("%s", msg), scanf("%d", choice) != 1 || *choice < 1 || *choice > option){
        printf("ตัวเลือกไม่ถูกต้อง\n");
        while(getchar() != '\n');
    }
}
double KVCharge(double kv, double kw){
    return round(fmax(0, (kv - (kw * 0.6197))));
}
void residentialNormalRate(){ //ประเภทที่ 1.1 บ้านอยู่อาศัย (อัตราปกติ)
    double unit, unit_tmp, base_tariff, vat_charge, ft_charge, service_charge, cost, base = 0;
    int choice;
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
void residentialTOURate(){ //ประเภทที่ 1.2 บ้านอยู่อาศัย (อัตรา TOU)
    double NeedOnPeak, NeedOffPeak, NeedHoliday, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
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
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &NeedOnPeak);
    base += NeedOnPeak * onPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &NeedOffPeak);
    base += NeedOffPeak * offPeak;
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &NeedHoliday);
    base += NeedHoliday * holiday;
    base_tariff = base + service_charge;
    ft_charge = (NeedOnPeak + NeedOffPeak + NeedHoliday) * Ft;
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
void smallBusinessNormalRate(){ //ประเภทที่ 2.1 กิจการขนาดเล็ก (อัตราปกติ)
    int choice;
    double unit, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 2);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    switch(choice){
        case 1:
        service_charge = 312.24;
        base += unit * 3.9086;
        break;
        case 2:
        service_charge = 46.16;
        double unit_tmp = unit;
        if(unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
        if(unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
        base += unit_tmp * 3.2484;
        break;
    }
    ft_charge = unit * Ft;
    base_tariff = base + service_charge;
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
void smallBusinessTOURate(){ //ประเภทที่ 2.2 กิจการขนาดเล็ก (อัตรา TOU)
    double NeedOnPeak, NeedOffPeak, NeedHoliday, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;

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
        service_charge = 46.16;
        break;
    }
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &NeedOnPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &NeedOffPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &NeedHoliday);
    base += NeedOnPeak * onPeak;
    base += NeedOffPeak * offPeak;
    base += NeedHoliday * holiday;
    ft_charge = (NeedOnPeak + NeedOffPeak + NeedHoliday) * Ft;
    base_tariff = base + service_charge;
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
void mediumBusiness(){ //ประเภทที่ 3.1 กิจการขนาดกลาง
    double rate, power, Kilovar, kv_charge, unit, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;

    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    
    switch(choice){
        case 1:
        HighestRate = 175.70;
        rate = 3.1097;
        break;
        case 2:
        HighestRate = 196.26;
        rate = 3.1471;
        break;
        case 3:
        HighestRate = 221.50;
        rate = 3.1751;
        break;
    }
    getInput("ความต้องการพลังงานไฟฟ้าสูงสุด (กิโลวัตต์): ", &NeedOnHighestRate);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    service_charge = 312.24;
    power = NeedOnHighestRate * HighestRate;
    unit_price = unit * rate;
    Kilovar = KVCharge(NeedReactive, NeedOnHighestRate);
    kv_charge = Kilovar * 56.07;
    base = power + unit_price + service_charge + kv_charge;
    base_tariff = unit_price + service_charge + power + kv_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge; 

    printf("3.1 อัตราปกติ (Normal Rate)\n\n");
    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n");
    printf("\t\tค่าความต้องการพลังไฟฟ้า %21.2f บาท\n", power);
    printf("\t\tค่าพลังงานไฟฟ้า %28.2f บาท\n", unit_price);
    printf("\t\tค่าเพาเวอร์แฟคเตอร์\n");
    printf("\t\tจำนวนกิโลวาร์ที่คิดเงิน %24.0f กิโลวาร์\n", Kilovar);
    printf("\t\tจำนวนเงิน %33.2f บาท\n", kv_charge);
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base_tariff);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);
}
void mediumBusinessTOURate(){ //ประเภทที่ 3.2 กิจการขนาดกลาง (อัตรา TOU)
    double NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, power, Kilovar, kv_charge, unit, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;

    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    
    switch(choice){
        case 1:
        HighestRate = 74.14;
        rateOn = 4.1025;
        rateOff = 2.5849;
        break;
        case 2:
        HighestRate = 132.93;
        rateOn = 4.1839;
        rateOff = 2.6037;
        break;
        case 3:
        HighestRate = 210.00;
        rateOn = 4.3297;
        rateOff = 2.6369;
        break;
    }
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวาร์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (หน่วย): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &onPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &offPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &holiday);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
    service_charge = 312.24;
    power = NeedOnPeak * HighestRate;
    unit_price = (onPeak * rateOn) + ((offPeak + holiday) * rateOff); //
    Kilovar = KVCharge(NeedReactive, (fmax(NeedOnPeak, fmax(NeedOffPeak, NeedHoliday))));
    kv_charge = Kilovar * 56.07;
    base = power + unit_price + service_charge + kv_charge;
    base_tariff = unit_price + service_charge + power + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge; 

    // printf("3.1 อัตราปกติ (Normal Rate)\n\n");
    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n");
    // printf("\t\tค่าความต้องการพลังไฟฟ้า %21.2f บาท\n", power);
    // printf("\t\tค่าพลังงานไฟฟ้า %28.2f บาท\n", unit_price);
    // printf("\t\tค่าเพาเวอร์แฟคเตอร์\n");
    // printf("\t\tจำนวนกิโลวาร์ที่คิดเงิน %24.0f กิโลวาร์\n", Kilovar);
    // printf("\t\tจำนวนเงิน %33.2f บาท\n", kv_charge);
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base_tariff);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);
}
void largeBusinessTODRate(){ //ประเภทที่ 4.1 กิจการขนาดใหญ่ (อัตรา TOD)
    int choice;
    double Kilovar, power, unit_price, kv_charge, base_tariff, vat_charge, ft_charge, NeedOnPeak, unit, NeedOffPeak, NeedPartialPeak, NeedReactive, base = 0, cost, NeedRateOn, NeedRateOff, NeedRatePartial, rateOn, rateOff, service_charge;
    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Partial Peak (กิโลวัตต์): ", &NeedPartialPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);

    switch(choice){
        case 1:
        NeedRateOn = 224.3;
        NeedRatePartial = 29.91;
        rateOn = 3.1097;
        break;
        case 2:
        NeedRateOn = 285.05;
        NeedRatePartial = 58.88;
        rateOn = 3.1471;
        break;
        case 3:
        NeedRateOn = 332.71;
        NeedRatePartial = 68.22;
        rateOn = 3.1751;
        break;
    }
    service_charge = 312.24;
    power = (NeedOnPeak * NeedRateOn) + ((NeedPartialPeak - NeedOnPeak) * NeedRatePartial);
    unit_price = unit * rateOn;
    Kilovar = KVCharge(NeedReactive, fmax(NeedOnPeak, fmax(NeedPartialPeak, NeedOffPeak)));
    // Kilovar = round(fmax(0, (NeedReactive - (fmax(NeedOnPeak, fmax(NeedPartialPeak, NeedOffPeak) * 0.6197)))));
    printf("kv = %f\n", Kilovar);
    kv_charge = Kilovar * 56.07;
    printf("kv charge = %f\n", kv_charge);
    base_tariff = power + unit_price + kv_charge + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    // double NeedPower = round(NeedOnPeak * NeedRateOn) + round((NeedPartialPeak - NeedOnPeak) * NeedRatePartial);
    // double Power = round(Unit * RateOn);
    // double Base = NeedPower + 
    // double Summary = Base + FT + VAT;
    // return Summary;
    // cost += (NeedOnPeak * NeedRateOn) + ((NeedPartialPeak * NeedOnPeak) * NeedPartialPeak);

    // printf("3.1 อัตราปกติ (Normal Rate)\n\n");
    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n");
    // printf("\t\tค่าความต้องการพลังไฟฟ้า %21.2f บาท\n", power);
    // printf("\t\tค่าพลังงานไฟฟ้า %28.2f บาท\n", unit_price);
    // printf("\t\tค่าเพาเวอร์แฟคเตอร์\n");
    // printf("\t\tจำนวนกิโลวาร์ที่คิดเงิน %24.0f กิโลวาร์\n", Kilovar);
    // printf("\t\tจำนวนเงิน %33.2f บาท\n", kv_charge);
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base_tariff);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);
}
void nonProfitOrganization(){ //ประเภทที่ 6.1 องค์การที่ไม่แสวงหากำไร
    double NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, power, Kilovar, kv_charge, unit, unit_tmp, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    printf("(1) แรงดัน 69 กินโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟฟ้า: ", &choice, 3);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    switch(choice){
        case 1:
        base += unit * 3.4149;
        service_charge = 312.24;
        break;
        case 2:
        base += unit * 3.5849;
        service_charge = 312.24;
        break;
        case 3:
        unit_tmp = unit;
        if(unit_tmp > 10) base += (unit_tmp - 10) * 3.8919, unit_tmp = 10;
        base += unit_tmp * 2.8013;
        service_charge = 20;
        break;
    }
    base_tariff = base + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;

    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n");
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base_tariff);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);

}
void agricultureWaterPumping(){ // ประเภทที่ 7.1 สูบน้ำเพื่อการเกษตร
    double ft_charge, service_charge, vat_charge, cost, base = 0, unit, unit_tmp, base_tariff;
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    service_charge = 115.16;
    unit_tmp = unit;
    if(unit_tmp > 100) base += (unit_tmp - 100) *  3.2405, unit_tmp = 100;
    base += unit_tmp * 2.0889;
    ft_charge = unit * Ft;
    base_tariff = base + service_charge;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = vat_charge + ft_charge + base_tariff;
    printf("\t7.1 อัตราปกติ (Normal Rate)\n\n");
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);
}
void temporaryElectricity(){ //ประเภทที่ 8 ไฟฟ้าชั่วคราว
    double service_charge, ft_charge, vat_charge, base, base_tariff, unit, cost;
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    service_charge = 0;
    base = unit * 6.8025;
    ft_charge = unit * Ft;
    vat_charge = (base + ft_charge) * VAT;
    cost = base + ft_charge + vat_charge;

    printf("\t7.1 อัตราปกติ (Normal Rate)\n\n");
    printf("\t\tค่าบริการ %33.2f บาท\n", service_charge);
    printf("\t\tรวมค่าไฟฟ้าฐาน %28.2f บาท\n", base);
    printf("\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n");
    printf("\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %17.2f บาท\n", ft_charge);
    printf("\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n");
    printf("\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %13.2f บาท\n", vat_charge);
    printf("\n\tรวมเงินค่าไฟฟ้า %36.2f บาท\n", cost);
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
    getOption("เลือกประเภทไฟฟ้า(1 - 15): ", &choice, 15);
    switch(choice){
        case 1:
        residentialNormalRate();
            break;
        case 2:
        residentialTOURate();
            break;
        case 3:
        smallBusinessNormalRate();
            break;
        case 4:
        smallBusinessTOURate();
            break;
        case 5:
        mediumBusiness();
            break;
        case 6:
        mediumBusinessTOURate();
            break;
        case 7:
        largeBusinessTODRate();
            break;
        // case 8:
        // largeBusinessTOURate();
            // break;
        // case 9:
        // specialBusinessNormalRate();
            // break;
        // case 10:
        // specialBusinessTOURate();
            // break;
        case 11:
        nonProfitOrganization();
            break;
        // case 12:
        // nonProfitOrganizationTOURate();
            // break;
        case 13:
        agricultureWaterPumping();
            break;
        // case 14:
        // agricultureWaterPumpingTOURate();
            // break;
        case 15:
        temporaryElectricity();
            break;
    }
}
int main(){
    int unit;
    double cost;

    menu();
    // printf("cost price = %f\n", cost);
    // double display_cost = floor(cost * 100.0) / 100.0;
    // printf("last price = %.2f\n", display_cost);

    return 0;
}
