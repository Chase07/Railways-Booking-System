#ifndef Users_Managing
#define Users_Managing
#define _CRT_SECURE_NO_WARNINGS

#include"Tools.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<conio.h>
#include<ctime>

class User
{
public :
	std::string name;
	std::string password;
public :
	User() = default;
	User(const std::string& name, const std::string& password);
	void receive_password();
	void change_password();
private :
	std::string user_decision;
};
class Passenger : public User
{
public :
	// 需要设计订单信息
	std::string order_number;
	std::vector<std::string> orders;

public :
	Passenger() = default;
	Passenger(const std::string& name, const std::string& password);
	void book_trains();
	void return_tickets();
};
class Manager : public User
{
public :
	std::string job_number;

public :
	Manager() = default;	
	Manager(const std::string& name, const std::string& password, const std::string& job_number);
	void add_trains();
	void passengers_info();
};
class Users
{
public:
	std::vector<Passenger> passengers;
	std::vector<Manager> managers;
public :
	Users() = default;
	Users(const std::string& passengers_file, 
		  const std::string& managers_file);
	template<typename T> void update_password(const std::string& status, T& user);
	std::string generate_job_number();
private :
	std::string passengers_file;
	std::string managers_file;
	std::fstream users_data;
	size_t manager_account;
private :
	void read_in();
	
};
template<typename T> void Users::update_password(const std::string& status, T& user)
{
	// 更新文件需要被改进
	std::string temp_file_name;
	std::string temp_file;
	std::string temp_line;
	if (status == "Manager") { temp_file_name = managers_file; }
	else if(status == "Passenger") { temp_file_name = passengers_file; }
	users_data.open(temp_file_name, fstream::in);
	if (users_data.fail()) { cerr << "Fail to open " + status + "s' file!"; }
	else
	{
		while (getline(users_data, temp_line))
		{			
			String_Manipulation SM(temp_line);
			SM.chopping(" ");
			if (user.name == SM.pieces.at(0))
			{
				SM.pieces.at(1) = user.password;
				temp_line = SM.sewing(" ");
				
			}
			temp_file += temp_line + "\n";
		}
		users_data.close();
		users_data.open(temp_file_name, fstream::out);
		users_data << temp_file;
	}
	users_data.close();
}
#endif // Users_Managing 