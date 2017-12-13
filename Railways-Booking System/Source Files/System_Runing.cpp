#include"System_Runing.h"

#include<conio.h>

using namespace::std;

/*
 * Public Part
 */
System::System(
	const std::string& trains_file,
	const std::string& passengers_file,
	const std::string& managers_file) :
	/*trains_file(trains_file),
	passengers_file(passengers_file),
	managers_file(managers_file),*/
	user_decision(""), 
	Infa(),
	trains_manager(trains_file),
	users(passengers_file, managers_file),
	curr_user(), 
	curr_manager(nullptr), 
	curr_passenger(nullptr) {}
void System::Run()
{	
	launch();
	//Infa.trainsIF();
}
/*
 * Private Part
 */
void System::launch()
{
	main_meun_option();
}
void System::receive_option()
{
	Input_Control IC('1', '9',  1);
	cout << "\nPLZ select the option by entering an integer:";
	IC.filtered_in() >> user_decision;
}
void System::main_meun_option()
{
	while (true)
	{
		Infa.welcomeIF();
		receive_option();
		switch (stoul(user_decision))
		{
			case 1: {			
				/*
				1.Searh Trains
				*/		
				system("cls");
				search_trains();
				continue;
			}
			case 2: {
				/*
				2.Login
				*/
				system("cls");
				login();		
				continue;
			}
			case 3: {
				/*
				3.Sign up
				*/
				system("cls");
				sign_up();
				continue;
			}
			case 4: {
				/*
				4.Update and exit
				*/
				update_files();
				exit_system();
				continue;
			}

			default: {
				cerr <<  "\nSuch an option doesn't exist! Hit any key to retry...";
				_getch();
				continue;

			}		
		}
	}
}
void System::manager_meun_option(Manager& curr_manager)
{
	while (true)
	{
		Infa.managerIF(curr_manager.name);
		receive_option();

		switch (stoul(user_decision))
		{
			case 1: {
				system("cls");
				/*
				1.Add Trains
				*/
				//curr_manager.add_trains();
				continue;
			}
			case 2: {
				system("cls");
				/*
				2.List of Passenagers
				*/
				info_of_passengers();
				continue;
			}
			case 3: {
				system("cls");
				/*
				3.Change password
				*/
				curr_manager.change_password();	
				continue;
			}
			case 4: {
				/*
				4.Return to Main-menu
				*/
				this->curr_manager = nullptr;
				main_meun_option();
				continue;
			}
			case 5: {
				/*
				5.Update and exit
				*/
				update_files();
				exit_system();
				continue;
			}
			default: {
				cout << "\nSuch an option doesn't exist!" << endl;
				continue;
			}
		}
	}
}
void System::passneger_meun_option(Passenger& curr_passenger)
{
	while (true)
	{
		Infa.passengerIF(curr_passenger.name);
		receive_option();

		switch (stoul(user_decision))
		{
			case 1: {
				system("cls");
				/*
				1.Book Trains
				*/
				search_trains();
				continue;
			}
			case 2: {
				system("cls");
				/*
				2.List orders
				*/
				Infa.ordersIF(curr_passenger.orders);
				cout << "You can hit any key to return...";
				_getch();
				continue;
			}
			case 3: {
				system("cls");
				/*
				3.Change password
				*/
				curr_passenger.change_password();
				continue;
			}
			case 4: {
				/*
				4.Return Tickets
				*/
				return_tickets();
				continue;
			}
			case 5: {
				/*
				5.Update and exit
				*/
				update_files();
				exit_system();
				continue;
			}
			case 6: {
				/*
				6.Return to Main-menu
				*/
				this->curr_passenger = nullptr;
				main_meun_option();
			}
			default: {
				cout << "\nSuch an option doesn't exist!" << endl;
				continue;

			}
		}
	}
}
void System::login()
{
	string manager_detect;
	cout << "\nPLZ input your name:";
	cin >> manager_detect;
	if (manager_detect == "manager")
	{
		// Manager
		cout << "\nPLZ input your name anagin:";
		cin >> curr_user.name;
		curr_manager = check_id(curr_user, users.managers);
		if(curr_manager != nullptr )
		{		
			manager_meun_option(*curr_manager);
		}
		else { 
			cerr << "\nPlZ hitting any key to return main menu..."; 
			_getch();// Receive any key
		}
		
	}
	else {
		// Passenger
		curr_user.name = manager_detect;
		curr_passenger = check_id(curr_user, users.passengers);
		if(curr_passenger != nullptr)
		{ 		
			passneger_meun_option(*curr_passenger);
		}
		else {
			cerr << "\nPLZ hitting any key to return main menu...";
			_getch();// Receive any key
		}
	}

}
void System::sign_up()
{
	User new_user;
	Input_Control IC("YyNn", 1);
	string temp_password;
	string status;

	cout << "\nFirst input your name:";
	cin >> status;
	if (status == "0668")
	{
		cout << "\nPLZ input your name again:";
		cin >> new_user.name;
	}
	else 
	{
		new_user.name = status;
	}
	while (true)
	{
		cout << "\nAnd then input your password:";
		new_user.receive_password();
		temp_password = new_user.password;
		cout << "\nMake sure input the password as above:";
		new_user.receive_password();
		if (new_user.password != temp_password)
		{
			cerr << "\nTwo passwords is not the same!";
			cerr << "\nWould you want to retry?[Y/N]";
			IC.filtered_in() >> user_decision;
			if (user_decision.at(0) == 'Y' || user_decision.at(0) == 'y') { continue; }
			else if (user_decision.at(0) == 'N' || user_decision.at(0) == 'n') { break; }
		}
		else 
		{
			// Password is verified
			if (status == "0668")
			{
				// The new user is a manager
				users.managers.push_back(Manager(
					new_user.name, 
					new_user.password, 
					users.generate_job_number()
				));
				curr_manager = get_id(new_user, users.managers);
				if (curr_manager != nullptr)
				{				
					cout << "\nThe resistration is successful! Hit any key to menu...";
					_getch();
					manager_meun_option(*curr_manager);
				}
				else {
					cout << "\nThe resistration is failed! Hit any key to main menu...";
					_getch();
				}				
				break;
			}
			else
			{
				// The new user is a passenger
				users.passengers.push_back(Passenger(
					new_user.name,
					new_user.password,
					"Data Files/Users_Info/Orders/" + new_user.name + "_orders.txt"
				));
				curr_passenger = get_id(new_user, users.passengers);
				if (curr_passenger != nullptr)
				{				
					cout << "\n\nThe resistration is successful! Hit any key to menu...";
					_getch();
					passneger_meun_option(*curr_passenger);
				}
				else
				{
					cerr << "\n\nThe resistration is failed! Hit any key to main menu...";
					_getch();
				}			
				break;
			}
		}
	}
}
void System::search_trains() {
	string departure;
	string terminal;
	Input_Control IC("YyNn", 1);
	if (curr_passenger == nullptr) 
	{ 
		cout << "Without login, you can't book any trains!"; 
		cout << "\nWould you want to continue?[Y/N]:";
		IC.filtered_in() >> user_decision;
		if (user_decision == "Y" || user_decision == "y") { /*Do Nothing*/ }
		else if (user_decision == "N" || user_decision == "n") { return; }
	}
	cout << "\n\nPLZ input the departure:";
	cin >> departure;
	cout << "\nPLZ input the terminal:";
	cin >> terminal;
	search_trains(departure, terminal);
}
void System::search_trains(std::string& departure, std::string& terminal) 
{
	list<const Train*> suited_trains;
	for (auto& train : trains_manager.trains)
	{
		if (train.departure_station == departure && train.terminal_station == terminal)
		{
			suited_trains.push_back(&train);
		}
	}
	if (suited_trains.size() != 0)
	{
		Infa.trainsIF(suited_trains);// Show the information of trains
		if(curr_passenger != nullptr)
		{
			curr_passenger->book_trains(&trains_manager);
		}
		if (curr_passenger == nullptr)
		{
			cout << "\nYou can hit any key at any time to return main menu...";
			_getch();
		}
	}
	else 
	{
		cerr << "No data about " + departure + " to " + terminal + ", hitting any key to return menu...";
		_getch();
	}
	
}
void System::info_of_passengers()
{
	while (true)
	{
		Infa.info_of_passengersIF(users.passengers);
		if (curr_manager != nullptr)
		{
			curr_passenger = curr_manager->info_of_passengers(users.passengers);
			if (curr_passenger != nullptr)
			{
				Infa.ordersIF(curr_passenger->orders);
			}
			else { break; }
		}
		else
		{
			cerr << "\nFatal error occured in search_trains function!";
			cout << "\nYou can hit any key to end up...";
			_getch();
			_exit(1);
		}	
	}
}
void System::return_tickets()
{
	Input_Control IC1('0', '9', 10);
	Input_Control IC2("YyNn", 1);
	Input_Control IC3;
	IC3.set_accept_amount(20);
	IC3.set_accept_range('A', 'Z');
	IC3.add_accept_range('a', 'z');
	IC3.add_accept_char(" _");
	string temp_order_number;
	string temp_passenger_name;
	Order* curr_order;
	Ticket* curr_ticket;

	Infa.ordersIF(curr_passenger->orders);
	while (true)
	{
		cout << "\nPLZ select the order by typing the order number:";
		IC1.filtered_in() >> temp_order_number;
		curr_order = curr_passenger->find_order(temp_order_number);
		if (curr_order != nullptr)
		{
			while (true)
			{
				cout << "\nPLZ type the passenger's name to choose ticket:";
				IC3.filtered_in() >> temp_passenger_name;
				curr_ticket = curr_order->find_ticket(temp_passenger_name);
				if (curr_ticket != nullptr)
				{
					// Add the train seat
					trains_manager.add_seat(*curr_ticket);
					if (false == curr_order->erase_ticket(curr_ticket->passenger_name))
					{
						cerr << "\nFatal error occur in erase_ticket function...";
						cout << "\nNow hitting any key to end up...";
						_getch();
						_exit(1);
					}
					// minus the ticket or order if ticket_amount become zero
					if (curr_order->ticket_amount == 0)
					{
						File_Managing FM;
						FM.rmfile(curr_order->tickets_file);// Delete the ticket file
						if (false == curr_passenger->erase_order(curr_order->order_number))
						{
							cerr << "\nFatal error occur in erase_order function...";
							cout << "\nNow hitting any key to end up...";
							_getch();
							_exit(1);
						}
					}
					cout << "\nYou have returned the " + temp_passenger_name + "'s ticket!";
					cout << "\nNow hitting any key to return...";
					_getch();
					break;
				}
				else
				{
					cerr << "\nYou have typed a wrong passenger's name...";
					cout << "\nWould you want to retry?[Y/N]:";
					IC2.filtered_in() >> user_decision;
					if (user_decision.at(0) == 'Y' || user_decision.at(0) == 'y') { continue; }
					else if (user_decision.at(0) == 'N' || user_decision.at(0) == 'n') { break; }
				}
			}
			break;

		}
		else
		{
			cerr << "\nYou don't have such order...";
			cout << "\nWould you want to retry?[Y/N]:";
			IC2.filtered_in() >> user_decision;
			if (user_decision.at(0) == 'Y' || user_decision.at(0) == 'y') { continue; }
			else if (user_decision.at(0) == 'N' || user_decision.at(0) == 'n') { break; }
		}
	}
}
void System::exit_system() { _exit(0); }
void System::update_files()
{
	std::string temp_line;
	String_Manipulation SM;
	File_Managing FM;

	/*
	Update the passengers_data 
	*/
	// OK
	data_stream.close();
	data_stream.open(users.passengers_file, fstream::out);// Open and empty it
	if (data_stream.fail())
	{
		cerr << "\nFail to open " + users.passengers_file + " while updating!";
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	else
	{
		for (auto& temp_passenger : users.passengers)
		{

			data_stream << setiosflags(ios::left)
				<< setw(20) << temp_passenger.name
				<< setw(20) << temp_passenger.password << endl;		
		}
	}

	/*
	Update the orders_data
	*/
	for (auto& temp_passenger : users.passengers)
	{
		data_stream.close();
		data_stream.open(temp_passenger.orders_file, fstream::out);// Open and empty it
		if (data_stream.fail())
		{
			cerr << "\nFail to open " + temp_passenger.orders_file + " while updating!";
			cout << "\nPLZ check the data file, hitting any key to exit...";
			_getch();
			_exit(1);
		}
		else
		{
			for (auto& temp_order : temp_passenger.orders)
			{
				data_stream << setiosflags(ios::left)
					<< setw(20) << temp_order.order_number
					<< setw(20) << temp_order.booking_time << endl;
			}
		}
	}

	/*
	Update the tickets_data
	*/
	for (auto& temp_passenger : users.passengers)
	{
		for (auto& temp_order : temp_passenger.orders)
		{
			data_stream.close();
			data_stream.open(temp_order.tickets_file, fstream::out);// Open and empty it
			if (data_stream.fail())
			{
				SM.reset_str(temp_order.tickets_file);
				SM.chopping("\\/");
				SM.pieces.pop_back();
				if (true == FM.mkdir(SM.sewing("/")))
				{
					data_stream.open(temp_order.tickets_file, fstream::out);
					if (data_stream.fail())
					{
						cerr << "\nFail to open " + temp_order.tickets_file + " while updating!";
						cout << "\nPLZ check the data file, hitting any key to exit...";
						_getch();
						_exit(1);
					}
				}
				else
				{
					cerr << "\nFail to creat " + SM.sewing("/") + " while updating!";
					cout << "\nPLZ check the data file, hitting any key to exit...";
					_getch();
					_exit(1);
				}
				
			}
			/*
			While runing here, the data_stream is absolutely OK!
			*/
			for (auto& temp_ticket : temp_order.tickets)
			{
				data_stream << setiosflags(ios::left)
					<< setw(16) << temp_ticket.passenger_name
					<< setw(16) << temp_ticket.train_number
					<< setw(16) << temp_ticket.departure_station
					<< setw(16) << temp_ticket.terminal_station
					<< setw(16) << temp_ticket.departure_time
					<< setw(16) << temp_ticket.terminal_time
					<< setw(16) << temp_ticket.box_number
					<< setw(16) << temp_ticket.seat_number
					<< setw(16) << temp_ticket.seat_type
					<< setw(16) << temp_ticket.seat_price << endl;
			}
		}
	}

	/*
	Update the managers_data
	*/
	data_stream.close();
	data_stream.open(users.managers_file, fstream::out);// Open and empty it
	if (data_stream.fail())
	{
		cerr << "\nFail to open " + users.managers_file + " while updating!";
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	else
	{
		for (auto& temp_manager : users.managers)
		{
			data_stream << setiosflags(ios::left)
				<< setw(20) << temp_manager.name
				<< setw(20) << temp_manager.password
				<< setw(20) << temp_manager.job_number << endl;
		}
	}

	/*
	Update the trains_data
	*/
	data_stream.close();
	data_stream.open(trains_manager.trains_file, fstream::out);// Open and empty it
	if (data_stream.fail())
	{
		cerr << "\nFail to open " + trains_manager.trains_file + " while updating!";
		cout << "\nPLZ check the data file, hitting any key to exit...";
		_getch();
		_exit(1);
	}
	else
	{
		for (auto& temp_train : trains_manager.trains)
		{
			data_stream << setiosflags(ios::left)
				<< setw(16) << temp_train.number
				<< setw(16) << temp_train.departure_station
				<< setw(16) << temp_train.terminal_station
				<< setw(16) << temp_train.departure_time
				<< setw(16) << temp_train.terminal_time << endl;
		}
	}

	/*
	Update the boxes_data
	*/
	for (auto& temp_train : trains_manager.trains)
	{
		data_stream.close();
		data_stream.open(temp_train.boxes_file, fstream::out);
		if (data_stream.fail())
		{
			cerr << "\nFail to open " + temp_train.boxes_file + " while updating!";
			cout << "\nPLZ check the data file, hitting any key to exit...";
			_getch();
			_exit(1);
		}
		else 
		{
			for (auto& temp_box : temp_train.boxes)
			{
				data_stream << setiosflags(ios::left)
					<< setw(16) << temp_box.seat_type
					<< setw(16) << SM.num_to_str(temp_box.number)
					<< setw(16) << SM.num_to_str(temp_box.seat_left)
					<< setw(16) << SM.num_to_str(temp_box.seat_amount)
					<< setw(16) << SM.num_to_str(temp_box.seat_price) << endl;
			}
		}	
	}
}
