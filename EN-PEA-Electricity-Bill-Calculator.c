#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

const double VAT = 0.07; // 7% Value Added Tax rate used everywhere VAT is calculated

// Function to get numeric input from the user and check if it is valid
void getInput(char *msg, double *value){
    char ch;
    while(1){ // Loop until valid input is received
        printf("%s", msg); // Display message to let the user know what to enter
        if(scanf("%lf", value) == 1 && *value >= 0){ // If input is a valid number and non-negative
            if(scanf("%c", &ch) == 1 && ch != '\n'){ // Check if there are stray characters after (e.g., "12a")
                printf("Invalid input\n"); // If there are, notify the user
                while(getchar() != '\n'); // Clear the input buffer
            }else{
                break; // If valid, exit the loop
            }
        }else{
            printf("Invalid input\n"); // If not a number or negative, notify the user
            while(getchar() != '\n'); // Clear buffer for new input
        }
    }
}

// Function to get an option (e.g., 1-15) and check if it's within the specified range
void getOption(char *msg, int *parameter, int option){
    char ch;
    while(1){ // Loop until a valid option is received
        printf("%s", msg); // Display message to let the user know what to choose
        if(scanf("%d", parameter) == 1 && *parameter >= 1 && *parameter <= option){ // If input is a number within range
            if(scanf("%c", &ch) == 1 && ch != '\n'){ // Check for stray characters after input
                printf("Invalid input\n");
                while(getchar() != '\n'); // Clear buffer
            }else{
                break; // If valid, exit the loop
            }
        }else{
            printf("Invalid input\n");
            while(getchar() != '\n'); // Clear buffer if input is invalid
        }
    }
}
// Function to return the greater of two double values
double max(double a, double b) { 
    // Compare the two values
    if (a > b) { 
        return a; // If 'a' is greater, return 'a'
    } else {
        return b; // Otherwise, return 'b'
    }
}
// Function to calculate Power Factor charge if it exceeds the threshold
double KVCharge(double kv, double kw){
    return round(max(0, (kv - (kw * 0.6197)))); // Calculate excess of kv compared to kw * 0.6197, round to nearest integer, return 0 if negative
}

// Function to select Ft rate based on month and year
double getFt(int isResidential){ // isResidential = 1 for residential, 0 for non-residential
    int month, year;
    system("cls"); // Clear screen before showing menu
    printf("Select month\n"
        "(1)  January\n"
        "(2)  February\n"
        "(3)  March\n"
        "(4)  April\n"
        "(5)  May\n"
        "(6)  June\n"
        "(7)  July\n"
        "(8)  August\n"
        "(9)  September\n"
        "(10) October\n"
        "(11) November\n"
        "(12) December\n"); 
    getOption("Month: ", &month, 12); // Select month 1-12

    printf("\n(1) 2568\n(2) 2567\n(3) 2566\n");
    char ch;
    while(1){ // Loop to get valid year
        printf("Year: ");
        if(scanf("%d", &year) == 1 && ((year >= 1 && year <= 3) || (year >= 2566 && year <= 2568))){ // Accept 1-3 or 2566-2568
            if(scanf("%c", &ch) == 1 && ch != '\n'){
                printf("Invalid input\n");
                while(getchar() != '\n');
            }else{
                break;
            }
        }else{
            printf("Invalid input\n");
            while(getchar() != '\n');
        }
    }
    if(year == 1 || year == 2568){
        return 0.3672; // Year 2568 Ft rate fixed for all months
    } else if(year == 2 || year == 2567){
        return 0.3972; // Year 2067 Ft rate fixed for all months
    } else if(year == 3 || year == 2566){ // Year 2566 varies by month
        if (month >= 9 && month <= 12){
            return 0.2048; // Months 9-12
        }else if(month >= 5 && month <= 9){ 
            return 0.9119; // Months 5-9
        }else if(month >= 1 && month <= 4){ 
            if(isResidential){
                return 0.9343; // Months 1-4 for residential
            }else{
                return 1.5492; // Months 1-4 for non-residential
            }
        }
    }
    return 0; // Shouldn't reach here, but included for edge cases
}

