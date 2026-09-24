# Parking Management System (ParkingSys)

## Overview

ParkingSys is a desktop-based parking management system developed in C++ using Qt 6 and CMake. The application provides an intuitive graphical interface to manage customer registrations, visual parking slot allocations, floor configurations, check-in timestamps, duration tracking, vehicle checkouts with tiered charge calculation, and custom tariff management.

---

## Architecture and Design

The project is structured with a clean separation of concerns:
- **Core Business Logic and Data Structures:** Managed in standard C++ structures (`Customer`, `ParkingLot`, `Floor`, `RateTier`, and the `Structures` controller class) independently of the GUI.
- **User Interface:** Developed using Qt Designer form definitions (`.ui`) and driven by Qt's signal-and-slot mechanism.
- **Intuitive Starting Dashboard:** Features a live status banner detailing total floors, total capacity, available spots, and currently occupied slots.
- **UI Synthesis / Subproject Workflow:** The `Window/` directory contains the base UI synthesis and class scaffolding, while the primary project under the root directory orchestrates the complete integrated build.

---

## Features

- **Intuitive Starting Menu Dashboard:**
  - Real-time status display tracking total floors, total capacity, parked vehicles, and available spots.
  - Centered navigation buttons for spot reservation, vehicle checkout, floor/lot management, and tariff rates.
  - Top menu bar for quick access to management tools and application controls.
- **Dynamic Interactive Slot Grid with Multi-Floor Support:** 
  - Dynamic visual grid representation of parking bays on each floor.
  - Floor selection switcher allowing seamless navigation across multiple floors.
  - Real-time color-coded availability:
    - Green for available slots.
    - Red for occupied slots, displaying the occupying vehicle registration number.
    - Blue highlight for currently selected slot.
- **Floor and Parking Lot Management Menu:**
  - View real-time capacity and occupancy metrics for every floor.
  - Add new floors dynamically with custom initial spot counts.
  - Remove empty top floors safely.
  - Add extra parking lots to any floor on demand.
  - Remove unassigned spots from floors without affecting occupied vehicles.
- **Tariff & Rate Tier Management Section:**
  - View all active pricing tiers with their duration bounds and KES rates.
  - Edit charges for any tier directly from the UI.
  - Add new custom pricing tiers with custom duration limits (hours/minutes) and fees.
  - Configure the overtime fee for stays exceeding all defined tiers.
- **Occupant Details on Demand:** Clicking any occupied spot displays the vehicle details and registration.
- **Integrated Customer Registration with Phone Number:** Prompts for First Name, Second Name, Vehicle Registration, National ID, and Phone Number when reserving a spot.
- **Automated Check-in Timestamping:** Accurately logs the entry time in seconds using `std::chrono::system_clock`.
- **Vehicle Exit and Checkout:**
  - Multi-floor vehicle lookup displaying floor and spot location for all parked cars.
  - Computes natural duration breakdown (hours, minutes, seconds).
  - Outputs checkout receipt with charges calculated in KES according to the active rate tiers.
  - Automatically vacates and resets the slot back to available.

---

## Project Structure

```text
ParkingSys/
├── CMakeLists.txt              # Root build configuration
├── include/                    # Public C++ header files
│   ├── mainwindow.h            # Main application window class
│   ├── main.hpp                # Global headers and formatting
│   ├── structures.hpp          # Core data structures, rate tiers, and parking logic
│   └── window_mgmt.hpp         # Auxiliary window management utilities
├── src/                        # C++ source files
│   ├── main.cpp                # Application entry point
│   └── mainwindow.cpp          # Window logic and event handlers
├── ui/                         # Qt Designer UI XML files
│   ├── CustomerInfo.ui         # Customer and vehicle registration dialog (includes phone)
│   ├── mainwindow.ui           # Starting dashboard layout with management buttons
│   └── ReserveParking.ui       # Parking space grid dialog
├── Window/                     # Standalone UI synthesis project
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── mainwindow.h
│   ├── mainwindow.cpp
│   ├── mainwindow.ui
│   ├── CustomerInfo.ui
│   └── ReserveParking.ui
└── docs/                       # Project documentation
    ├── DataStructures.md
    └── Overview.md
```

---

## Prerequisites and Dependencies

- **Compiler:** C++20 compliant compiler (GCC 11+, Clang 13+, or MSVC 2019+)
- **Build System:** CMake (version 3.16 or higher)
- **Framework:** Qt 6 (Components: `Qt6::Widgets`)
- **Make/Ninja:** Build tools (e.g., `make`, `ninja`)

