//THis code was written by human
//That statementsmakes it more sus but well
//haha
//
#pragma once
#include <chrono>
#include <vector>
enum OPERATION
{
    ADD=0,
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
    unsigned long OccupantID;
    

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
        this->customer[CustomerCount + 1].Id = CustomerCount + 1;
        this->customer[CustomerCount + 1].FirstName = Firstname;
        this->customer[CustomerCount + 1].SecondName = SecondName;
        this->customer[CustomerCount + 1].IdNumber = IdNum;
        this->customer[CustomerCount + 1].CheckInTime = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());  
        this->CustomerCount += 1;      
        return 0;
    }
    int SelectSpace(unsigned long CustomerID_, unsigned long Floor_, unsigned long ParkingSpot)
    {
        if (!(this->floors[Floor_ + 1].parkinglots[ParkingSpot].occupied))
        {
            this->floors[Floor_ + 1].parkinglots[ParkingSpot].occupied = true;
            this->floors[Floor_ + 1].parkinglots[ParkingSpot].OccupantID = CustomerID_;

        }   
    else if (this->floors[Floor_ + 1].parkinglots[ParkingSpot].occupied) 
    {
        return -1;
    }
    return 0;
    }
    Customer GetCustomer(unsigned long CustomerID_)
    {
        return this->customer[CustomerID_];
    }
    Floor GetFloors(unsigned long FloorID_)
    {
        return this->floors[FloorID_];
    }

private:
    unsigned long NoOfFloors = 3; // This includes the groundfloor so 1 means just the groundfloor and is default 
    Customer customer[100]; // hardcoded instances of customers .. will come back to correct this later
    std::vector<Floor> floors;
    unsigned long CustomerCount = 0;
};

