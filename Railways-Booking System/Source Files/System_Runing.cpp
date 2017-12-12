#include"System_Runing.h"

#include<conio.h>

using namespace::std;

/*
 * Public Part
 */
System::System(): 
	user_decision(""), 
	Infa(), 
	curr_user(), 
	users("Data Files/Users_Info/passengers.txt", 
		  "Data Files/Users_Info/managers.txt"), 
	curr_manager(nullptr), 
	curr_passenger(nullptr),
	trains("Data Files/Trains_Info/Trains.txt") {}
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
				system("cls");
				/*
				1.Searh Trains
				*/			
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
void System::manager_meun_option()
{
	while (true)
	{
		Infa.managerIF();
		receive_option();

		switch (stoul(user_decision))
		{
			case 1: {
				system("cls");
				/*
				1.Add Trains
				*/
				continue;
			}
			case 2: {
				system("cls");
				/*
				2.List of Passenagers
				*/				
				continue;
			}
			case 3: {
				system("cls");
				/*
				3.Change password
				*/
				curr_manager->change_password();				
				users.update_password("Manager", *curr_manager);
				continue;
			}
			case 4: {
				/*
				4.Return to Main-menu
				*/
				curr_manager = nullptr;
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
void System::passneger_meun_option()
{
	while (true)
	{
		Infa.passengerIF();
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
				2.Return Tickets
				*/
				continue;
			}
			case 3: {
				system("cls");
				/*
				3.Change password
				*/
				curr_passenger->change_password();
				users.update_password("Passenger", *curr_passenger);
				continue;
			}
			case 4: {
				/*
				4.Return to Main-menu
				*/
				curr_passenger = nullptr;
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
			manager_meun_option();
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
			passneger_meun_option();
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
			cerr << "\n\nTwo passwords is not the same!";
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
				/////////////////
				curr_manager = get_id(new_user, users.managers);
				if (curr_manager != nullptr)
				{				
					cout << "\n\nThe resistration is successful! Hit any key to menu...";
					_getch();
					manager_meun_option();
				}
				else {
					cout << "\n\nThe resistration is failed! Hit any key to main menu...";
					_getch();
				}				
				break;
			}
			else
			{
				// The new user is a passenger
				users.passengers.push_back(Passenger(
					new_user.name,
					new_user.password
				));
				curr_passenger = get_id(new_user, users.passengers);
				if (curr_passenger != nullptr)
				{				
					cout << "\n\nThe resistration is successful! Hit any key to menu...";
					_getch();
					passneger_meun_option();
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
void System::search_trains(std::string& departure, std::string& terminal) {
	list<const Train*> suited_trains;
	for (auto& train : trains.trains)
	{
		if (train.departure_station == departure && train.terminal_station == terminal)
		{
			suited_trains.push_back(&train);
		}
	}
	if (suited_trains.size() != 0)
	{
		Infa.trainsIF(suited_trains);
		if(curr_passenger != nullptr)
		{
			curr_passenger->book_trains(&trains);
		}
		if (curr_passenger == nullptr)
		{
			cout << "You can hit any key at any time to return main menu...";
			_getch();
		}
	}
	else 
	{
		cerr << "No data about " + departure + " to " + terminal + ", hitting any key to return menu...";
		_getch();
	}
	
}
void System::exit_system() { _exit(0); }
void System::update_files()
{



}