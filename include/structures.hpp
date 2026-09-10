#pragma once
enum OPERATION
{
    ADD=0
    REMOVE
    MODIFY
}
struct Customer
{
    unsigned long Id;
    char *name;
    char *IdNumber;
    unsigned long CheckInTime;
};
struct ParkingLot
{
    char *Floor;
    unsigned long Id;

}
class structures
{
public:
    structures() {}
    ~structures() {}
    int SetFloors(unsigned long count, OPERATION op)
    {
        if (op = ADD)
        {
            this->Floors+=count;
        }
        if (op = REMOVE)
        {
            if (count > this->Floors)
            {
                reuturn -1;
                
            }
            else if (count <= this->Floors)
            {
                this->Floors-=count;
            }
        }
        return 0;
    }
    int AddCustomer
private:
    Customer customer;
    unsigned long CustomerCount = 0;
    unsigned long Floors = 0;
    unsigned long TotalSpaces = 0;
    
    

};

