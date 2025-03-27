#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>

const double VAT = 0.07; // อัตราภาษีมูลค่าเพิ่ม 7% ใช้ทุกที่ที่ต้องคำนวณ VAT

// ฟังก์ชันรับตัวเลขจากผู้ใช้ แล้วเช็กว่าถูกต้องไหม
void getInput(char *msg, double *value){
    char ch;
    while(1){ // วนไปเรื่อย ๆ จนกว่าจะได้ข้อมูลถูกต้อง
        printf("%s", msg); // แสดงข้อความให้ผู้ใช้รู้ว่าต้องกรอกอะไร
        if(scanf("%lf", value) == 1 && *value >= 0){ // ถ้ากรอกเป็นตัวเลขจริง ๆ และไม่ติดลบ
            if(scanf("%c", &ch) == 1 && ch != '\n'){ // เช็กว่ามีตัวอักษรแปลกปลอมตามหลังไหม (เช่น "12a")
                printf("ข้อมูลไม่ถูกต้อง\n"); // ถ้ามี บอกว่าไม่ถูก
                while(getchar() != '\n'); // ล้างข้อมูลเก่าที่ค้างใน buffer
            }else{
                break; // ถ้าถูกต้อง ออกลูป
            }
        }else{
            printf("ข้อมูลไม่ถูกต้อง\n"); // ถ้ากรอกไม่ใช่ตัวเลขหรือติดลบ บอกว่าไม่ถูก
            while(getchar() != '\n'); // ล้าง buffer เพื่อรับใหม่
        }
    }
}
// ฟังก์ชันรับตัวเลือก (เช่น 1-15) แล้วเช็กว่าอยู่ในช่วงที่กำหนดไหม
void getOption(char *msg, int *parameter, int option){
    char ch;
    while(1){ // วนไปจนกว่าจะได้ตัวเลือกที่ถูกต้อง
        printf("%s", msg); // แสดงข้อความให้ผู้ใช้รู้ว่าต้องเลือกอะไร
        if(scanf("%d", parameter) == 1 && *parameter >= 1 && *parameter <= option){ // ถ้ากรอกเลขและอยู่ในช่วง (เช่น 1-15)
            if(scanf("%c", &ch) == 1 && ch != '\n'){ // เช็กว่ามีตัวอักษรแปลกปลอมตามหลังไหม
                printf("ข้อมูลไม่ถูกต้อง\n");
                while(getchar() != '\n'); // ล้าง buffer
            }else{
                break; // ถ้าถูกต้อง ออกลูป
            }
        }else{
            printf("ข้อมูลไม่ถูกต้อง\n");
            while(getchar() != '\n'); // ล้าง buffer ถ้ากรอกผิด
        }
    }
}
double max(double a, double b){
    if (a > b) {
        return a;
    } else {
        return b; 
    }
}
// ฟังก์ชันคำนวณหน่วย Power Factor ถ้าเกินเกณฑ์ต้องจ่ายเพิ่ม
double KVCharge(double NeedReactive, double HighestRate){
    return round(max(0, (NeedReactive - (HighestRate * 0.6197)))); 
    // คำนวณค่าที่เกินจาก NeedReactive เมื่อเทียบกับ HighestRate * 0.6197
    // ปัดผลลัพธ์เป็นจำนวนเต็มที่ใกล้เคียงที่สุด
    // ส่งกลับ 0 ถ้าผลลัพธ์เป็นค่าลบ
}
// ฟังก์ชันเลือกค่า Ft ตามเดือนและปี
double getFt(int isResidential){ // isResidential = 1 ถ้าเป็นบ้าน, 0 ถ้าไม่ใช่
    int month, year;
    system("cls"); // ล้างหน้าจอก่อนแสดงเมนู
    printf("เลือกเดือน\n"
        "(1)  มกราคม\n"
        "(2)  กุมภาพันธ์\n"
        "(3)  มีนาคม\n"
        "(4)  เมษายน\n"
        "(5)  พฤษภาคม\n"
        "(6)  มิถุนายน\n"
        "(7)  กรกฎาคม\n"
        "(8)  สิงหาคม\n"
        "(9)  กันยายน\n"
        "(10) ตุลาคม\n"
        "(11) พฤศจิกายน\n"
        "(12) ธันวาคม\n"); 
    getOption("เดือน: ", &month, 12); // เลือกเดือน 1-12

    printf("\n(1) 2568\n(2) 2567\n(3) 2566\n");
    char ch;
    while(1){ // วนรับปีจนกว่าจะถูกต้อง
        printf("ปี: ");
        if(scanf("%d", &year) == 1 && ((year >= 1 && year <= 3) || (year >= 2566 && year <= 2568))){ // รองรับทั้ง 1-3 และ 2566-2568
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
    if(year == 1 || year == 2568){
        return 0.3672; // ปี 2568 ค่า Ft คงที่ทุกเดือน
    } else if(year == 2 || year == 2567){
        return 0.3972; // ปี 2567 ค่า Ft คงที่ทุกเดือน
    } else if(year == 3 || year == 2566){ // ปี 2566 แยกตามเดือน
        if (month >= 9 && month <= 12){
            return 0.2048; // เดือน 9-12
        }else if(month >= 5 && month <= 9){ 
            return 0.9119; // เดือน 5-9
        }else if(month >= 1 && month <= 4){ 
            if(isResidential){
                return 0.9343; // เดือน 1-4 ถ้าเป็นบ้าน
            }else{
                return 1.5492; // เดือน 1-4 ถ้าไม่ใช่บ้าน
            }
        }
    }
    return 0; // ไม่ควรถึงบรรทัดนี้ แต่ใส่ไว้เผื่อกรณีผิดพลาด
}
// ฟังก์ชันแสดงบิลค่าไฟแบบเป็นระเบียบ
void displayBill(double base, double service_charge, double base_tariff, double ft_charge, double vat_charge, double cost){
    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n"
    "\t\tค่าพลังงานไฟฟ้า %'28.2f บาท\n" // ค่าพลังงานจากหน่วยที่ใช้
    "\t\tค่าบริการ %'33.2f บาท\n" // ค่าบริการคงที่
    "\t\tรวมค่าไฟฟ้าฐาน %'28.2f บาท\n" // รวมค่าพลังงาน + ค่าบริการ
    "\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n"
    "\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %'17.2f บาท\n" // ค่า Ft คูณหน่วยที่ใช้
    "\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n"
    "\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %'13.2f บาท\n" // VAT 7% ของค่าไฟรวม
    "\n\tรวมเงินค่าไฟฟ้า %'36.2f บาท\n", // รวมทุกอย่าง
    base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟบ้านแบบปกติ (1.1)
void residentialNormalRate(){
    double Ft, unit, unit_tmp, base_tariff, vat_charge, ft_charge, service_charge, cost, base = 0;
    int choice;
    system("cls");
    printf("1. ประเภทที่ 1.1.1 ใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n2. ประเภทที่ 1.1.2 ใช้พลังงานไฟฟ้าเกิน 150 หน่วยต่อเดือน\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3); // เลือก 1 หรือ 2 (ใส่ 3 อาจผิด ควรเป็น 2)
    Ft = getFt(1); // ดึงค่า Ft สำหรับบ้าน
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit); // รับจำนวนหน่วยที่ใช้
    unit_tmp = unit; // เก็บหน่วยไว้ในตัวแปรชั่วคราวเพื่อคำนวณทีละขั้น
    switch(choice){
        case 1: // ใช้ไม่เกิน 150 หน่วย มีหลายขั้น
            if(unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400; // เกิน 400 คิดแพงสุด
            if(unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
            if(unit_tmp > 100) base += (unit_tmp - 100) * 3.7171, unit_tmp = 100;
            if(unit_tmp > 35) base += (unit_tmp - 35) * 3.6237, unit_tmp = 35;
            if(unit_tmp > 25) base += (unit_tmp - 25) * 3.2405, unit_tmp = 25;
            if(unit_tmp > 15) base += (unit_tmp - 15) * 2.9882, unit_tmp = 15;
            base += unit_tmp * 2.3488; // หน่วยแรก ๆ ถูกสุด
            service_charge = 8.19; // ค่าบริการถูก
            break;
        case 2: // ใช้เกิน 150 หน่วย ขั้นน้อยกว่า
            if(unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
            if(unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
            base += unit_tmp * 3.2484; // หน่วยแรกแพงกว่าแบบ 1
            service_charge = 24.62; // ค่าบริการแพงกว่า
            break;
    }
    base_tariff = base + service_charge; // รวมค่าไฟฐาน
    ft_charge = unit * Ft; // ค่า Ft = หน่วย x อัตรา Ft
    vat_charge = (base_tariff + ft_charge) * VAT; // VAT 7%
    cost = base_tariff + ft_charge + vat_charge; // รวมทั้งหมด
    system("cls");
    if(choice == 1) printf("1.1.1 อัตราปกติ ปริมาณการใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n\n");
    if(choice == 2) printf("1.1.2 อัตราปกติ ปริมาณการใช้พลังงานไฟฟ้าเกินกว่า 150 หน่วยต่อเดือน\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟบ้านแบบ TOU (1.2) แยกตามช่วงเวลา
void residentialTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(1); // ดึงค่า Ft สำหรับบ้าน
    system("cls");
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 2); // เลือกแรงดันไฟฟ้า
    switch(choice){
        case 1: // แรงดันสูง
            onPeak = 5.1135; // อัตราช่วง peak
            offPeak = 2.6037; // อัตราช่วง off-peak
            holiday = 2.6037; // อัตราช่วงวันหยุด
            service_charge = 312.24; // ค่าบริการแพง
            break;
        case 2: // แรงดันต่ำ
            onPeak = 5.7982;
            offPeak = 2.6369;
            holiday = 2.6369;
            service_charge = 24.62; // ค่าบริการถูกกว่า
            break;
    }
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &NeedOnPeak); // หน่วยช่วง peak
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &NeedOffPeak); // หน่วยช่วง off-peak
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &NeedHoliday); // หน่วยช่วงวันหยุด
    base += NeedOnPeak * onPeak; // คำนวณค่าไฟช่วง peak
    base += NeedOffPeak * offPeak; // คำนวณค่าไฟช่วง off-peak
    base += NeedHoliday * holiday; // คำนวณค่าไฟช่วงวันหยุด
    base_tariff = base + service_charge;
    ft_charge = (NeedOnPeak + NeedOffPeak + NeedHoliday) * Ft; // Ft คิดจากหน่วยรวม
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("1.2 อัตราตามช่วงเวลาของการใช้ (Time of Use Tariff : TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการขนาดเล็กแบบปกติ (2.1)
void smallBusinessNormalRate(){
    double Ft, unit, cost, base_tariff, ft_charge, vat_charge, service_charge, base = 0;
    int choice;
    Ft = getFt(0); // ดึง Ft สำหรับไม่ใช่บ้าน
    system("cls");
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 2);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    switch(choice){
        case 1: // แรงดันสูง คิดอัตราเดียว
            service_charge = 312.24;
            base += unit * 3.9086;
            break;
        case 2: // แรงดันต่ำ มีขั้น
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
    system("cls");
    printf("2.1 อัตราปกติ (Normal Rate)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการขนาดเล็กแบบ TOU (2.2)
void smallBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 2);
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
    system("cls");
    printf("2.2 อัตราตามช่วงเวลาของการใช้ (Time of Use Tariff : TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการขนาดกลางแบบปกติ (3.1) มี Power Factor
void mediumBusiness(){
    double Ft, rate, power, Kilovar, kv_charge, unit, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    switch(choice){
        case 1:
            HighestRate = 175.70; // อัตราความต้องการสูงสุด
            rate = 3.1097; // อัตราต่อหน่วย
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
    getInput("ความต้องการพลังงานไฟฟ้าสูงสุด (กิโลวัตต์): ", &NeedOnHighestRate); // รับค่า demand
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive); // รับค่า reactive power
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    service_charge = 312.24;
    power = NeedOnHighestRate * HighestRate; // ค่า demand charge
    unit_price = unit * rate; // ค่าพลังงาน
    Kilovar = KVCharge(NeedReactive, NeedOnHighestRate); // คำนวณหน่วย Power Factor
    kv_charge = Kilovar * 56.07; // ค่า Power Factor
    base_tariff = unit_price + service_charge + power + kv_charge;  // รวมทุกอย่างในค่าไฟฐาน
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("3.1 อัตราปกติ (Normal Rate)\n\n"
        "\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n"
        "\t\tค่าความต้องการพลังไฟฟ้า %'21.2f บาท\n" // ค่า demand
        "\t\tค่าพลังงานไฟฟ้า %'28.2f บาท\n" // ค่าหน่วย
        "\t\tค่าเพาเวอร์แฟคเตอร์\n"
        "\t\tจำนวนกิโลวาร์ที่คิดเงิน %24.0f กิโลวาร์\n" // หน่วย Power Factor
        "\t\tจำนวนเงิน %'33.2f บาท\n" // ค่า Power Factor
        "\t\tค่าบริการ %'33.2f บาท\n"
        "\t\tรวมค่าไฟฟ้าฐาน %'28.2f บาท\n\n"
        "\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n"
        "\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %'17.2f บาท\n\n"
        "\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n"
        "\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %'13.2f บาท\n\n"
        "\tรวมเงินค่าไฟฟ้า %'36.2f บาท\n",
        power, unit_price, Kilovar, kv_charge, service_charge, base_tariff, 
        ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการขนาดกลางแบบ TOU (3.2) มีทั้ง demand และหน่วยแยกช่วง
void mediumBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, power, Kilovar, kv_charge, unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    switch(choice){
        case 1:
            HighestRate = 74.14; // อัตรา demand ช่วง peak
            rateOn = 4.1025; // อัตราช่วง peak
            rateOff = 2.5849; // อัตราช่วง off-peak
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
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak); // demand ช่วง peak
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวาร์): ", &NeedOffPeak); // demand ช่วง off-peak
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (หน่วย): ", &NeedHoliday); // demand ช่วงวันหยุด
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &onPeak); // หน่วยช่วง peak
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &offPeak); // หน่วยช่วง off-peak
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &holiday); // หน่วยช่วงวันหยุด
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive); // ค่า reactive power
    service_charge = 312.24;
    power = NeedOnPeak * HighestRate; // ค่า demand คิดจาก peak เท่านั้น
    unit_price = (onPeak * rateOn) + ((offPeak + holiday) * rateOff); // ค่าหน่วยแยกตามช่วง
    Kilovar = KVCharge(NeedReactive, (max(NeedOnPeak, max(NeedOffPeak, NeedHoliday)))); // Power Factor ใช้ demand สูงสุด
    kv_charge = Kilovar * 56.07;
    base = power + unit_price + service_charge + kv_charge; // รวมทุกอย่างในค่าไฟฐาน
    base_tariff = unit_price + service_charge + power + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("3.2 อัตราตามช่วงเวลาของการใช้ (Time of Use Tariff : TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการขนาดใหญ่แบบ TOD (4.1)
void largeBusinessTODRate(){
    double Ft, Kilovar, unit_price, kv_charge, base_tariff, vat_charge, ft_charge, NeedOnPeak, unit, NeedOffPeak, NeedPartialPeak, NeedReactive, base = 0, cost, NeedRateOn, NeedRatePartial, rateOn, service_charge;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Partial Peak (กิโลวัตต์): ", &NeedPartialPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    switch(choice){
        case 1:
            NeedRateOn = 224.3; // อัตรา demand ช่วง peak
            NeedRatePartial = 29.91; // อัตรา demand ช่วง partial peak
            rateOn = 3.1097; // อัตราหน่วยเดียว
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
    base = (NeedOnPeak * NeedRateOn) + ((NeedPartialPeak - NeedOnPeak) * NeedRatePartial); // ค่า demand คิดจาก peak และ partial
    unit_price = unit * rateOn; // ค่าหน่วยคิดอัตราเดียว
    Kilovar = KVCharge(NeedReactive, max(NeedOnPeak, max(NeedPartialPeak, NeedOffPeak))); // Power Factor ใช้ demand สูงสุด
    kv_charge = Kilovar * 56.07;
    base_tariff = base + unit_price + kv_charge + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("4.1 อัตราตามช่วงเวลา (Time of Day Rate : TOD Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการขนาดใหญ่แบบ TOU (4.2)
void largeBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, Kilovar, kv_charge,  unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (กิโลวัตต์): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &onPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &offPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &holiday);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
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
    service_charge = 312.24;
    base = NeedOnPeak * HighestRate; // ค่า demand คิดจาก peak
    unit_price = (onPeak * rateOn) + ((offPeak + holiday) * rateOff); // ค่าหน่วยแยกตามช่วง
    Kilovar = KVCharge(NeedReactive, max(NeedOnPeak, max(NeedOffPeak, NeedHoliday)));
    kv_charge = Kilovar * 56.07;
    base_tariff = base + service_charge + unit_price + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("4.2 อัตราตามช่วงเวลาของการใช้ (Time of Use Tariff : TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟองค์กรไม่แสวงหากำไรแบบปกติ (6.1)
void nonProfitOrganization(){
    double Ft, unit, unit_tmp, cost, base_tariff, ft_charge, vat_charge, service_charge, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    switch(choice){
        case 1:
            base += unit * 3.4149; // อัตราเดียว
            service_charge = 312.24;
            break;
        case 2:
            base += unit * 3.5849; // อัตราเดียว
            service_charge = 312.24;
            break;
        case 3:
            unit_tmp = unit;
            if(unit_tmp > 10) base += (unit_tmp - 10) * 3.8919, unit_tmp = 10; // เกิน 10 หน่วย คิดแพงขึ้น
            base += unit_tmp * 2.8013; // 10 หน่วยแรกถูก
            service_charge = 20;
            break;
    }
    base_tariff = base + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("6.1 อัตราปกติ (Normal Rate)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟสูบน้ำเพื่อเกษตรแบบปกติ (7.1)
void agricultureWaterPumping(){
    double Ft, ft_charge, service_charge, vat_charge, cost, base = 0, unit, unit_tmp, base_tariff;
    Ft = getFt(0);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    service_charge = 115.16;
    unit_tmp = unit;
    if(unit_tmp > 100) base += (unit_tmp - 100) * 3.2405, unit_tmp = 100; // เกิน 100 คิดแพงขึ้น
    base += unit_tmp * 2.0889; // 100 หน่วยแรกถูก
    ft_charge = unit * Ft;
    base_tariff = base + service_charge;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = vat_charge + ft_charge + base_tariff;
    system("cls");
    printf("\t7.1 อัตราปกติ (Normal Rate)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟฟ้าชั่วคราว (8)
void temporaryElectricity(){
    double Ft, service_charge, ft_charge, vat_charge, base, base_tariff, unit, cost;
    Ft = getFt(0);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    service_charge = 0; // ไม่มีค่าบริการ
    base = unit * 6.8025; // อัตราสูงมาก
    base_tariff = base + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("8 อัตราปกติ (Normal Rate)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟองค์กรไม่แสวงหากำไรแบบ TOU (6.2)
void nonProfitOrganizationTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, Kilovar, kv_charge, unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (กิโลวัตต์): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &onPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &offPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &holiday);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
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
    service_charge = 312.24;
    base = NeedOnPeak * HighestRate;
    unit_price = (onPeak * rateOn) + ((offPeak + holiday) * rateOff);
    Kilovar = KVCharge(NeedReactive, max(NeedOnPeak, NeedOffPeak)); // Power Factor ใช้ demand สูงสุดจาก peak หรือ off-peak
    kv_charge = Kilovar * 56.07;
    base_tariff = base + service_charge + unit_price + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("6.2 อัตราตามช่วงเวลาของการใช้ (Time of Use Tariff : TOU Tariff)\n\n"); 
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการเฉพาะอย่างแบบปกติ (5.1)
void specialBusinessNormalRate(){
    double Ft, rateOn, Kilovar, kv_charge, unit, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังงานไฟฟ้าสูงสุด (กิโลวัตต์): ", &NeedOnHighestRate);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    switch(choice){
        case 1:
            HighestRate = 220.56;
            rateOn = 3.1097;
            break;
        case 2:
            HighestRate = 256.07;
            rateOn = 3.1471;
            break;
        case 3:
            HighestRate = 276.64;
            rateOn = 3.1751;
            break;
    }
    service_charge = 312.24;
    base = HighestRate * NeedOnHighestRate; // ค่า demand
    unit_price = unit * rateOn; // ค่าหน่วย
    Kilovar = KVCharge(NeedReactive, NeedOnHighestRate);
    kv_charge = Kilovar * 56.07;
    base_tariff = base + service_charge + unit_price + kv_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("5.1 อัตราปกติ (Normal Rate)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟกิจการเฉพาะอย่างแบบ TOU (5.2)
void specialBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, Kilovar, kv_charge, unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (กิโลวัตต์): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &onPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &offPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &holiday);
    getInput("ความต้องการพลังไฟฟ้ารีแอคตีฟ (กิโลวาร์): ", &NeedReactive);
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
    service_charge = 312.24;
    base = NeedOnPeak * HighestRate;
    unit_price = (onPeak * rateOn) + ((offPeak + holiday) * rateOff);
    Kilovar = KVCharge(NeedReactive, max(NeedOnPeak, max(NeedOffPeak, NeedHoliday)));
    kv_charge = Kilovar * 56.07;
    base_tariff = base + service_charge + unit_price + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("5.2 อัตราตามช่วงเวลาของการใช้ (Time of Use Tariff : TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// คำนวณค่าไฟสูบน้ำเพื่อเกษตรแบบ TOU (7.2)
void agricultureWaterPumpingTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, HighestRate, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 22 - 33 กิโลโวลต์\n(2) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 2);
    getInput("ความต้องการพลังไฟฟ้าช่วง On Peak (กิโลวัตต์): ", &NeedOnPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Off Peak (กิโลวัตต์): ", &NeedOffPeak);
    getInput("ความต้องการพลังไฟฟ้าช่วง Holiday (กิโลวัตต์): ", &NeedHoliday);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง On Peak (หน่วย): ", &onPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Off Peak (หน่วย): ", &offPeak);
    getInput("ปริมาณการใช้พลังงานไฟฟ้าช่วง Holiday (หน่วย): ", &holiday);
    switch(choice){
        case 1:
            HighestRate = 132.93;
            rateOn = 4.1839;
            rateOff = 2.6037;
            break;
        case 2:
            HighestRate = 210;
            rateOn = 4.3297;
            rateOff = 2.6369;
            break;
    }
    service_charge = 204.07;
    base += (NeedOnPeak * HighestRate); // ค่า demand
    base += (onPeak * rateOn) + (offPeak * rateOff) + (holiday * rateOff); // ค่าหน่วยแยกตามช่วง
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    base_tariff = base + service_charge;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + vat_charge + ft_charge;
    system("cls");
    printf("7.2 อัตราตามช่วงเวลาของการใช้ (Time of Use Tariff : TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}
// เมนูหลักให้เลือกประเภทไฟฟ้า
void menu(){
    int choice;
    system("cls");
    printf("ประเภทไฟฟ้า\n");
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
        case 1: residentialNormalRate(); break;
        case 2: residentialTOURate(); break;
        case 3: smallBusinessNormalRate(); break;
        case 4: smallBusinessTOURate(); break;
        case 5: mediumBusiness(); break;
        case 6: mediumBusinessTOURate(); break;
        case 7: largeBusinessTODRate(); break;
        case 8: largeBusinessTOURate(); break;
        case 9: specialBusinessNormalRate(); break;
        case 10: specialBusinessTOURate(); break;
        case 11: nonProfitOrganization(); break;
        case 12: nonProfitOrganizationTOURate(); break;
        case 13: agricultureWaterPumping(); break;
        case 14: agricultureWaterPumpingTOURate(); break;
        case 15: temporaryElectricity(); break;
    }
}
// ฟังก์ชันหลัก วนลูปเมนู
int main(){
    setlocale(LC_NUMERIC, ""); // ตั้งค่าให้ตัวเลขมี comma (เช่น 10,000)

    while(1){ // วนไปเรื่อย ๆ กด X เพื่อออก
        system("cls");
        menu();
        printf("\nกด Enter เพื่อทำงานอีกครั้ง...(กด Ctrl + C เพื่อออก)");
        char x = getch(); // รอผู้ใช้กด Enter เพื่อเริ่มใหม่
        if(tolower(x) == 'x'){
            break;
        }
    }
    return 0;
}