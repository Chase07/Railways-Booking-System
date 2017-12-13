#ifndef Tools
#define Tools
#define _CRT_SECURE_NO_WARNINGS

#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>
#include<sstream>
#include<ctime>
#include<io.h>
#include<direct.h>
#include<conio.h>

class String_Manipulation
{
public :
	std::vector<std::string> pieces;
	std::vector<char> char_pieces;
public :
	String_Manipulation() = default;
	String_Manipulation(const std::string& source);
	void reset_str(const std::string& source);
	void add_piece(const std::string& piece);
	void washing(std::string& dirty_str);
	void chopping(const std::string& cut = " \t\r\n", const unsigned& choise = 1);
	void chop_into_char();
	std::string sewing(const std::string& thread);
	template <typename T>
	std::string num_to_str(const T& number);
	std::string extend_str(const std::string& str, const std::string& prefix = "", const std::string& suffix = "");
	void clear(const std::string& what);
private :
	std::string str;
	std::string cut;
	std::string whitespaces = " \t\r\n";
private :
	
};
template <typename T>
std::string String_Manipulation::num_to_str(const T& number)
{
	stringstream a_str;
	a_str << number;
	return a_str.str();

}
class File_Managing
{
public :
	File_Managing() = default;

public :
	bool mkdir(const std::string& path);
	bool rmfile(const std::string& path);
private :
	std::string path_name;
};
class Input_Control
{
public :
	Input_Control();
	Input_Control(
		const std::string& accept_char, 
		const unsigned& amount);
	Input_Control(
		const char& beg_char, 
		const char& end_char, 
		const unsigned& amount);
	std::istringstream& filtered_in(std::istream& in = std::cin);
	void set_accept_char(
		const std::string& accept_char);
	void set_accept_range(
		const char& beg_char, 
		const char& end_char);
	void add_accept_char(
		const char& accept_char);
	void add_accept_char(
		const std::string& accept_chars);
	void add_accept_range(
		const char& beg_char,
		const char& end_char);
	void set_accept_amount(
		const unsigned& amount);
	void enable_esc();
	void disable_esc();
	void set_echo(const char& echo);
private :
	std::unordered_set<char> accept;
	unsigned amount;
	char echo;
	char esc;
	std::string accept_istream;
	std::istringstream filtered_istream;

private :
	void clear();
};
class Time
{
public :
	std::string date;
	std::string date_and_now;
public :
	Time();
private :
	void set_time();
};
#endif // Tools
