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
	const unsigned& seat_account,
	const double& seat_price) :
	seat_type(seat_type),
	number(number),
	seat_account(seat_account),
	seat_price(seat_price) {}
Seats::Seats(const std::string& type,
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
//unsigned Train::sum_seat(const std::string& seat_type)
//{
//	unsigned temp_sum(0);
//	for (auto& box : this->boxes)
//	{
//		if(box.seat_type == seat_type)
//		{
//			temp_sum += box.seat_account;
//		}
//	}
//	return temp_sum;
//}
Trains::Trains(
	const std::string& trains_file) :
	trains_file(trains_file) {
	read_in();
}
/*
 * Private Part
 */
void Train::read_in() {
	/*
	Initialize the list of Box
	*/
	string temp_line;
	boxes_data.open(boxes_file, fstream::in);
	if (boxes_data.fail()) { cerr << "\nFail to open Boxes.txt!"; }
	while (getline(boxes_data, temp_line))
	{
		String_Manipulation SM(temp_line);
		SM.chopping(" ");
		if (SM.pieces.size() == 13)
		{
			if (SM.pieces.at(0) == number)
			{
				unsigned temp_boxes_account(0);
				unsigned box_number(0);
				for (unsigned index = 2; index != 14; index += 4)
				{
					temp_boxes_account = stoi(SM.pieces.at(index));
					for (unsigned i = 0; i != temp_boxes_account; ++i)
					{
						boxes.push_back(
							Box(
							SM.pieces.at(index - 1),
							++box_number,
							stoul(SM.pieces.at(index + 1)),
							stod(SM.pieces.at(index + 2))
							)
						);
					}
				}
				break;
			}
			else {
				continue;
			}
		}
		else
		{
			cerr << "\nWrong infomations occur in boxes.txt!";
			cerr << "\nNow program is end up, hitting any key to continue...";
			_getch();
			boxes_data.close();
			_exit(1);
		}
	}
	boxes_data.close();
	/*
	Initialize the vector of Seats
	*/
	string prev_type("");
	unsigned temp_seat_left(0);
	double prev_seat_price(0);
	// Problem Here: In list, having no way to konw whether curr is the last element
	for (auto& curr : boxes)
	{
		prev_type == "" ? prev_type = curr.seat_type : prev_type;
		prev_seat_price == 0 ? prev_seat_price = curr.seat_price : prev_seat_price;
		if (curr.seat_type == prev_type)
		{
			temp_seat_left += curr.seat_account;
		}
		else
		{
			seats.push_back(Seats(
				prev_type,
				temp_seat_left,
				prev_seat_price)
			);
			prev_type = curr.seat_type;
			temp_seat_left = curr.seat_account;
			prev_seat_price = curr.seat_price;
		}	
	}
	// Add the last type of seat
	seats.push_back(Seats(boxes.back().seat_type, temp_seat_left, boxes.back().seat_price));
}
void Trains::read_in() {
	string temp_line;
	trains_data.open(trains_file, fstream::in);
	if (trains_data.fail()) { cerr << "\nFail to open Trains.txt!"; }
	while (getline(trains_data, temp_line))
	{
		String_Manipulation SM(temp_line);
		SM.chopping(" ");
		if (SM.pieces.size() == 7)
		{
			trains.push_back(Train(SM.pieces.at(0), SM.pieces.at(1), SM.pieces.at(2), SM.pieces.at(3), SM.pieces.at(4), "Data Files/Trains_Info/Boxes.txt"));
		}
		else
		{
			cerr << "\nWrong infomations occur in Trains.txt!";
			cerr << "\nNow program is end up, hitting any key to continue...";
			_getch();
			trains_data.close();
			_exit(1);
		}	
	}
	trains_data.close();
}