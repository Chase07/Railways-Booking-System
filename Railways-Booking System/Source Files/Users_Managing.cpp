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
		cout << "\n\nPLZ verify your new password:";
		receive_password();
		if (password == original_password)
		{
			cerr << "\n\nThe new password is same as the original password!";
			cout << "\nWould you want to retry?[Y/N]";
			IC.filtered_in() >> user_decision;
			if (user_decision == "Y" || user_decision == "y") { continue; }
			else if (user_decision == "N" || user_decision == "n") { break; }
		}
		else if (password != temp_password)
		{
			password = original_password;
			cerr << "\n\nTwo passwords is not the same!";
			cout << "\nWould you want to retry?[Y/N]";
			IC.filtered_in() >> user_decision;
			if (user_decision == "Y" || user_decision == "y") { continue; }
			else if (user_decision == "N" || user_decision == "n") { break; }
		}
		else {
			cout << "\n\nYou already changed your password! Enter any key to return.";
			_getch();
			break;
		}		
	}	
}
/*
µÈ´ýÐÞ¸Ä
*/
Passenger::Passenger(
	const std::string& name, 
	const std::string& password) : 
	User(name, password) {}
Manager::Manager(
	const std::string& name, 
	const std::string& password, 
	const std::string& job_number) : 
	User(name, password), 
	job_number(job_number) {}
Users::Users(
	const std::string& passengers_file, 
	const std::string& managers_file) :
	passengers_file(passengers_file), 
	managers_file(managers_file) {
	read_in();
	manager_account = managers.size();
}
string Users::generate_job_number()
{
	time_t now = time(nullptr);
	tm* local_time = localtime(&now);
	String_Manipulation SM;
	string personal_code( SM.num_to_str(manager_account) );
	string month_code = ( SM.num_to_str(local_time->tm_mon + 1) );
	string day_code = ( SM.num_to_str(local_time->tm_mday) );

	if (personal_code.size() != 2) 
	{ SM.extend_str(personal_code, "0"); }
	SM.pieces.push_back(personal_code);

	SM.pieces.push_back(SM.num_to_str(local_time->tm_year + 1900));
	
	if (month_code.size() != 2)
	{
		SM.extend_str(month_code, "0");
	}
	SM.pieces.push_back(month_code);
	
	if (day_code.size() != 2)
	{
		SM.extend_str(day_code, "0");
	}
	SM.pieces.push_back(day_code);
	
	return SM.sewing("");
}
/*
 * Protected Part
 */


/*
 * Private Part
 */
void Users::read_in()
{
	string temp_line;
	users_data.open(passengers_file, fstream::in);
	if (users_data.fail()) { cerr << "\nFail to open passengers.txt!"; }
	while (getline(users_data, temp_line))
	{
		String_Manipulation SM(temp_line);
		SM.chopping(" ");
		if (SM.pieces.size() == 2)
		{
			passengers.push_back(Passenger(SM.pieces.at(0), SM.pieces.at(1)));
		}
		else
		{
			cerr << "\nWrong infomations occur in passengers.txt!";
			cerr << "\nNow program is end up, hitting any key to continue...";
			_getch();
			exit( 1 );
		}
	}
	users_data.close();

	users_data.open(managers_file, fstream::in);
	if (users_data.fail()) { cerr << "\nFail to open managers.txt!"; }
	while (getline(users_data, temp_line))
	{
		String_Manipulation SM(temp_line);
		SM.chopping(" ");
		if (SM.pieces.size() == 3)
		{
			managers.push_back(Manager(SM.pieces.at(0), SM.pieces.at(1), SM.pieces.at(2)));
		}
		else
		{
			cerr << "\nWrong infomations occur in managers.txt!";
			cerr << "\nNow program is end up, hitting any key to continue...";
			_getch();
			users_data.close();
			exit( 1 );
		}	
	}
	users_data.close();
}
