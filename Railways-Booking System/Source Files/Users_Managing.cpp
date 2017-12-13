#include"Users_Managing.h"

using namespace :: std;

/*
 * Public Part
 */
User::User(
	const std::string& name, 
	const std::string& password) : 
	name(name), 
	password(password),
	user_decision(""){}
void User::receive_password() 
{
	password.erase(password.begin(), password.end());
	Input_Control IC('!', '~', 16);// The password is consist of 16 characters
	IC.set_echo('*');
	IC.filtered_in() >> password;
}
void User::change_password()
{
	string original_password(password);
	string temp_password;
	Input_Control IC("YyNn", 1);
	while (true)
	{
		cout << "\nPLZ input your new password:";
		receive_password();
		temp_password = password;
		cout << "\nPLZ verify your new password:";
		receive_password();
		if (password != temp_password)
		{
			password = original_password;
			cerr << "\n\nTwo passwords is not the same!";
			cout << "\nWould you want to retry?[Y/N]";
			IC.filtered_in() >> user_decision;
			if (user_decision == "Y" || user_decision == "y") { continue; }
			else if (user_decision == "N" || user_decision == "n") { break; }		
		}
		else if (password == original_password)
		{
			cerr << "\n\nThe new password is same as the original password!";
			cout << "\nWould you want to retry?[Y/N]";
			IC.filtered_in() >> user_decision;
			if (user_decision == "Y" || user_decision == "y") { continue; }
			else if (user_decision == "N" || user_decision == "n") { break; }
		}
		else {
			cout << "\n\nYou already changed your password! Enter any key to return...";
			_getch();
			break;
		}		
	}	
}
Passenger::Passenger(
	const std::string& name, 
	const std::string& password,
	const std::string& orders_file) :
	User(name, password),
	orders_file(orders_file) {
	read_in_orders();
}
void Passenger::book_trains(Trains* curr_trains)
{
	Input_Control IC1;
	IC1.set_accept_amount(16);
	IC1.add_accept_range('0', '9');
	IC1.add_accept_range('A', 'Z');
	IC1.add_accept_range('a', 'z');
	IC1.add_accept_char("_");

	Input_Control IC2('1', '9', 1);
	IC2.add_accept_char(27);
	Input_Control IC3("YyNn", 1);
	String_Manipulation SC;

	Train* booking_train(nullptr);
	Box* booking_box(nullptr);
	Seat* booking_seat;
	unsigned ticket_amount;

	//cout << "Tips: At any time, you can just press [ESC] to cancel booking...";
	/*
	Select the train
	*/
	while (true)
	{
		cout << "\nPLZ select the train number:";
		booking_train = curr_trains->find_train(IC1.filtered_in().str());
		if (booking_train != nullptr)
		{
			/*
			Select the seat_type
			*/
			while (true)
			{
				cout << "\nPLZ select the seat type:";
				booking_seat = booking_train->find_seat_type(IC1.filtered_in().str());
				if (booking_seat == nullptr)
				{
					cerr << "\nNo such seat type...";
					cout << "\nWould you want to retry?[Y/N]:";
					IC3.filtered_in() >> user_decision;
					if (user_decision.at(0) == 'Y' || user_decision.at(0) == 'y') { continue; }
					else if (user_decision.at(0) == 'N' || user_decision.at(0) == 'n') { break; }
				}
				else if (booking_seat != nullptr && booking_seat->seat_left == 0)
				{
					cerr << "This type of seat has no more seats...";
					cout << "\nWould you want to retry?[Y/N]:";
					IC3.filtered_in() >> user_decision;
					if (user_decision.at(0) == 'Y' || user_decision.at(0) == 'y') { continue; }
					else if (user_decision.at(0) == 'N' || user_decision.at(0) == 'n') { break; }
				}
				else if(booking_seat != nullptr && booking_seat->seat_left > 0)
				{
					/*
					Purchase the tickets
					*/
					while (true)
					{
						cout << "\nHow many tickets do you want:";
						ticket_amount = stoul(IC2.filtered_in().str());
						if (ticket_amount <= booking_seat->seat_left)
						{
							IC1.set_accept_range('A', 'Z');
							IC1.add_accept_range('a', 'z');
							IC1.add_accept_char(' ');
							IC1.set_accept_amount(20);// The length of passenger's name
							string passenger_name;
							list<Ticket> temp_tickets;

							/*
							Verify and draw each ticket  
							*/
							for (unsigned counter = 0; counter != ticket_amount; ++counter)
							{
								// In normally, here the booking_box must not to be nullptr 
								booking_box = booking_train->find_box(booking_seat->type);
								if (booking_box != nullptr)
								{
									cout << "\nPLZ type in the No." + SC.num_to_str(counter + 1) + " passenger's name:";
									getline(IC1.filtered_in(), passenger_name);
									temp_tickets.push_back(Ticket(
										passenger_name,
										booking_train->number,
										booking_train->departure_station,
										booking_train->terminal_station,
										booking_train->departure_time,
										booking_train->terminal_time,
										SC.num_to_str(booking_box->number),
										SC.num_to_str((booking_box->seat_amount + 1) - booking_box->seat_left),// generate the seat_number
										booking_box->seat_type,
										SC.num_to_str(booking_box->seat_price)
									));
									booking_box->seat_left - 1 != 4294967295 ? --booking_box->seat_left : booking_box->seat_left/*Do nothing*/;
									booking_seat->seat_left - 1 != 4294967295 ? --booking_seat->seat_left : booking_seat->seat_left/*Do nothing*/;
								}
								else
								{
									cerr << "Fatal error have occured in drawing ticket, system will exit now, hitting any key to continue...";
									_getch();
									_exit(1);
								}
							}
							// Add an order
							orders.push_back(Order(
								++order_amount,
								temp_tickets,
								"Data Files/Users_Info/Tickets/" + name + "/" // The complete path name will finished by Order constructor  
							));
							cout << "\nYour reservation is successful!";
							cout << "\nHitting any key to return main menu...";
							_getch();
							break;
						}
						else
						{
							cerr << "This type of seat has only " + SC.num_to_str(booking_seat->seat_left) + " ticket(s)...";
							cout << "\nWould you want to retry?[Y/N]:";
							IC3.filtered_in() >> user_decision;
							if (user_decision.at(0) == 'Y' || user_decision.at(0) == 'y') { continue; }
							else if (user_decision.at(0) == 'N' || user_decision.at(0) == 'n') { break; }
						}
					}
					break;
				}
			}	
			break;
		}
		else{
			cerr << "\nYou have selected the nonexistent train...";
			cerr << "\nWould you want to retry?[Y/N]:";
			IC3.filtered_in() >> user_decision;
			if (user_decision.at(0) == 'Y' || user_decision.at(0) == 'y') { continue; }
			else if (user_decision.at(0) == 'N' || user_decision.at(0) == 'n') { break; }
		}
	}	

}
bool Passenger::erase_order(const std::string& order_number)
{
	for (list<Order>::iterator curr = orders.begin(); curr != orders.end(); ++curr)
	{
		if (curr->order_number == order_number)
		{
			order_amount - 1 != 4294967295 ? --order_amount : order_amount;
			orders.erase(curr);
			return true;
		}
	}
	return false;
}
Order* Passenger::find_order(const std::string& order_number)
{
	for (auto& curr_order : orders)
	{
		if (curr_order.order_number == order_number)
		{
			return &curr_order;
		}
	}
	return nullptr;
}
Manager::Manager(
	const std::string& name, 
	const std::string& password, 
	const std::string& job_number) : 
	User(name, password), 
	job_number(job_number) {}