// Function to display the electricity bill in a structured format
void displayBill(double base, double service_charge, double base_tariff, double ft_charge, double vat_charge, double cost){
    printf("\tSection 1: Base Electricity Cost\n\n"
    "\t\tElectricity Usage Cost %'28.2f Baht\n" // Cost from units used
    "\t\tService Charge %'36.2f Baht\n" // Fixed service charge
    "\t\tTotal Base Electricity Cost %'23.2f Baht\n" // Usage + service charge
    "\n\tSection 2: Variable Electricity Cost (Ft)\n\n"
    "\t\tUnits x Ft Rate %'35.2f Baht\n" // Ft cost based on units
    "\n\tSection 3: 7%% Value Added Tax\n\n"
    "\t\t(Base Cost + Ft) x 7/100 %'26.2f Baht\n" // VAT 7% of total
    "\n\tTotal Electricity Cost %'36.2f Baht\n", // Sum of all costs
    base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate electricity cost for residential normal rate (1.1)
void residentialNormalRate(){
    double Ft, unit, unit_tmp, base_tariff, vat_charge, ft_charge, service_charge, cost, base = 0;
    int choice;
    system("cls");
    printf("1. Type 1.1.1 Uses less than 150 units per month\n2. Type 1.1.2 Uses more than 150 units per month\n");
    getOption("Select electricity type: ", &choice, 2); // Choose 1 or 2
    Ft = getFt(1); // Get Ft rate for residential
    getInput("User's electricity usage (units): ", &unit); // Get number of units used
    unit_tmp = unit; // Store units in temp variable for step-by-step calculation
    switch(choice){
        case 1: // Uses less than 150 units, tiered rates
            if(unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400; // Above 400, most expensive
            if(unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
            if(unit_tmp > 100) base += (unit_tmp - 100) * 3.7171, unit_tmp = 100;
            if(unit_tmp > 35) base += (unit_tmp - 35) * 3.6237, unit_tmp = 35;
            if(unit_tmp > 25) base += (unit_tmp - 25) * 3.2405, unit_tmp = 25;
            if(unit_tmp > 15) base += (unit_tmp - 15) * 2.9882, unit_tmp = 15;
            base += unit_tmp * 2.3488; // First units cheapest
            service_charge = 8.19; // Cheaper service charge
            break;
        case 2: // Uses more than 150 units, fewer tiers
            if(unit_tmp > 400) base += (unit_tmp - 400) * 4.4217, unit_tmp = 400;
            if(unit_tmp > 150) base += (unit_tmp - 150) * 4.2218, unit_tmp = 150;
            base += unit_tmp * 3.2484; // First units more expensive than case 1
            service_charge = 24.62; // More expensive service charge
            break;
    }
    base_tariff = base + service_charge; // Total base cost
    ft_charge = unit * Ft; // Ft cost = units x Ft rate
    vat_charge = (base_tariff + ft_charge) * VAT; // VAT 7%
    cost = base_tariff + ft_charge + vat_charge; // Total cost
    system("cls");
    if(choice == 1) printf("1.1.1 Normal Rate, Usage not exceeding 150 units per month\n\n");
    if(choice == 2) printf("1.1.2 Normal Rate, Usage exceeding 150 units per month\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate residential TOU rate (1.2) separated by time periods
void residentialTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(1); // Get Ft rate for residential
    system("cls");
    printf("(1) Voltage 22 - 33 kilovolts\n(2) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 2); // Choose voltage type
    switch(choice){
        case 1: // High voltage
            onPeak = 5.1135; // Peak rate
            offPeak = 2.6037; // Off-peak rate
            holiday = 2.6037; // Holiday rate
            service_charge = 312.24; // Expensive service charge
            break;
        case 2: // Low voltage
            onPeak = 5.7982;
            offPeak = 2.6369;
            holiday = 2.6369;
            service_charge = 24.62; // Cheaper service charge
            break;
    }
    getInput("Electricity usage during On Peak (units): ", &NeedOnPeak); // Units during peak
    getInput("Electricity usage during Off Peak (units): ", &NeedOffPeak); // Units during off-peak
    getInput("Electricity usage during Holiday (units): ", &NeedHoliday); // Units during holiday
    base += NeedOnPeak * onPeak; // Calculate peak cost
    base += NeedOffPeak * offPeak; // Calculate off-peak cost
    base += NeedHoliday * holiday; // Calculate holiday cost
    base_tariff = base + service_charge;
    ft_charge = (NeedOnPeak + NeedOffPeak + NeedHoliday) * Ft; // Ft based on total units
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("1.2 Time of Use Tariff (TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate small business normal rate (2.1)
void smallBusinessNormalRate(){
    double Ft, unit, cost, base_tariff, ft_charge, vat_charge, service_charge, base = 0;
    int choice;
    Ft = getFt(0); // Get Ft rate for non-residential
    system("cls");
    printf("(1) Voltage 22 - 33 kilovolts\n(2) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 2);
    getInput("User's electricity usage (units): ", &unit);
    switch(choice){
        case 1: // High voltage, single rate
            service_charge = 312.24;
            base += unit * 3.9086;
            break;
        case 2: // Low voltage, tiered rates
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
    printf("2.1 Normal Rate\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate small business TOU rate (2.2)
void smallBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 22 - 33 kilovolts\n(2) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 2);
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
    getInput("Electricity usage during On Peak (units): ", &NeedOnPeak);
    getInput("Electricity usage during Off Peak (units): ", &NeedOffPeak);
    getInput("Electricity usage during Holiday (units): ", &NeedHoliday);
    base += NeedOnPeak * onPeak;
    base += NeedOffPeak * offPeak;
    base += NeedHoliday * holiday;
    ft_charge = (NeedOnPeak + NeedOffPeak + NeedHoliday) * Ft;
    base_tariff = base + service_charge;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("2.2 Time of Use Tariff (TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate medium business normal rate (3.1) with Power Factor
void mediumBusiness(){
    double Ft, rate, power, Kilovar, kv_charge, unit, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    switch(choice){
        case 1:
            HighestRate = 175.70; // Highest demand rate
            rate = 3.1097; // Unit rate
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
    getInput("Maximum electricity demand (kilowatts): ", &NeedOnHighestRate); // Get demand
    getInput("Reactive power demand (kilovars): ", &NeedReactive); // Get reactive power
    getInput("User's electricity usage (units): ", &unit);
    service_charge = 312.24;
    power = NeedOnHighestRate * HighestRate; // Demand charge
    unit_price = unit * rate; // Energy cost
    Kilovar = KVCharge(NeedReactive, NeedOnHighestRate); // Calculate Power Factor units
    kv_charge = Kilovar * 56.07; // Power Factor charge
    base_tariff = unit_price + service_charge + power + kv_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("3.1 Normal Rate\n\n"
        "\tSection 1: Base Electricity Cost\n\n"
        "\t\tElectricity Demand Cost %'27.2f Baht\n" // Demand cost
        "\t\tElectricity Usage Cost %'28.2f Baht\n" // Unit cost
        "\t\tPower Factor Charge\n"
        "\t\tKilovars charged %34.0f kilovars\n" // Power Factor units
        "\t\tAmount %'44.2f Baht\n" // Power Factor cost
        "\t\tService Charge %'36.2f Baht\n"
        "\t\tTotal Base Electricity Cost %'23.2f Baht\n\n"
        "\tSection 2: Variable Electricity Cost (Ft)\n\n"
        "\t\tUnits x Ft Rate %'35.2f Baht\n\n"
        "\tSection 3: 7%% Value Added Tax\n\n"
        "\t\t(Base Cost + Ft) x 7/100 %'26.2f Baht\n\n"
        "\tTotal Electricity Cost %'36.2f Baht\n",
        power, unit_price, Kilovar, kv_charge, service_charge, base_tariff, 
        ft_charge, vat_charge, cost);
}

// Calculate medium business TOU rate (3.2) with demand and time-separated units
void mediumBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, power, Kilovar, kv_charge, unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    switch(choice){
        case 1:
            HighestRate = 74.14; // Peak demand rate
            rateOn = 4.1025; // Peak unit rate
            rateOff = 2.5849; // Off-peak unit rate
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
    getInput("Electricity demand during On Peak (kilowatts): ", &NeedOnPeak); // Peak demand
    getInput("Electricity demand during Off Peak (kilovars): ", &NeedOffPeak); // Off-peak demand
    getInput("Electricity demand during Holiday (units): ", &NeedHoliday); // Holiday demand
    getInput("Electricity usage during On Peak (units): ", &onPeak); // Peak units
    getInput("Electricity usage during Off Peak (units): ", &offPeak); // Off-peak units
    getInput("Electricity usage during Holiday (units): ", &holiday); // Holiday units
    getInput("Reactive power demand (kilovars): ", &NeedReactive); // Reactive power
    service_charge = 312.24;
    power = NeedOnPeak * HighestRate; // Demand cost based on peak only
    unit_price = (onPeak * rateOn) + ((offPeak + holiday) * rateOff); // Units cost by time
    Kilovar = KVCharge(NeedReactive, (max(NeedOnPeak, max(NeedOffPeak, NeedHoliday)))); // Power Factor uses highest demand
    kv_charge = Kilovar * 56.07;
    base = power + unit_price + service_charge + kv_charge; // Total base cost
    base_tariff = unit_price + service_charge + power + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("3.2 Time of Use Tariff (TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate large business TOD rate (4.1)
void largeBusinessTODRate(){
    double Ft, Kilovar, unit_price, kv_charge, base_tariff, vat_charge, ft_charge, NeedOnPeak, unit, NeedOffPeak, NeedPartialPeak, NeedReactive, base = 0, cost, NeedRateOn, NeedRatePartial, rateOn, service_charge;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    getInput("Electricity demand during On Peak (kilowatts): ", &NeedOnPeak);
    getInput("Electricity demand during Partial Peak (kilowatts): ", &NeedPartialPeak);
    getInput("Electricity demand during Off Peak (kilowatts): ", &NeedOffPeak);
    getInput("Reactive power demand (kilovars): ", &NeedReactive);
    getInput("User's electricity usage (units): ", &unit);
    switch(choice){
        case 1:
            NeedRateOn = 224.3; // Peak demand rate
            NeedRatePartial = 29.91; // Partial peak demand rate
            rateOn = 3.1097; // Single unit rate
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
    base = (NeedOnPeak * NeedRateOn) + ((NeedPartialPeak - NeedOnPeak) * NeedRatePartial); // Demand cost from peak and partial
    unit_price = unit * rateOn; // Single unit rate cost
    Kilovar = KVCharge(NeedReactive, max(NeedOnPeak, max(NeedPartialPeak, NeedOffPeak))); // Power Factor uses highest demand
    kv_charge = Kilovar * 56.07;
    base_tariff = base + unit_price + kv_charge + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("4.1 Time of Day Rate (TOD Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate large business TOU rate (4.2)
void largeBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, Kilovar, kv_charge,  unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    getInput("Electricity demand during On Peak (kilowatts): ", &NeedOnPeak);
    getInput("Electricity demand during Off Peak (kilowatts): ", &NeedOffPeak);
    getInput("Electricity demand during Holiday (kilowatts): ", &NeedHoliday);
    getInput("Electricity usage during On Peak (units): ", &onPeak);
    getInput("Electricity usage during Off Peak (units): ", &offPeak);
    getInput("Electricity usage during Holiday (units): ", &holiday);
    getInput("Reactive power demand (kilovars): ", &NeedReactive);
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
    base = NeedOnPeak * HighestRate; // Demand cost from peak
    unit_price = (onPeak * rateOn) + ((offPeak + holiday) * rateOff); // Units cost by time
    Kilovar = KVCharge(NeedReactive, max(NeedOnPeak, max(NeedOffPeak, NeedHoliday)));
    kv_charge = Kilovar * 56.07;
    base_tariff = base + service_charge + unit_price + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("4.2 Time of Use Tariff (TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate non-profit organization normal rate (6.1)
void nonProfitOrganization(){
    double Ft, unit, unit_tmp, cost, base_tariff, ft_charge, vat_charge, service_charge, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    getInput("User's electricity usage (units): ", &unit);
    switch(choice){
        case 1:
            base += unit * 3.4149; // Single rate
            service_charge = 312.24;
            break;
        case 2:
            base += unit * 3.5849; // Single rate
            service_charge = 312.24;
            break;
        case 3:
            unit_tmp = unit;
            if(unit_tmp > 10) base += (unit_tmp - 10) * 3.8919, unit_tmp = 10; // Above 10 units more expensive
            base += unit_tmp * 2.8013; // First 10 units cheaper
            service_charge = 20;
            break;
    }
    base_tariff = base + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("6.1 Normal Rate\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate agriculture water pumping normal rate (7.1)
void agricultureWaterPumping(){
    double Ft, ft_charge, service_charge, vat_charge, cost, base = 0, unit, unit_tmp, base_tariff;
    Ft = getFt(0);
    getInput("User's electricity usage (units): ", &unit);
    service_charge = 115.16;
    unit_tmp = unit;
    if(unit_tmp > 100) base += (unit_tmp - 100) * 3.2405, unit_tmp = 100; // Above 100 units more expensive
    base += unit_tmp * 2.0889; // First 100 units cheaper
    ft_charge = unit * Ft;
    base_tariff = base + service_charge;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = vat_charge + ft_charge + base_tariff;
    system("cls");
    printf("\t7.1 Normal Rate\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate temporary electricity cost (8)
void temporaryElectricity(){
    double Ft, service_charge, ft_charge, vat_charge, base, base_tariff, unit, cost;
    Ft = getFt(0);
    getInput("User's electricity usage (units): ", &unit);
    service_charge = 0; // No service charge
    base = unit * 6.8025; // High single rate
    base_tariff = base + service_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("8 Normal Rate\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate non-profit organization TOU rate (6.2)
void nonProfitOrganizationTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, Kilovar, kv_charge, unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    getInput("Electricity demand during On Peak (kilowatts): ", &NeedOnPeak);
    getInput("Electricity demand during Off Peak (kilowatts): ", &NeedOffPeak);
    getInput("Electricity demand during Holiday (kilowatts): ", &NeedHoliday);
    getInput("Electricity usage during On Peak (units): ", &onPeak);
    getInput("Electricity usage during Off Peak (units): ", &offPeak);
    getInput("Electricity usage during Holiday (units): ", &holiday);
    getInput("Reactive power demand (kilovars): ", &NeedReactive);
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
    Kilovar = KVCharge(NeedReactive, max(NeedOnPeak, NeedOffPeak)); // Power Factor uses highest of peak or off-peak
    kv_charge = Kilovar * 56.07;
    base_tariff = base + service_charge + unit_price + kv_charge;
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("6.2 Time of Use Tariff (TOU Tariff)\n\n"); 
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate special business normal rate (5.1)
void specialBusinessNormalRate(){
    double Ft, rateOn, Kilovar, kv_charge, unit, unit_price, NeedOnHighestRate, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    getInput("Maximum electricity demand (kilowatts): ", &NeedOnHighestRate);
    getInput("Reactive power demand (kilovars): ", &NeedReactive);
    getInput("User's electricity usage (units): ", &unit);
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
    base = HighestRate * NeedOnHighestRate; // Demand cost
    unit_price = unit * rateOn; // Unit cost
    Kilovar = KVCharge(NeedReactive, NeedOnHighestRate);
    kv_charge = Kilovar * 56.07;
    base_tariff = base + service_charge + unit_price + kv_charge;
    ft_charge = unit * Ft;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + ft_charge + vat_charge;
    system("cls");
    printf("5.1 Normal Rate\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate special business TOU rate (5.2)
void specialBusinessTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, Kilovar, kv_charge, unit_price, HighestRate, NeedReactive, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 69 kilovolts and above\n(2) Voltage 22 - 33 kilovolts\n(3) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 3);
    getInput("Electricity demand during On Peak (kilowatts): ", &NeedOnPeak);
    getInput("Electricity demand during Off Peak (kilowatts): ", &NeedOffPeak);
    getInput("Electricity demand during Holiday (kilowatts): ", &NeedHoliday);
    getInput("Electricity usage during On Peak (units): ", &onPeak);
    getInput("Electricity usage during Off Peak (units): ", &offPeak);
    getInput("Electricity usage during Holiday (units): ", &holiday);
    getInput("Reactive power demand (kilovars): ", &NeedReactive);
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
    printf("5.2 Time of Use Tariff (TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Calculate agriculture water pumping TOU rate (7.2)
void agricultureWaterPumpingTOURate(){
    double Ft, NeedOnPeak, NeedOffPeak, NeedHoliday, rateOn, rateOff, HighestRate, cost, base_tariff, ft_charge, vat_charge, service_charge, onPeak, offPeak, holiday, base = 0;
    int choice;
    Ft = getFt(0);
    system("cls");
    printf("(1) Voltage 22 - 33 kilovolts\n(2) Voltage below 22 kilovolts\n");
    getOption("Select voltage type: ", &choice, 2);
    getInput("Electricity demand during On Peak (kilowatts): ", &NeedOnPeak);
    getInput("Electricity demand during Off Peak (kilowatts): ", &NeedOffPeak);
    getInput("Electricity demand during Holiday (kilowatts): ", &NeedHoliday);
    getInput("Electricity usage during On Peak (units): ", &onPeak);
    getInput("Electricity usage during Off Peak (units): ", &offPeak);
    getInput("Electricity usage during Holiday (units): ", &holiday);
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
    base += (NeedOnPeak * HighestRate); // Demand cost
    base += (onPeak * rateOn) + (offPeak * rateOff) + (holiday * rateOff); // Units cost by time
    ft_charge = (onPeak + offPeak + holiday) * Ft;
    base_tariff = base + service_charge;
    vat_charge = (base_tariff + ft_charge) * VAT;
    cost = base_tariff + vat_charge + ft_charge;
    system("cls");
    printf("7.2 Time of Use Tariff (TOU Tariff)\n\n");
    displayBill(base, service_charge, base_tariff, ft_charge, vat_charge, cost);
}

// Main menu to select electricity type
void menu(){
    int choice;
    system("cls");
    printf("Electricity Types\n");
    printf("(1) 1.1 Residential (Normal Rate)\n"); 
    printf("(2) 1.2 Residential (TOU Rate)\n"); 
    printf("(3) 2.1 Small Business (Normal Rate)\n"); 
    printf("(4) 2.2 Small Business (TOU Rate)\n"); 
    printf("(5) 3.1 Medium Business\n");
    printf("(6) 3.2 Medium Business (TOU Rate)\n");
    printf("(7) 4.1 Large Business (TOD Rate)\n");
    printf("(8) 4.2 Large Business (TOU Rate)\n");
    printf("(9) 5.1 Specific Business (Normal Rate)\n");
    printf("(10) 5.2 Specific Business (TOU Rate)\n");
    printf("(11) 6.1 Non-Profit Organization\n");
    printf("(12) 6.2 Non-Profit Organization (TOU Rate)\n");
    printf("(13) 7.1 Agriculture Water Pumping\n");
    printf("(14) 7.2 Agriculture Water Pumping (TOU Rate)\n");
    printf("(15) 8. Temporary Electricity\n");
    getOption("Select electricity type (1 - 15): ", &choice, 15);
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

// Main function, loops the menu
int main(){
    setlocale(LC_NUMERIC, "");

    while(1){ // Infinite loop, press Ctrl+C to exit
        system("cls");
        menu();
        printf("\nPress Enter to continue...(Press Ctrl + C to exit)");
        getchar(); // Wait for Enter to restart
    }
    return 0;
}
