//THis code was written by human
//That statementsmakes it more sus but well
//haha
//
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

// Customer info struct with phonenumber added as requested
struct Customer
{
    unsigned long Id;
    std::string FirstName;
    std::string SecondName;
    std::string IdNumber;
    std::string PhoneNumber; // phonenumber field for customeer contact
    unsigned long CheckInTime;
};

// Parking lot struct to track if spot is occupied or free
struct ParkingLot
{
    bool occupied = false;
    std::string OVehicleReg;
    unsigned long OccupantID = 0;
    unsigned long CheckInTime = 0;
};

// Floor struct now holds a dynamic vector of parkng lots so we can add more spots later
struct Floor
{
    std::vector<ParkingLot> parkinglots;
    Floor(size_t spotCount = 12)
    {
        parkinglots.resize(spotCount);
    }
};

// Rate tier struct for the chareges logic so we can edit rates and add new tiers
struct RateTier
{
    std::string name; // eg "under 30 mins" or "2 to 4 hrs"
    unsigned long maxSeconds; // max duratin in seconds for this tier
    unsigned long charge; // amnt in KES
};

class Structures
{
public:
    Structures() 
    {
        floors.resize(this->NoOfFloors);
        // default rate tiers initialised here like in my earlier code
        rateTiers.push_back({"Free tier (<= 30 mins)", 30 * 60, 0});
        rateTiers.push_back({"Short stay (30 mins to 2 hrs)", 2 * 60 * 60, 50});
        rateTiers.push_back({"Medium stay (2 hrs to 4 hrs)", 4 * 60 * 60, 100});
        rateTiers.push_back({"Long stay (4 hrs to 6 hrs)", 6 * 60 * 60, 300});
    }
    ~Structures() {}

    // Method to set or add floors 
    int SetFloors(unsigned long count, OPERATION op)
    {
        if (op == ADD)
        {
            this->NoOfFloors += count;
            this->floors.resize(this->NoOfFloors);
        }
        if (op == REMOVE)
        {
            if (count > this->NoOfFloors)
            {
                return -1; // cant remove more floors than we actually hav
            }
            else if (count <= this->NoOfFloors)
            {
                this->NoOfFloors -= count;
                this->floors.resize(this->NoOfFloors);
            }
        }
        return 0;
    }

    // convenient methd to add a single floor with default spots
    int AddFloor(unsigned long defaultSpots = 12)
    {
        this->NoOfFloors += 1;
        this->floors.push_back(Floor(defaultSpots));
        return static_cast<int>(this->floors.size());
    }

    // methd to remove top floor if empty
    int RemoveFloor()
    {
        if (this->floors.size() <= 1)
        {
            return -1; // keep atleast 1 floor groundfloor
        }
        // check if any spot is occupied on teh top floor before deletign
        const auto &topFloor = this->floors.back();
        for (const auto &spot : topFloor.parkinglots)
        {
            if (spot.occupied)
            {
                return -2; // cant delete floor with car parked
            }
        }
        this->floors.pop_back();
        this->NoOfFloors = this->floors.size();
        return 0;
    }

    // Method to add more parkng lots to a specific floor as requested
    int AddParkingLots(unsigned long Floor_, unsigned long count = 1)
    {
        if (Floor_ >= this->floors.size())
        {
            return -1;
        }
        for (unsigned long i = 0; i < count; ++i)
        {
            this->floors[Floor_].parkinglots.push_back(ParkingLot());
        }
        return static_cast<int>(this->floors[Floor_].parkinglots.size());
    }

    // Methd to remove last parking spot from a floor if it is not occupied
    int RemoveParkingLot(unsigned long Floor_)
    {
        if (Floor_ >= this->floors.size() || this->floors[Floor_].parkinglots.empty())
        {
            return -1;
        }
        if (this->floors[Floor_].parkinglots.back().occupied)
        {
            return -2; // cant remove occupied spot
        }
        this->floors[Floor_].parkinglots.pop_back();
        return static_cast<int>(this->floors[Floor_].parkinglots.size());
    }