Passenger* Manager::info_of_passengers(vector<Passenger>& passengers)
{
	Input_Control IC1;
	IC1.set_accept_amount(16);
	IC1.add_accept_range('A', 'Z');
	IC1.add_accept_range('a', 'z');
	IC1.add_accept_range('0', '9');
	IC1.add_accept_char(' ');
	IC1.enable_esc();
	Input_Control IC2("YyNn", 1);
	string passenger_name;

	while (true)
	{
		cout << "\nPLZ select a singel passenger to see the details:";
		getline(IC1.filtered_in(), passenger_name);
		if (passenger_name != "\x1b")
		{
			for (auto& curr_passenger : passengers)
			{
				if (curr_passenger.name == passenger_name)
				{
					return &curr_passenger;
				}
			}
			cout << "\nYou may select an nonexistent passenger...";
			cout << "\nWould you want to retry?[Y/N]:";
			IC2.filtered_in() >> user_decision;
			if (user_decision == "Y" || user_decision == "y") { continue; }
			else if (user_decision == "N" || user_decision == "n") { return nullptr; }
		}
		else {
			return nullptr;
		}
	}
	
}
Users::Users(
	const std::string& passengers_file, 
	const std::string& managers_file) :
	passengers_file(passengers_file), 
	managers_file(managers_file) {
	read_in_users();
	passenger_amount = static_cast<unsigned>(passengers.size());
	manager_amount = static_cast<unsigned>(managers.size());
}
string Users::generate_job_number()
{
	Time now;
	String_Manipulation SM1;
	String_Manipulation SM2(now.date);
	string personal_code(SM1.num_to_str(++manager_amount));
	
	personal_code.size() == 2 ?
		SM1.add_piece(personal_code) :
		SM1.add_piece(SM1.extend_str(personal_code, "0"));
	SM2.chopping("-:");
	for (auto& curr_piece : SM2.pieces)
	{
		SM1.add_piece(curr_piece);
	}
	return SM1.sewing("");
}Order::Order(
	const std::string& order_number,
	const std::string& booking_time,
	const std::string& tickets_file):
	order_number(order_number),
	booking_time(booking_time),
	tickets_file(tickets_file){
	read_in_tickets();
	ticket_amount = static_cast<unsigned>(tickets.size());
}
Order::Order(
	unsigned& order_amount,
	const std::list<Ticket> tickets,
	const std::string& tickets_file) :
	order_number(generate_order_number(order_amount)),
	booking_time(generate_booking_time()),
	tickets(tickets),
	ticket_amount(static_cast<unsigned>(tickets.size())){
	// Supplement the path name for tickets_file
	this->tickets_file = tickets_file + order_number + "_tickets.txt";
}
Ticket* Order::find_ticket(const std::string& passenger_name)
{
	for (auto& curr : tickets)
	{
		if (curr.passenger_name == passenger_name)
		{
			return &curr;
		}
	}
	return nullptr;
}
bool Order::erase_ticket(const std::string& passenger_name)
{
	for (list<Ticket>::iterator curr = tickets.begin(); curr != tickets.end(); ++curr)
	{
		if (curr->passenger_name == passenger_name)
		{
			ticket_amount - 1 != 4294967295 ? --ticket_amount : ticket_amount;
			tickets.erase(curr);
			return true;
		}
	}
	return false;
}
/*
 * Private Part
 */
