#pragma once
#include <chrono>
#include <vector>
#include <string>

enum OPERATION
{
    ADD = 0,
    REMOVE,
    MODIFY
};

struct Customer
{
    unsigned long Id;
    std::string FirstName;
    std::string SecondName;
    std::string IdNumber;
    unsigned long CheckInTime;
};

struct ParkingLot
{
    bool occupied = false;
    std::string OVehicleReg;
    unsigned long OccupantID = 0;
    unsigned long CheckInTime = 0;
};

struct Floor
{
    ParkingLot parkinglots[12];
};

class Structures
{
public:
    Structures() 
    {
        floors.resize(this->NoOfFloors);
    }
    ~Structures() {}

    int SetFloors(unsigned long count, OPERATION op)
    {
        if (op == ADD)
        {
            this->NoOfFloors += count;
        }
        if (op == REMOVE)
        {
            if (count > this->NoOfFloors)
            {
                return -1;
            }
            else if (count <= this->NoOfFloors)
            {
                this->NoOfFloors -= count;
            }
        }
        return 0;
    }

    int AddCustomer(std::string Firstname, std::string SecondName, std::string IdNum)
    {
        this->customer[CustomerCount].Id = CustomerCount + 1;
        this->customer[CustomerCount].FirstName = Firstname;
        this->customer[CustomerCount].SecondName = SecondName;
        this->customer[CustomerCount].IdNumber = IdNum;
        this->customer[CustomerCount].CheckInTime = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());  
        this->CustomerCount += 1;      
        return this->CustomerCount - 1;
    }

    int SelectSpace(std::string RegNo, unsigned long Floor_, unsigned long ParkingSpot, unsigned long custId = 0)
    {
        if (Floor_ >= this->floors.size() || ParkingSpot >= 12)
        {
            return -1;
        }
        if (!(this->floors[Floor_].parkinglots[ParkingSpot].occupied))
        {
            this->floors[Floor_].parkinglots[ParkingSpot].occupied = true;
            this->floors[Floor_].parkinglots[ParkingSpot].OVehicleReg = RegNo;
            this->floors[Floor_].parkinglots[ParkingSpot].OccupantID = custId;
            this->floors[Floor_].parkinglots[ParkingSpot].CheckInTime = static_cast<unsigned long>(
                std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count());
        }   
        else
        {
            return -1;
        }
        return 0;
    }

    unsigned long CalculateDuration(unsigned long checkInTime)
    {
        unsigned long now = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
        if (now > checkInTime)
        {
            return now - checkInTime;
        }
        return 0;
    }

    unsigned long GetDuration(unsigned long checkInTime)
    {
        return CalculateDuration(checkInTime);
    }

    std::string FormatDuration(unsigned long total_stay_time)
    {
        unsigned long hours = total_stay_time / (60 * 60);
        unsigned long minutes = (total_stay_time % (60 * 60)) / 60;
        unsigned long seconds = total_stay_time % 60;

        std::string result;
        if (hours > 0)
        {
            result += std::to_string(hours) + (hours == 1 ? " hour" : " hours");
        }
        if (minutes > 0)
        {
            if (!result.empty())
            {
                result += " ";
            }
            result += std::to_string(minutes) + (minutes == 1 ? " minute" : " minutes");
        }
        if (seconds > 0 || result.empty())
        {
            if (!result.empty())
            {
                result += " ";
            }
            result += std::to_string(seconds) + (seconds == 1 ? " second" : " seconds");
        }
        return result;
    }

    std::string GetDurationNatural(unsigned long checkInTime)
    {
        return FormatDuration(CalculateDuration(checkInTime));
    }

    unsigned long CalculateCharges(unsigned long checkInTime)
    {
        unsigned long total_stay_time = CalculateDuration(checkInTime);
        if (total_stay_time <= (30 * 60))
        {
            return 0;
        }
        if ((total_stay_time > (30 * 60)) && (total_stay_time <= (2 * 60 * 60)))
        {
            return 50;
        }
        if ((total_stay_time > (2 * 60 * 60)) && (total_stay_time <= (4 * 60 * 60)))
        {
            return 100;
        }
        if ((total_stay_time > (4 * 60 * 60)) && (total_stay_time <= (6 * 60 * 60)))
        {
            return 300;
        }
        else 
        {
            return 500;
        }
        return 0;
    }

    int FreeSpace(unsigned long Floor_, unsigned long ParkingSpot)
    {
        if (Floor_ >= this->floors.size() || ParkingSpot >= 12)
        {
            return -1;
        }
        this->floors[Floor_].parkinglots[ParkingSpot].occupied = false;
        this->floors[Floor_].parkinglots[ParkingSpot].OVehicleReg = "";
        this->floors[Floor_].parkinglots[ParkingSpot].OccupantID = 0;
        this->floors[Floor_].parkinglots[ParkingSpot].CheckInTime = 0;
        return 0;
    }

    Customer GetCustomer(unsigned long CustomerID_)
    {
        return this->customer[CustomerID_];
    }

    Floor GetFloors(unsigned long FloorID_)
    {
        if (FloorID_ >= this->floors.size())
        {
            return Floor();
        }
        return this->floors[FloorID_];
    }

private:
    unsigned long NoOfFloors = 3;
    Customer customer[100];
    std::vector<Floor> floors;
    unsigned long CustomerCount = 0;
};
