#ifndef Interfaces
#define Interfaces

#include"Tools.h"
#include"Trains_Managing.h"

#include<iostream>
#include<iomanip>
#include<List>


class Interface
{
public:
	Interface() = default;
	void welcomeIF() const;
	void passengerIF() const;
	void managerIF() const;
	void trainsIF(std::list<const Train*> suited_trains) const;
	//void trainsIF() const;
};



#endif // Interfaces