std::string Order::generate_order_number(unsigned& passenger_order_amount)
{
	Time now;
	String_Manipulation SM1;
	String_Manipulation SM2(now.date);
	string order_code(SM1.num_to_str(passenger_order_amount));

	order_code.size() == 2 ?
		SM1.add_piece(order_code) :
		SM1.add_piece(SM1.extend_str(order_code, "0"));
	SM2.chopping("-:");
	for (auto& curr_piece : SM2.pieces)
	{
		SM1.add_piece(curr_piece);
	}
	return SM1.sewing("");

}
std::string Order::generate_booking_time()
{
	return Time().date_and_now;
}
void Users::read_in_users()
{
	string temp_line;
	/*
	Read in the passengers_data
	*/
	users_data.open(passengers_file, fstream::in);
	if (users_data.fail()) 
	{ 
		cerr << "\nFail to open " + passengers_file + "!";
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	else 
	{
		while (getline(users_data, temp_line))
		{
			String_Manipulation SM(temp_line);
			SM.chopping();
			if (SM.pieces.size() == 2)
			{
				passengers.push_back(Passenger(
					SM.pieces.at(0),// passenger's name
					SM.pieces.at(1),
					"Data Files/Users_Info/Orders/" + SM.pieces.at(0) + "_orders.txt"
				));
			}
			else
			{
				users_data.close();
				cerr << "\nWrong infomations occur in  " + passengers_file + "!";
				cout << "\nNow program is end up, hitting any key to continue...";
				_getch();
				exit(1);
			}
		}
		users_data.close();
	}
		
	/*
	Read in the managers_data
	*/
	users_data.open(managers_file, fstream::in);
	if (users_data.fail())
	{ 
		cerr << "\nFail to open " + managers_file + " !";
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	else 
	{
		while (getline(users_data, temp_line))
		{
			String_Manipulation SM(temp_line);
			SM.chopping();
			if (SM.pieces.size() == 3)
			{
				managers.push_back(Manager(SM.pieces.at(0), SM.pieces.at(1), SM.pieces.at(2)));
			}
			else
			{
				users_data.close();
				cerr << "\nWrong infomations occur in " + managers_file + " !";
				cerr << "\nNow program is end up, hitting any key to continue...";
				_getch();
				exit(1);
			}
		}
		users_data.close();
	}
}
void Passenger::read_in_orders() {
	/*
	Read in the orders_data
	*/
	string temp_line;
	orders_data.open(orders_file, fstream::in);
	if (orders_data.fail())
	{
		// This is a new passenger, having no any orders
		order_amount = 0;
	}
	else
	{

		while (getline(orders_data, temp_line))
		{
			String_Manipulation SM(temp_line);
			SM.chopping();
			if (SM.pieces.size() == 2)
			{
				orders.push_back(Order(
				SM.pieces.at(0),
				SM.pieces.at(1),
				"Data Files/Users_Info/Tickets/" + name	+ "/" + SM.pieces.at(0) + "_tickets.txt"
				));
			}
			else
			{
				orders_data.close();
				cerr << "\nWrong infomations occur in " + orders_file + "!";
				cerr << "\nNow program is end up, hitting any key to continue...";
				_getch();
				exit(1);
			}
		}
		order_amount = static_cast<unsigned>(orders.size());
		orders_data.close();
	}
}
void Order::read_in_tickets()
{
	string temp_line;
	tickets_data.open(tickets_file, fstream::in);
	if (tickets_data.fail())
	{
		cerr << "\nFail to open " + tickets_file + "!";
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	while (getline(tickets_data, temp_line))
	{
		String_Manipulation SM(temp_line);
		SM.chopping();
		if (SM.pieces.size() == 10)
		{
			tickets.push_back(Ticket(
				SM.pieces.at(0),
				SM.pieces.at(1),
				SM.pieces.at(2),
				SM.pieces.at(3), 
				SM.pieces.at(4),
				SM.pieces.at(5),
				SM.pieces.at(6),
				SM.pieces.at(7),
				SM.pieces.at(8),
				SM.pieces.at(9)
			));
		}
		else
		{
			tickets_data.close();
			cerr << "\nWrong infomations occur in " + tickets_file + "!";
			cerr << "\nNow program is end up, hitting any key to continue...";
			_getch();
			exit(1);
		}
	}
	tickets_data.close();
}
