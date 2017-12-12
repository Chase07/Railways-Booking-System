#include"Trains_Managing.h"

using namespace::std;
/*
 * Public Part
 */
Station::Station(
	const std::string& name, 
	const std::string& arrival_time, 
	const std::string& departure_time, 
	const std::string& stay_time) : 
	name(name), 
	arrival_time(arrival_time), 
	departure_time(departure_time), 
	stay_time(stay_time){}
Box::Box(
	const std::string& seat_type,
	const unsigned& number,
	const unsigned& seat_left,
	const unsigned& seat_amount,
	const double& seat_price) :
	seat_type(seat_type),
	number(number),
	seat_left(seat_left),
	seat_amount(seat_amount),
	seat_price(seat_price) {}
Seat::Seat(const std::string& type,
	const unsigned& seat_left,
	const double& price) : 
	type(type), 
	seat_left(seat_left), 
	price(price){}
Train::Train(
	const std::string& number,
	const std::string& departure_station,
	const std::string& terminal_station,
	const std::string& departure_time,
	const std::string& terminal_time,
	const std::string& boxes_file) :
	number(number),
	departure_station(departure_station),
	terminal_station(terminal_station),
	departure_time(departure_time),
	terminal_time(terminal_time),
	boxes_file(boxes_file){
	read_in();
}
Seat* Train::find_seat_type(const std::string& seat_type)
{
	for (auto& curr_seats : seats)
	{
		if (curr_seats.type == seat_type)
		{ return &curr_seats; }
	}
	return nullptr;
}
Box* Train::find_box(const std::string& seat_type)
{
	for (auto& curr_box : boxes)
	{
		if (curr_box.seat_type == seat_type && curr_box.seat_left != 0) 
		{ return &curr_box; }
	}
	return nullptr;
}
Trains::Trains(const std::string& trains_file) :
	trains_file(trains_file) {
	read_in();
}
Train* Trains::find_train(const std::string& train_number)
{
	for (auto& train : trains)
	{
		if (train.number == train_number) { return &train; }
	}
	return nullptr;
}
Ticket::Ticket(
	const std::string passenger_name,
	const std::string train_number,
	const std::string departure_station,
	const std::string terminal_station,
	const std::string departure_time,
	const std::string terminal_time,
	const std::string box_number,
	const std::string seat_number,
	const std::string seat_type,
	const std::string seat_price):
	 passenger_name(passenger_name),
	 train_number(train_number),
	 departure_station(departure_station),
	 terminal_station(terminal_station),
	 departure_time(departure_time),
	 terminal_time(terminal_time),
	 box_number(box_number),
	 seat_number(seat_number),
	 seat_type(seat_type),
	 seat_price(seat_price) {}
/*
 * Private Part
 */
void Train::read_in() {
	/*
	Initialize the list of Box
	*/
	string temp_line;
	boxes_data.open(boxes_file, fstream::in);
	if (boxes_data.fail()) 
	{ 
		cerr << "\nFail to open " + boxes_file + "!"; 
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	else {
		while (getline(boxes_data, temp_line))
		{
			String_Manipulation SM(temp_line);
			SM.chopping();
			if (SM.pieces.size() == 5)
			{
				boxes.push_back(Box(
						SM.pieces.at(0),
						stoul(SM.pieces.at(1)),
						stoul(SM.pieces.at(2)),
						stoul(SM.pieces.at(3)),
						stod(SM.pieces.at(4))			
					));
			}
			else
			{
				boxes_data.close();
				cerr << "\nWrong infomations occur in " + boxes_file + "!";
				cerr << "\nNow program is end up, hitting any key to continue...";
				_getch();				
				_exit(1);
			}
		}
		boxes_data.close();
	}

	/*
	Initialize the vector of Seats
	*/
	string prev_type("");
	unsigned temp_seat_left(0);
	double prev_seat_price(0);
	// Noisy problem Here: In list, having no way to konw whether curr is the last element
	for (auto& curr_box : boxes)
	{
		prev_type == "" ? prev_type = curr_box.seat_type : prev_type;
		prev_seat_price == 0 ? prev_seat_price = curr_box.seat_price : prev_seat_price;
		if (curr_box.seat_type == prev_type)
		{
			temp_seat_left += curr_box.seat_left;
		}
		else
		{
			seats.push_back(Seat(
				prev_type,
				temp_seat_left,
				prev_seat_price)
			);
			prev_type = curr_box.seat_type;
			temp_seat_left = curr_box.seat_left;
			prev_seat_price = curr_box.seat_price;
		}	
	}
	// Add the last type of seat
	seats.push_back(Seat(boxes.back().seat_type, temp_seat_left, boxes.back().seat_price));
}
void Trains::read_in() {
	string temp_line;
	trains_data.open(trains_file, fstream::in);
	if (trains_data.fail())
	{
		cerr << "\nFail to open " + trains_file + "!";
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	else
	{
		while (getline(trains_data, temp_line))
		{
			String_Manipulation SM(temp_line);
			SM.chopping();
			if (SM.pieces.size() == 5)
			{
				trains.push_back(Train(
					SM.pieces.at(0),
					SM.pieces.at(1),
					SM.pieces.at(2),
					SM.pieces.at(3),
					SM.pieces.at(4),
					"Data Files/Trains_Info/Boxes/" + SM.pieces.at(0) + "_boxes.txt"
				));
			}
			else
			{
				trains_data.close();
				cerr << "\nWrong infomations occur in " + trains_file + "!";
				cout << "\nNow program is end up, hitting any key to continue...";
				_getch();			
				_exit(1);
			}
		}
	}
	trains_data.close();
}