    unsigned long GetFloorCount() const
    {
        return this->floors.size();
    }

    unsigned long GetSpotCount(unsigned long Floor_) const
    {
        if (Floor_ >= this->floors.size()) return 0;
        return this->floors[Floor_].parkinglots.size();
    }

    // Add customer with phonenumber support
    int AddCustomer(std::string Firstname, std::string SecondName, std::string IdNum, std::string PhoneNum = "")
    {
        this->customer[CustomerCount].Id = CustomerCount + 1;
        this->customer[CustomerCount].FirstName = Firstname;
        this->customer[CustomerCount].SecondName = SecondName;
        this->customer[CustomerCount].IdNumber = IdNum;
        this->customer[CustomerCount].PhoneNumber = PhoneNum;
        this->customer[CustomerCount].CheckInTime = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());  
        this->CustomerCount += 1;      
        return this->CustomerCount - 1;
    }

    // Select space and reserve it for a vehicle
    int SelectSpace(std::string RegNo, unsigned long Floor_, unsigned long ParkingSpot, unsigned long custId = 0)
    {
        if (Floor_ >= this->floors.size() || ParkingSpot >= this->floors[Floor_].parkinglots.size())
        {
            return -1; // spot or floor out of bounds
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

    // calculates duration in seconds from checkintime to currnt time
    unsigned long CalculateDuration(unsigned long checkInTime)
    {
        unsigned long now = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
        if (now > checkInTime)
        {
            return now - checkInTime;
        }
        return 0; // incase clock drift happens
    }

    unsigned long GetDuration(unsigned long checkInTime)
    {
        return CalculateDuration(checkInTime);
    }

    // Formats duration into natural hours and minutes and secnds
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

    // Rates section: get rate tiers vector to display in UI or loop through
    std::vector<RateTier>& GetRateTiers()
    {
        return this->rateTiers;
    }

    const std::vector<RateTier>& GetRateTiers() const
    {
        return this->rateTiers;
    }

    // Seciton for changing the rates of any tier
    bool UpdateRateTier(size_t index, unsigned long newRate, unsigned long newMaxSeconds = 0)
    {
        if (index >= this->rateTiers.size())
        {
            return false;
        }
        this->rateTiers[index].charge = newRate;
        if (newMaxSeconds > 0)
        {
            this->rateTiers[index].maxSeconds = newMaxSeconds;
        }
        return true;
    }

    // Method for addign new tiers as requested
    void AddRateTier(std::string name, unsigned long maxSeconds, unsigned long charge)
    {
        RateTier newTier;
        newTier.name = name;
        newTier.maxSeconds = maxSeconds;
        newTier.charge = charge;
        this->rateTiers.push_back(newTier);
    }

    void SetMaxOvertimeCharge(unsigned long charge)
    {
        this->maxOvertimeCharge = charge;
    }

    unsigned long GetMaxOvertimeCharge() const
    {
        return this->maxOvertimeCharge;
    }

    // Calcualtes charges based on the configured rate tiers
    unsigned long CalculateCharges(unsigned long checkInTime)
    {
        unsigned long total_stay_time = CalculateDuration(checkInTime);
        for (const auto &tier : this->rateTiers)
        {
            if (total_stay_time <= tier.maxSeconds)
            {
                return tier.charge;
            }
        }
        // if stay is more than all the tiers then return max overtime charge
        return this->maxOvertimeCharge;
    }

    int FreeSpace(unsigned long Floor_, unsigned long ParkingSpot)
    {
        if (Floor_ >= this->floors.size() || ParkingSpot >= this->floors[Floor_].parkinglots.size())
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
    unsigned long NoOfFloors = 3; // default number of floors
    Customer customer[100]; // static array for customers
    std::vector<Floor> floors; // dynamic vector for floors
    unsigned long CustomerCount = 0;
    std::vector<RateTier> rateTiers; // vector of rate tiers for pricing calcualtion
    unsigned long maxOvertimeCharge = 500; // charge if stay surpasses all tiers
};
