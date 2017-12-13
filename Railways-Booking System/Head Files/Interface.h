#ifndef Interfaces
#define Interfaces

#include"Tools.h"
#include"Users_Managing.h"
#include"Trains_Managing.h"

#include<iostream>
#include<iomanip>
#include<List>


class Interface
{
public:
	Interface() = default;
	void welcomeIF() const;
	void passengerIF(const std::string passenger_name) const;
	void managerIF(const std::string manager_name) const;
	void trainsIF(const std::list<const Train*>& suited_trains) const;
	void ordersIF(const std::list<Order>& orders) const;
	void info_of_passengersIF(const std::vector<Passenger>& passengers) const;
};



#endif // Interfaces
