# PEA Electricity Bill Calculator

![C Language](https://img.shields.io/badge/Language-C-blue.svg)  
![License](https://img.shields.io/badge/License-MIT-green.svg)  
![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)

## Overview

This project is a **mini-project for a university assignment**, designed to calculate electricity bills based on the tariff structures provided by the **Provincial Electricity Authority (PEA)** of Thailand. The program is written in **C** and uses data from the years **2566–2568 (2023–2025)**, sourced from the official PEA estimation tool at [https://eservice.pea.co.th/EstimateBill/](https://eservice.pea.co.th/EstimateBill/). It supports various electricity consumer types, including residential, business, non-profit, agricultural, and temporary usage, with both normal and Time of Use (TOU) tariff options.

The calculator takes user inputs such as electricity usage (in units), voltage type, demand (in kilowatts or kilovars where applicable), and billing month/year to compute the total cost, including base tariff, service charge, Ft (Fuel Adjustment) rate, and VAT (Value Added Tax).

## Features

- **Multiple Consumer Types**: Supports 15 different electricity tariff categories (e.g., Residential Normal Rate, Large Business TOU Rate, Agriculture Water Pumping, etc.).
- **Flexible Input Validation**: Ensures robust input handling with checks for valid numeric values and options.
- **Time-Based Tariffs**: Implements TOU (Time of Use) and TOD (Time of Day) rates with peak, off-peak, and holiday usage.
- **Power Factor Calculation**: Includes power factor charges for medium and large business consumers.
- **Detailed Bill Breakdown**: Displays a structured bill with sections for base cost, Ft charge, and VAT.
- **Dynamic Ft Rates**: Adjusts Ft rates based on the selected month and year (2566–2568).
- **Localized Formatting**: Uses Thai Baht currency formatting for readability.

## Tariff Categories

1. **Residential (1.1 Normal, 1.2 TOU)**  
2. **Small Business (2.1 Normal, 2.2 TOU)**  
3. **Medium Business (3.1 Normal, 3.2 TOU)**  
4. **Large Business (4.1 TOD, 4.2 TOU)**  
5. **Specific Business (5.1 Normal, 5.2 TOU)**  
6. **Non-Profit Organization (6.1 Normal, 6.2 TOU)**  
7. **Agriculture Water Pumping (7.1 Normal, 7.2 TOU)**  
8. **Temporary Electricity (8)**  

## Prerequisites

- **C Compiler**: GCC or any compatible C compiler (e.g., MinGW-w64 for Windows, Clang for macOS/Linux).
- **Operating System**: Works on Windows, Linux, or macOS with a terminal/console.
- **Windows Users**:
  - Must use **MinGW-w64** (MSYS2 recommended) for compilation.
  - Install MinGW-w64 via MSYS2:  
    ```sh
    pacman -S mingw-w64-x86_64-gcc
    ```

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/DoubleP987/PEA_bill.git
   ```
2. Navigate to the project directory:
   ```bash
   cd PEA_bill
   ```
3. Compile the code:
   ```bash
   gcc -o PEA_bill main.c -lm
   ```
4. Run the program:
   ```bash
   ./PEA_bill
   ```

## Usage

1. Launch the program, and the main menu will display the available electricity tariff types (1–15).
2. Select a tariff type by entering a number between 1 and 15.
3. Follow the prompts to input required details (e.g., electricity usage in units, voltage type, month/year).
4. The program will calculate and display a detailed electricity bill.
5. Press Enter to return to the menu or Ctrl+C to exit.

## Electricity Types

```
(1) 1.1 Residential (Normal Rate)
(2) 1.2 Residential (TOU Rate)
...
Select electricity type (1 - 15): 1
Select electricity type: 1
User's electricity usage (units): 120
Select month: 3
Year: 2568
```

```
1.1.1 Normal Rate, Usage not exceeding 150 units per month

	Section 1: Base Electricity Cost
		Electricity Usage Cost            382.51 Baht
		Service Charge                      8.19 Baht
		Total Base Electricity Cost       390.70 Baht
	Section 2: Variable Electricity Cost (Ft)
		Units x Ft Rate                   44.06 Baht
	Section 3: 7% Value Added Tax
		(Base Cost + Ft) x 7/100          30.35 Baht
	Total Electricity Cost              465.11 Baht
```

## Data Source

The tariff rates, Ft values, and calculation logic are based on official data from the Provincial Electricity Authority (PEA) for the years 2566–2568, as provided on [PEA's official website](https://eservice.pea.co.th/EstimateBill/). Rates may vary beyond 2568 and should be updated accordingly.

## Limitations

- The program assumes static rates for 2566–2568 and does not account for future rate changes.
- No graphical user interface (GUI); it runs solely in the terminal.
- Limited to the tariff structures implemented; additional categories require manual coding.

## Contributing

This is a university project and not actively maintained. However, feel free to fork the repository and submit pull requests if you’d like to enhance it! Suggestions for improvements are welcome.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

- **Provincial Electricity Authority (PEA)** for providing the tariff data.
- **University instructors and peers** for guidance and feedback during development.

### Repository Link
[GitHub Repository](https://github.com/DoubleP987/PEA_bill)

---

Developed by **DoubleP987** as a university mini-project.

