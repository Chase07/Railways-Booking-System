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
void Interface::passengerIF(const std::string passenger_name) const 
{
	system("cls");
	cout << "              Hello, " + passenger_name + "!              " << endl;
	cout << "                                                          " << endl;
	cout << "        1.Book Trains        2.List orders                " << endl;
	cout << "                                                          " << endl;
	cout << "        3.Change password    4.Return Tickets             " << endl;
	cout << "                                                          " << endl;
	cout << "        5.Exit               6.Return to Main-menu        " << endl;

}
void Interface::managerIF(const std::string manager_name) const
{
	system("cls");
	cout << "              Bonjour, " + manager_name + "!              " << endl;
	cout << "                                                          " << endl;
	cout << "        1.Add Trains        2.Info of Passenagers	       " << endl;
	cout << "                                                          " << endl;
	cout << "        3.Change password   4.Return to Main-menu         " << endl;
	cout << "                                                          " << endl;
	cout << "        5.Exit                                            " << endl; 

}
void Interface::trainsIF(const std::list<const Train*>& suited_trains) const
{
	system("cls");
	cout << setiosflags(ios::left) 
		<< setw(16) << "" 
		<< setw(16) << "Departure Time" 
		<< setw(16) << "Seat Type" 
		<< setw(16) << "Seat Type" 
		<< setw(16) << "Seat Type" << endl;
	cout << setiosflags(ios::left) 
		<< setw(16) << "Train Number" 
		<< setw(16) << "" 
		<< setw(16) << "Seat Left" 
		<< setw(16) << "Seat Left" 
		<< setw(16) << "Seat Left" << endl;
	cout << setiosflags(ios::left) 
		<< setw(16) << "" 
		<< setw(16) << "Terminal Time" 
		<< setw(16) << "Seat Price" 
		<< setw(16) << "Seat Price" 
		<< setw(16) << "Seat Price" << endl;
	cout << endl;

	String_Manipulation SM;
	for (auto& curr_train : suited_trains)
	{
		cout << setiosflags(ios::left) 
			<< setw(16) << "" 
			<< setw(16) << curr_train->departure_time 
			<< setw(16) << curr_train->seats.at(0).type 
			<< setw(16) << curr_train->seats.at(1).type 
			<< setw(16) << curr_train->seats.at(2).type << endl;
		cout << setiosflags(ios::left) 
			<< setw(16) << curr_train->number 
			<< setw(16) << ""
			<< setw(16) << SM.num_to_str(curr_train->seats.at(0).seat_left)
			<< setw(16) << SM.num_to_str(curr_train->seats.at(1).seat_left)
			<< setw(16) << SM.num_to_str(curr_train->seats.at(2).seat_left) << endl;
		cout << setiosflags(ios::left) 
			<< setw(16) << ""
			<< setw(16) << curr_train->terminal_time << setw(16)
			<< setw(16) << SM.num_to_str(curr_train->seats.at(0).price)
			<< setw(16) << SM.num_to_str(curr_train->seats.at(1).price)
			<< setw(16) << SM.num_to_str(curr_train->seats.at(2).price) << endl;
		cout << endl;
	}
	
}
void Interface::ordersIF(const std::list<Order>& orders) const
{
	system("cls");
	cout << setiosflags(ios::left)
		<< setw(16) << "Train Number"
		<< setw(16) << "Departure"
		<< setw(16) << "Terminal"
		<< setw(16) << "Departure Time"
		<< setw(16) << "Terminal Time" << endl;
	cout << setiosflags(ios::left)
		<< setw(16) << "Passenger"
		<< setw(16) << "Seat Type"
		<< setw(16) << "Box Number"
		<< setw(16) << "Seat Number"
		<< setw(16) << "Seat Price" << endl;
	cout << endl;
	for (auto& curr_order : orders)
	{
		cout << "This order " + curr_order.order_number + " was booked at " + curr_order.booking_time << endl;
		cout << "Tickets:" << endl;
		for (auto& curr_ticket : curr_order.tickets)
		{
			cout << endl << setiosflags(ios::left)
				<< setw(16) << curr_ticket.train_number
				<< setw(16) << curr_ticket.departure_station
				<< setw(16) << curr_ticket.terminal_station
				<< setw(16) << curr_ticket.departure_time
				<< setw(16) << curr_ticket.terminal_time << endl;
			cout << setiosflags(ios::left)
				<< setw(16) << curr_ticket.passenger_name
				<< setw(16) << curr_ticket.seat_type
				<< setw(16) << curr_ticket.box_number
				<< setw(16) << curr_ticket.seat_number
				<< setw(16) << curr_ticket.seat_price << endl;
		}
		cout << endl << endl;
	}
	
}
void Interface::info_of_passengersIF(const std::vector<Passenger>& passengers) const
{
	system("cls");
	cout << setiosflags(ios::left)
		<< setw(16) << "Passenger"
		<< setw(16) << "Order Amount" 
		<< setw(16) << "Ticket Amount" << endl;
	cout << endl;
	for (auto& curr_passenger : passengers)
	{
		unsigned temp_ticket_amount(0);
		for (auto& curr_order : curr_passenger.orders)
		{
			temp_ticket_amount += curr_order.ticket_amount;
		}
		cout << setiosflags(ios::left)
			<< setw(16) << curr_passenger.name
			<< setw(16) << curr_passenger.order_amount 
			<< setw(16) << temp_ticket_amount << endl;
	}
	cout << endl;

	//_getch();
}
