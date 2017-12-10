#ifndef Trains_Managing
#define Trains_Managing

#include"Tools.h"

#include<string>
#include<list>
#include<vector>
#include<iostream>
#include<fstream>
#include<iterator>
#include<conio.h>

class Station
{
public :
	std::string name;
	std::string arrival_time;
	std::string departure_time;
	std::string stay_time;

public :
	Station(const std::string& name, 
			const std::string& arrival_time, 
			const std::string& departure_time, 
			const std::string& stay_time);
};
class Box
{
public:
	// hard_seat, berth, cushioned_berth
	std::string seat_type;
	unsigned number;
	unsigned seat_account;
	double seat_price;

public :
	Box(const std::string& seat_type,
		const unsigned& number,
		const unsigned& seat_account,
		const double& seat_price);
	
private :
	std::string train_number;
};
class Seats
{
public :
	std::string type;
	unsigned seat_left;
	double price;

public :
	Seats(const std::string& type, const unsigned& seat_left, const double& price);
};
class Train
{
public :
	std::string number;
	std::string departure_station;
	std::string terminal_station;
	std::string departure_time;
	std::string terminal_time;
	std::list<Box> boxes;
	std::vector<Seats> seats;
	//std::list<Station> way_stations;
public :
	Train(const std::string& number,
		  const std::string& departure_station,
		  const std::string& terminal_station,
	      const std::string& departure_time,
		  const std::string& terminal_time,
		  const std::string& boxes_file);
	//unsigned sum_seat(const std::string& seat_type);
private :
	std::string boxes_file;
	std::fstream boxes_data;
private :
	void read_in();


};
class Trains
{
public :
	std::vector<Train> trains;
public :
	Trains(const std::string& trains_file);
private :
	std::string trains_file;	
	std::fstream trains_data;
private :
	void read_in();
};
class Ticket
{
public:
	std::string train_number;
	std::string departure_station;
	std::string terminal_station;
	std::string departure_time;
	std::string terminal_time;
	std::string seat_type;
	std::string seat_price;
	std::string passenger_name;

};
#endif // Trains_Managing
