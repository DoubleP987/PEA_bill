#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

const double VAT = 0.07; // อัตราภาษีมูลค่าเพิ่ม 7% (กำหนดเป็นค่าคงที่เพื่อใช้ในทุกฟังก์ชัน)

// ฟังก์ชันรับอินพุตตัวเลขจากผู้ใช้พร้อมตรวจสอบความถูกต้อง
void getInput(char *msg, double *value) {
    char ch;
    while (1) {
        printf("%s", msg);
        // ตรวจสอบว่าอินพุตเป็นตัวเลขจริง ๆ และไม่ติดลบ
        if (scanf("%lf", value) == 1 && *value >= 0) {
            // ตรวจสอบว่ามีตัวอักษรแปลกปลอมหลังตัวเลขหรือไม่ (เช่น "123abc")
            if (scanf("%c", &ch) == 1 && ch != '\n') {
                printf("ข้อมูลไม่ถูกต้อง\n");
                while (getchar() != '\n'); // ล้าง buffer เพื่อป้องกันการค้างของอินพุตเก่า
            } else {
                break; // ออกเมื่ออินพุตถูกต้อง (เป็นตัวเลขและไม่มีตัวอักษรต่อท้าย)
            }
        } else {
            printf("ข้อมูลไม่ถูกต้อง\n");
            while (getchar() != '\n'); // ล้าง buffer ถ้าอินพุตไม่ใช่ตัวเลข
        }
    }
    // หมายเหตุ: ฟังก์ชันนี้ใช้ while(1) ซึ่งอาจทำให้ CPU ทำงานหนักถ้าผู้ใช้ป้อนผิดบ่อย ๆ
    // อาจพิจารณาใช้ fgets() + sscanf() เพื่อลดการเรียก scanf() หลายครั้ง
}

// ฟังก์ชันรับตัวเลือกจากผู้ใช้ (เช่น 1-15) พร้อมตรวจสอบว่าอยู่ในช่วงที่กำหนด
void getOption(char *msg, int *parameter, int option) {
    char ch;
    while (1) {
        printf("%s", msg);
        // ตรวจสอบว่าอินพุตเป็นจำนวนเต็ม และอยู่ในช่วง 1 ถึง option
        if (scanf("%d", parameter) == 1 && *parameter >= 1 && *parameter <= option) {
            // ตรวจสอบตัวอักษรแปลกปลอมหลังตัวเลข
            if (scanf("%c", &ch) == 1 && ch != '\n') {
                printf("ข้อมูลไม่ถูกต้อง\n");
                while (getchar() != '\n');
            } else {
                break; // ออกเมื่อข้อมูลถูกต้อง
            }
        } else {
            printf("ข้อมูลไม่ถูกต้อง\n");
            while (getchar() != '\n');
        }
    }
}

// คำนวณค่า Power Factor (หน่วยกิโลวาร์ที่ต้องชำระ) โดยใช้ความสัมพันธ์ระหว่าง kVAr และ kW
double KVCharge(double kv, double kw) {
    // คำนวณ threshold = kw * 0.6197 (ค่า Power Factor ที่ยอมรับได้)
    // ถ้า kv เกิน threshold จะคิดเงินส่วนเกิน โดยปัดเป็นจำนวนเต็มด้วย round()
    return round(fmax(0, (kv - (kw * 0.6197))));
    // หมายเหตุ: fmax() ใช้เพื่อให้แน่ใจว่าไม่ติดลบ แต่สามารถใช้ if แทนได้เพื่อลดการเรียกฟังก์ชัน
}

// เลือกค่า Ft (ค่าไฟฟ้าแปรผัน) ตามเดือนและปี
double getFt(int isResidential) {
    int month, year;
    system("cls");
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
    getOption("เดือน: ", &month, 12);

    printf("\n(1) 2568\n(2) 2567\n(3) 2566\n");
    char ch;
    while (1) {
        printf("ปี: ");
        // รองรับทั้งเลข 1-3 และปีเต็ม (2566-2568)
        if (scanf("%d", &year) == 1 && ((year >= 1 && year <= 3) || (year >= 2566 && year <= 2568))) {
            if (scanf("%c", &ch) == 1 && ch != '\n') {
                printf("ข้อมูลไม่ถูกต้อง\n");
                while (getchar() != '\n');
            } else {
                break;
            }
        } else {
            printf("ข้อมูลไม่ถูกต้อง\n");
            while (getchar() != '\n');
        }
    }
    // แปลง year จาก 1-3 เป็น 2566-2568 ถ้าผู้ใช้ป้อนแบบสั้น
    if (year <= 3) year = 2568 - (year - 1);

    // กำหนดค่า Ft ตามปีและเดือน
    if (year == 2568) return 0.3672; // ค่า Ft คงที่ทุกเดือนในปี 2568
    else if (year == 2567) return 0.3972; // ค่า Ft คงที่ทุกเดือนในปี 2567
    else if (year == 2566) {
        if (month >= 9 && month <= 12) return 0.2048;
        else if (month >= 5 && month <= 9) return 0.9119;
        else if (month >= 1 && month <= 4) {
            return isResidential ? 0.9343 : 1.5492; // แยกตามประเภทบ้านอยู่อาศัยหรือไม่
        }
    }
    return 0; // ไม่ควรถึงจุดนี้ แต่ใส่ไว้เพื่อความปลอดภัย
}