### Installation of Dependencies (Linux / Ubuntu / Debian)

```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev
```

### Installation of Dependencies (Arch Linux)

```bash
sudo pacman -S base-devel cmake qt6-base qt6-tools
```

---

## Build Instructions

### 1. Build the Unified Project (Root)

From the root project directory:

```bash
cmake -B build -S .
cmake --build build -j$(nproc)
```

The resulting executable will be located at:
```bash
./build/ParkingSys
```

### 2. Build the Window Subproject

If compiling the standalone UI module independently:

```bash
cmake -B Window/build -S Window
cmake --build Window/build -j$(nproc)
```

The resulting executable will be located at:
```bash
./Window/build/Window
```

---

## Usage Guide
### On lINux
do like this
1. **Launch the Application:**
   ```bash
   ./build/ParkingSys
   ```

2. **Starting Menu Dashboard:**
   - The main window displays the system header, a live capacity status banner, and four primary control buttons.

3. **Reserve a Parking Spot:**
   - Click the centered **Reserve Spot** button.
   - Use the Floor dropdown to select the desired floor.
   - The grid will display all parking bays for that floor.
   - Click any green **[ FREE ]** slot (it highlights in blue).
   - Click **OK**.
   - If customer details have not been entered yet, the **Customer Details** dialog prompts for First Name, Second Name, Vehicle Registration, National ID, and Phone Number.
   - The slot is committed and turns red with the vehicle registration number.

4. **Inspect Occupied Slots:**
   - Click on any red slot in the parking grid to view the vehicle registration number.

5. **Exit / Checkout a Vehicle:**
   - From the main window, click **Exit / Checkout**.
   - Select the parked vehicle from the multi-floor list.
   - The system calculates natural duration (hours, minutes, seconds) and total charges in KES based on the configured rate tiers, shows the receipt dialog, and frees the spot.

6. **Manage Floors & Parking Lots:**
   - Click **Manage Floors & Lots** on the main menu or via the Manage menu bar.
   - View floor capacities, add new floors, remove empty floors, or add/remove parking bays per floor.

7. **Configure Tariff & Rates:**
   - Click **Tariff & Rates Settings** on the main menu.
   - Review current rate tiers, edit existing rates in KES, add new pricing tiers with custom duration limits, or adjust the overtime charge.

### On windows
build using cmake (as per the command preferrably use powershell)
ensure to create the build folders in both root and Window
and build Window first to avoid missing header files for the main build

---

## Core Data Structures

### `Customer`
Stores personal identification, contact details (including phone number), vehicle registration, and check-in timestamp:
- `Id` (`unsigned long`): Unique customer identifier.
- `FirstName` (`std::string`): Customer first name.
- `SecondName` (`std::string`): Customer second name.
- `IdNumber` (`std::string`): National ID number.
- `PhoneNumber` (`std::string`): Customer phone contact.
- `CheckInTime` (`unsigned long`): Unix epoch entry timestamp in seconds.

### `ParkingLot`
Represents an individual parking slot:
- `occupied` (`bool`): Slot occupancy status.
- `OVehicleReg` (`std::string`): Occupant's vehicle registration number.
- `OccupantID` (`unsigned long`): Foreign identifier linking to `Customer::Id`.
- `CheckInTime` (`unsigned long`): Unix epoch timestamp (seconds) recorded at entry.

### `Floor`
Represents a floor containing a dynamic `std::vector<ParkingLot>` collection allowing spots to be expanded or reduced dynamically.

### `RateTier`
Represents a pricing bracket:
- `name` (`std::string`): Tier description or label.
- `maxSeconds` (`unsigned long`): Maximum stay duration in seconds for this tier.
- `charge` (`unsigned long`): Parking fee in KES.

### `Structures`
Controller class managing floors, spots, customers, space reservations, duration querying, dynamic rate tiers, fee calculations, and slot deallocations.

---

## Author

- Name: KIPLANGAT JETHRO
- Course: COMPUTER SCIENCE 

---
## TOOLS USED IN DEV

- QT Creator to visually build the user interface and generaet the Classes for UI all in the Window FOlder
- Developed On  linux however cross compatibilty with windows is ensured by the CMakelists.txt in the root folder and Window dir

## License

This project is submitted as an academic assignment. All rights reserved.
