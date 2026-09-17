# Parking Management System (ParkingSys)

## Overview

ParkingSys is a desktop-based parking management system developed in C++ using Qt 6 and CMake. The application provides an interactive graphical interface to manage customer registrations, visual parking slot allocations, check-in timestamps, duration tracking, and vehicle checkouts with charge calculation.

---

## Architecture and Design

The project is structured with a clean separation of concerns:
- **Core Business Logic and Data Structures:** Managed in standard C++ structures (`Customer`, `ParkingLot`, `Floor`, and the `Structures` controller class) independently of the GUI.
- **User Interface:** Developed using Qt Designer form definitions (`.ui`) and driven by Qt's signal-and-slot mechanism.
- **UI Synthesis / Subproject Workflow:** The `Window/` directory contains the base UI synthesis and class scaffolding, while the primary project under the root directory orchestrates the complete integrated build.

---

## Features

- **Dynamic Interactive Slot Grid:** 
  - Visual 6x2 grid representation of parking bays on each floor.
  - Real-time color-coded availability:
    - Green for available slots.
    - Red for occupied slots, displaying the occupying vehicle registration number.
    - Blue highlight for currently selected slot.
- **Occupant Details on Demand:** Clicking any occupied spot displays the vehicle details and registration.
- **Integrated Customer Registration:** Prompts for First Name, Second Name, Vehicle Registration, and National ID when reserving a spot.
- **Automated Check-in Timestamping:** Accurately logs the entry time in seconds using `std::chrono::system_clock`.
- **Vehicle Exit and Checkout:**
  - Automatically queries all currently parked vehicles.
  - Computes parking duration in seconds.
  - Outputs checkout receipt with charges calculated in KES.
  - Automatically vacates and resets the slot back to available.

---

## Project Structure

```text
ParkingSys/
├── CMakeLists.txt              # Root build configuration
├── include/                    # Public C++ header files
│   ├── mainwindow.h            # Main application window class
│   ├── main.hpp                # Global headers and formatting
│   ├── structures.hpp          # Core data structures and parking logic
│   └── window_mgmt.hpp         # Auxiliary window management utilities
├── src/                        # C++ source files
│   ├── main.cpp                # Application entry point
│   └── mainwindow.cpp          # Window logic and event handlers
├── ui/                         # Qt Designer UI XML files
│   ├── CustomerInfo.ui         # Customer and vehicle registration dialog
│   ├── mainwindow.ui           # Main menu window layout
│   └── ReserveParking.ui       # Parking space 6x2 grid dialog
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

2. **Reserve a Parking Spot:**
   - Click the centered **Reserve Spot** button.
   - The 6x2 grid will display all parking bays.
   - Click any green **[ FREE ]** slot (it will highlight in blue).
   - Click **OK**.
   - If customer information has not been entered yet, the system automatically prompts the **Customer Details** dialog.
   - Fill in First Name, Second Name, Vehicle Registration, and ID Number, then click **OK**.
   - The slot is committed to the backend structures and turns red with the vehicle registration.

3. **Inspect Occupied Slots:**
   - Click on any red slot in the parking grid to view the registration number of the vehicle parked there.

4. **Exit / Checkout a Vehicle:**
   - From the main window, click the **Exit** button.
   - If vehicles are parked, choose the vehicle/spot from the list.
   - The system queries `structures.CalculateCharges()`, calculates the elapsed parking duration, displays total charges in KES, and frees the slot.
### On windows
build using cmake (as per the command preferrably use powershell)
ensure to create the build folders in both root and Window
and build Window first to avoid missing header files for the main build

---

## Core Data Structures

### `Customer`
Stores personal identification, contact details, vehicle registration, and check-in timestamp.

### `ParkingLot`
Represents an individual parking slot:
- `occupied` (`bool`): Slot occupancy status.
- `OVehicleReg` (`std::string`): Occupant's vehicle registration number.
- `OccupantID` (`unsigned long`): Foreign identifier linking to `Customer::Id`.
- `CheckInTime` (`unsigned long`): Unix epoch timestamp (seconds) recorded at entry.

### `Floor`
Represents a floor containing a fixed array of 12 `ParkingLot` units.

### `Structures`
Controller class managing floors, customers, space reservations, duration querying, fee calculations, and slot deallocations.

---

## Roadmap and Future Enhancements

- [ ] Multi-floor selector (Ground Floor, 1st Floor, 2nd Floor).
- [ ] Tiered pricing rate calculation (hourly rates, grace period, penalty rates).
- [ ] SQLite / persistent file storage for historical records.
- [ ] Receipt generation and PDF export.

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