// ฟังก์ชันแสดงผลบิลค่าไฟในรูปแบบที่กำหนด
void displayBill(double base, double service_charge, double base_tariff, double ft_charge, double vat_charge, double cost) {
    printf("\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n"
           "\t\tค่าพลังงานไฟฟ้า %'28.2f บาท\n"
           "\t\tค่าบริการ %'33.2f บาท\n"
           "\t\tรวมค่าไฟฟ้าฐาน %'28.2f บาท\n"
           "\n\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n"
           "\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %'17.2f บาท\n"
           "\n\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n"
           "\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %'13.2f บาท\n"
           "\n\tรวมเงินค่าไฟฟ้า %'36.2f บาท\n",
           base, service_charge, base_tariff, ft_charge, vat_charge, cost);
    // หมายเหตุ: ฟังก์ชันนี้ใช้ได้ดีกับหลายประเภท แต่บางประเภท (เช่น mediumBusiness) มีส่วนประกอบเพิ่มเติม
    // อาจต้องปรับให้ยืดหยุ่นกว่านี้ถ้าต้องการรองรับทุกรูปแบบ
}

// ตัวอย่างฟังก์ชันคำนวณค่าไฟ: บ้านอยู่อาศัย (อัตราปกติ)
void residentialNormalRate() {
    double Ft, unit, unit_tmp, base_tariff, vat_charge, ft_charge, service_charge, cost, base = 0;
    int choice;
    system("cls");
    printf("1. ประเภทที่ 1.1.1 ใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n"
           "2. ประเภทที่ 1.1.2 ใช้พลังงานไฟฟ้าเกิน 150 หน่วยต่อเดือน\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3); // หมายเหตุ: ใส่ 3 แต่มีแค่ 2 ตัวเลือก (อาจเป็น typo)
    Ft = getFt(1);
    getInput("ผู้ใช้ไฟฟ้ามีปริมาณการใช้พลังงานไฟฟ้า (หน่วย): ", &unit);
    unit_tmp = unit; // ใช้ตัวแปรชั่วคราวเพื่อคำนวณตามช่วงหน่วย

    // คำนวณค่าไฟฟ้าตามช่วงหน่วย (progressive rate)
    switch (choice) {
        case 1: // ใช้ไม่เกิน 150 หน่วย
            if (unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
            if (unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
            if (unit_tmp > 100) base += (unit_tmp - 100) * 3.7171, unit_tmp = 100;
            if (unit_tmp > 35) base += (unit_tmp - 35) * 3.6237, unit_tmp = 35;
            if (unit_tmp > 25) base += (unit_tmp - 25) * 3.2405, unit_tmp = 25;
            if (unit_tmp > 15) base += (unit_tmp - 15) * 2.9882, unit_tmp = 15;
            base += unit_tmp * 2.3488;
            service_charge = 8.19;
            break;
        case 2: // ใช้เกิน 150 หน่วย
            if (unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
            if (unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
            base += unit_tmp * 3.2484;
            service_charge = 24.62;
            break;
    }
    base_tariff = base + service_charge; // รวมค่าไฟฟ้าฐาน
    ft_charge = unit * Ft; // ค่า Ft = จำนวนหน่วย x อัตรา Ft
    vat_charge = (base_tariff + ft_charge) * VAT; // VAT 7%
    cost = base_tariff + ft_charge + vat_charge; // รวมทั้งหมด

    system("cls");
    if (choice == 1) printf("1.1.1 อัตราปกติ ปริมาณการใช้พลังงานไฟฟ้าไม่เกิน 150 หน่วยต่อเดือน\n\n");
    if (choice == 2) printf("1.1.2 อัตราปกติ ปริมาณการใช้พลังงานไฟฟ้าเกินกว่า 150 หน่วยต่อเดือน\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// ตัวอย่างฟังก์ชันที่ซับซ้อน: กิจการขนาดกลาง (อัตราปกติ)
void mediumBusiness() {
    double Ft, rate, power, Kilovar, kv_charge, unit, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) แรงดัน 69 กิโลโวลต์ ขึ้นไป\n(2) แรงดัน 22 - 33 กิโลโวลต์\n(3) แรงดันต่ำกว่า 22 กิโลโวลต์\n");
    getOption("เลือกประเภทแรงดันไฟฟ้า: ", &choice, 3);

    // กำหนดอัตราค่าบริการตามระดับแรงดัน
    switch (choice) {
        case 1:
            HighestRate = 175.70; // อัตราความต้องการพลังงานสูงสุด (บาท/kW)
            rate = 3.1097; // อัตราต่อหน่วย (บาท/kWh)
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

    service_charge = 312.24; // ค่าบริการคงที่
    power = NeedOnHighestRate * HighestRate; // ค่า demand charge (ความต้องการสูงสุด x อัตรา)
    unit_price = unit * rate; // ค่าพลังงานไฟฟ้า (หน่วย x อัตรา)
    Kilovar = KVCharge(NeedReactive, NeedOnHighestRate); // คำนวณหน่วย kVAr ที่ต้องชำระ
    kv_charge = Kilovar * 56.07; // ค่า Power Factor (kVAr x อัตรา)
    base = power + unit_price + service_charge + kv_charge; // รวมค่าไฟฟ้าฐานทั้งหมด
    base_tariff = unit_price + service_charge + power + kv_charge; // ค่าไฟฟ้าฐาน (คำนวณซ้ำกับ base?)
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;

    system("cls");
    // แสดงผลแบบกำหนดเอง (ไม่ใช้ displayBill เพราะมีส่วนประกอบเพิ่มเติม)
    printf("3.1 อัตราปกติ (Normal Rate)\n\n"
           "\tส่วนที่ 1 ค่าไฟฟ้าฐาน\n\n"
           "\t\tค่าความต้องการพลังไฟฟ้า %'21.2f บาท\n"
           "\t\tค่าพลังงานไฟฟ้า %'28.2f บาท\n"
           "\t\tค่าเพาเวอร์แฟคเตอร์\n"
           "\t\tจำนวนกิโลวาร์ที่คิดเงิน %24.0f กิโลวาร์\n"
           "\t\tจำนวนเงิน %'33.2f บาท\n"
           "\t\tค่าบริการ %'33.2f บาท\n"
           "\t\tรวมค่าไฟฟ้าฐาน %'28.2f บาท\n\n"
           "\tส่วนที่ 2 ค่าไฟฟ้าแปร (Ft)\n\n"
           "\t\tจำนวนพลังงานไฟฟ้า x ค่า Ft %'17.2f บาท\n\n"
           "\tส่วนที่ 3 ค่าภาษีมูลค่าเพิ่ม 7%%\n\n"
           "\t\t(ค่าไฟฟ้าฐาน + ค่า Ft) x 7/100 %'13.2f บาท\n\n"
           "\tรวมเงินค่าไฟฟ้า %'36.2f บาท\n",
           power, unit_price, Kilovar, kv_charge, service_charge, base_tariff,
           ft_charge, vat_charge, cost);
    // หมายเหตุ: การแสดงผลที่นี่ไม่สอดคล้องกับฟังก์ชันอื่น (มี power และ kv_charge เพิ่ม)
    // อาจพิจารณาปรับ displayBill ให้ยืดหยุ่นกว่านี้
}

// ฟังก์ชันเมนูหลัก
void menu() {
    int choice;
    system("cls");
    printf("ประเภทไฟฟ้า\n");
    printf("(1) 1.1 บ้านอยู่อาศัย (อัตราปกติ)\n");
    // ... (รายการเมนูอื่น ๆ)
    getOption("เลือกประเภทไฟฟ้า(1 - 15): ", &choice, 15);
    switch (choice) {
        case 1: residentialNormalRate(); break;
        // ... (case อื่น ๆ)
    }
}

int main() {
    setlocale(LC_NUMERIC, ""); // ตั้งค่า locale เพื่อให้ตัวเลขมี comma (เช่น 10,000)
    while (1) { // ลูปเมนูไม่สิ้นสุด (ออกได้ด้วย Ctrl+C)
        system("cls");
        menu();
        printf("\nกด Enter เพื่อทำงานอีกครั้ง...");
        getchar(); // รอผู้ใช้กด Enter เพื่อเริ่มใหม่
    }
    return 0;
}