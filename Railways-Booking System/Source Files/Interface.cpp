#include"Interface.h"


using namespace::std;

void Interface::welcomeIF() const 
{
	system("cls");
	cout << "            Welcome to use Railway-Booking System!        " << endl;
	cout << "                                                          " << endl;
	cout << "                1.Searh Trains      2.Login               " << endl;
	cout << "                                                          " << endl;
	cout << "                3.Sign up           4.Exit                " << endl;
	
}
void Interface::passengerIF() const 
{
	system("cls");
	cout << "                  Hello, Passenger!                       " << endl;
	cout << "                                                          " << endl;
	cout << "        1.Book Trains        2.Return Tickets             " << endl;
	cout << "                                                          " << endl;
	cout << "        3.Change password    4.Return to Main-menu        " << endl;
	cout << "                                                          " << endl;
	cout << "        5.Exit                                            " << endl;

}
void Interface::managerIF() const 
{
	system("cls");
	cout << "                Bonjour, Manager!                         " << endl;
	cout << "                                                          " << endl;
	cout << "        1.Add Trains        2.Info of Passenagers	       " << endl;
	cout << "                                                          " << endl;
	cout << "        3.Change password   4.Return to Main-menu         " << endl;
	cout << "                                                          " << endl;
	cout << "        5.Exit                                            " << endl; 

}
void Interface::trainsIF(std::list<const Train*> suited_trains) const
{
	system("cls");
	cout << setiosflags(ios::left) << setw(16) << "" << setw(16) << "Departure Time" << setw(16) << "Seat Type" << setw(16) << "Seat Type" << setw(16) << "Seat Type" << endl;
	cout << setiosflags(ios::left) << setw(16) << "Train Number" << setw(16) << "" << setw(16) << "Seat Left" << setw(16) << "Seat Left" << setw(16) << "Seat Left" << endl;
	cout << setiosflags(ios::left) << setw(16) << "" << setw(16) << "Terminal Time" << setw(16) << "Seat Price" << setw(16) << "Seat Price" << setw(16) << "Seat Price" << endl;
	cout << endl;
	String_Manipulation SM;
	for (auto& train : suited_trains)
	{
		cout << setiosflags(ios::left) 
			<< setw(16) << "" 
			<< setw(16) << train->departure_time 
			<< setw(16) << train->seats.at(0).type 
			<< setw(16) << train->seats.at(1).type 
			<< setw(16) << train->seats.at(2).type << endl;
		cout << setiosflags(ios::left) 
			<< setw(16) << train->number 
			<< setw(16) << ""
			<< setw(16) << SM.num_to_str(train->seats.at(0).seat_left)
			<< setw(16) << SM.num_to_str(train->seats.at(1).seat_left)
			<< setw(16) << SM.num_to_str(train->seats.at(2).seat_left) << endl;
		cout << setiosflags(ios::left) 
			<< setw(16) << ""
			<< setw(16) << train->terminal_time << setw(16)
			<< setw(16) << SM.num_to_str(train->seats.at(0).price)
			<< setw(16) << SM.num_to_str(train->seats.at(1).price)
			<< setw(16) << SM.num_to_str(train->seats.at(2).price) << endl;
		cout << endl;
	}
	_getch();
}

