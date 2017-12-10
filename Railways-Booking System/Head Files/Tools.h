#ifndef Tools
#define Tools

#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>
#include<sstream>
#include<conio.h>

class String_Manipulation
{
public :
	std::vector<std::string> pieces;
	std::vector<char> char_pieces;
public :
	String_Manipulation() = default;
	String_Manipulation(const std::string& source);
	void chopping(const std::string& cut);
	void chop_into_char();
	std::string sewing(const std::string& thread);
	template <typename T>
	std::string num_to_str(const T& number);
	std::string extend_str(const std::string& str, const std::string& prefix = "", const std::string& suffix = "");
	void clear(const std::string& what);
private :
	std::string str;
	std::string cut;
private :
};
template <typename T>
std::string String_Manipulation::num_to_str(const T& number)
{
	stringstream a_str;
	a_str << number;
	return a_str.str();

}

class Input_Control
{
public :
	Input_Control(const std::string& accept_char, const unsigned& amount);
	Input_Control(const char& beg_char, const char& end_char, const unsigned& amount);
	std::istringstream& filtered_in(std::istream& in = std::cin);
	void set_accept_char(
		const std::string& accept_char);
	void set_accept_range(
		const char& beg_char, 
		const char& end_char);
	void set_accept_amount(
		const unsigned& amount);
	void set_echo(const char& echo);
private :
	std::unordered_set<char> accept;
	unsigned amount;
	char echo;
	std::string accept_istream;
	std::istringstream filtered_istream;

private :
	void clear();
};
#endif // Tools
