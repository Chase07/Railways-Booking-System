#ifndef System_Runing
#define System_Runing

#include"Tools.h"
#include"Interface.h"
#include"Users_Managing.h"
#include"Trains_Managing.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<memory>

class System {
	friend void User::change_password();
public:
	System();
	void Run();

private:
	std::string user_decision; 
	Interface Infa;
	Users users;
	User curr_user;
	Manager* curr_manager;
	Passenger* curr_passenger;
	Trains trains;
	
private :
	void launch();
	void receive_option();
	void main_meun_option();
	void manager_meun_option();
	void passneger_meun_option();
	void login();
	void sign_up();
	void search_trains();
	void search_trains(std::string& departure, std::string& terminal);
	void exit_system();
	void update_file();
	template <typename T> T* check_id(User& curr_user, std::vector<T>& users);

};
template <typename T> T* System::check_id(User& curr_user, std::vector<T>& users)
{
	Input_Control IC("YNyn", 1);
	for (auto& user : users)
	{
		if (user.name == curr_user.name)
		{
			while (true)
			{
				cout << "\nPLZ input your password:";
				curr_user.receive_password();
				if (user.password == curr_user.password) { return &user; }
				else
				{
					cerr << "\n\nWrong password!";
					cout << "\nWould you want to retry?[Y/N]";
					IC.filtered_in() >> user_decision;
					if (user_decision == "Y" || user_decision == "y") { continue; }
					else if (user_decision == "N" || user_decision == "n") { return nullptr; }
				}
			}		
		}				
	}
	cerr << "\nNo such name here!" << endl;
	return nullptr;
}

#endif // System_Runing