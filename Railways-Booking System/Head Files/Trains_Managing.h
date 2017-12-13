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
	unsigned seat_left;
	unsigned seat_amount;
	double seat_price;

public :
	Box(const std::string& seat_type,
		const unsigned& number,
		const unsigned& seat_left,
		const unsigned& seat_amount,
		const double& seat_price);
	
//private :
//	std::string train_number;
};
class Seat
{
public :
	std::string type;
	unsigned seat_left;
	double price;

public :
	Seat(const std::string& type, const unsigned& seat_left, const double& price);
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
	std::vector<Seat> seats;
	std::string boxes_file;
	//std::list<Station> way_stations;
public :
	Train(const std::string& number,
		  const std::string& departure_station,
		  const std::string& terminal_station,
	      const std::string& departure_time,
		  const std::string& terminal_time,
		  const std::string& boxes_file);
	Seat* find_seat_type(const std::string& seat_type);
	Box* find_box(const std::string& seat_type);
	Box* find_box(const unsigned& box_number);
private :
	std::fstream boxes_data;
private :
	void read_in();


};
class Ticket
{
public:
	std::string passenger_name;
	std::string train_number;
	std::string departure_station;
	std::string terminal_station;
	std::string departure_time;
	std::string terminal_time;
	std::string box_number;
	std::string seat_number;
	std::string seat_type;
	std::string seat_price;

public :
	Ticket(
	const std::string passenger_name,
	const std::string train_number,
	const std::string departure_station,
	const std::string terminal_station,
	const std::string departure_time,
	const std::string terminal_time,
	const std::string box_number,
	const std::string seat_number,
	const std::string seat_type,
	const std::string seat_price
	);
};
class Trains
{
public:
	std::vector<Train> trains;
	std::string trains_file;
public:
	Trains(const std::string& trains_file);
	Train* find_train(const std::string& train_number);
	void add_seat(const Ticket& ticket);
private:

	std::fstream trains_data;
private:
	void read_in();
};
#endif // Trains_Managing
