#include"Tools.h"

using namespace::std;
/*
 * Public Part
 */
String_Manipulation::String_Manipulation(const std::string& source) : str(source) {}
void String_Manipulation::add_piece(const string& piece) {
	pieces.push_back(piece);
}
void String_Manipulation::washing(std::string& dirty_str)
{
	if (dirty_str != "")
	{
		string::size_type pos1(0), pos2(0);
		string::size_type size = dirty_str.size();
		string temp_str;

		pos2 = dirty_str.find_first_not_of(whitespaces, pos1);
		dirty_str.erase(pos1, pos2);
		pos1 = dirty_str.find_last_not_of(whitespaces);
		dirty_str.erase(pos1 + 1);
	}
}
void String_Manipulation::chopping(const std::string& cut, const unsigned& choise)
{
	string::size_type pos1(0), pos2(0);
	string::size_type size = str.size();
	string temp_str;
	washing(str);
	if (choise == 1)
	{
		/*
		The cut is consist of some characters unwanted(Default)
		*/
		while (pos2 < size)
		{
			pos2 = str.find_first_of(cut, pos1);
			pos2 == string::npos ? pos2 = size : pos2;// Judge whether pos2 points to the end of str
			temp_str = str.substr(pos1, pos2 - pos1);
			pieces.push_back(temp_str);

			pos1 = str.find_first_not_of(cut, pos2);
		}
	}
	else if (choise == 2)
	{
		/*
		The cut is a template
		*/
		while (pos2 < size)
		{
			pos2 = str.find(cut, pos1);
			pos2 == string::npos ? pos2 = size : pos2;// Judge whether pos2 points to the end of str
			temp_str = str.substr(pos1, pos2 - pos1);
			temp_str == "" ? temp_str : pieces.push_back(temp_str);

			pos1 = pos2 + cut.size();
		}
	}
	
}

void String_Manipulation::chop_into_char()
{
	if (str != "")
	{
		for (auto& curr_char : str)
		{
			char_pieces.push_back(curr_char);
		}
	}
}
std::string String_Manipulation::sewing(const std::string& thread)
{
	string temp_str;
	for (auto& piece : pieces)
	{
		temp_str += (thread + piece);
	}
	return temp_str.erase(0, thread.size());// Cut the first substring of thread
}
std::string String_Manipulation::extend_str(
	const std::string& str, 
	const std::string& prefix, 
	const std::string& suffix)
{
	string temp_str(prefix);
	temp_str.append(str);
	temp_str.append(suffix);
	return temp_str;
}
void String_Manipulation::clear(const std::string& what)
{
	what == "all" ? 
		pieces.clear(), char_pieces.clear() :
		what == "string" ? 
		pieces.clear() : what == "char" ?
		char_pieces.clear() :
		what;
}
Input_Control::Input_Control() : echo(' ') {}
Input_Control::Input_Control(
	const std::string& accept_char,
	const unsigned& amount):
	amount(amount),
	echo(' '){
	set_accept_char(accept_char);
}
Input_Control::Input_Control(
	const char& beg_char, 
	const char& end_char, 
	const unsigned& amount):
	amount(amount),
	echo(' ') {
	set_accept_range(beg_char, end_char);
}
std::istringstream& Input_Control::filtered_in(std::istream& in)
{
	char curr_char;
	unsigned temp_amount(0);
	accept_istream.clear();
	filtered_istream.clear();
	while ((curr_char = _getch()) != 13 || accept_istream.size() == 0)// Make sure receive somethings
	{		
		if (accept.find(curr_char) != accept.end() && temp_amount < amount)
		{
			++temp_amount;
			accept_istream += curr_char;
			if (echo != ' ') { cout << echo; }
			else { cout << curr_char; }
		}
		else if (curr_char == 8 && accept_istream.size() != 0)
		{
			--temp_amount;
			accept_istream.erase(accept_istream.end() - 1);
			cout << "\b \b";// Backspace and print a ' ', then backsapce; simulating the process of deleting a character
		}
		else if (curr_char == 0 || curr_char == -32)
		{
			// discard those arrow and F* keys 
			curr_char = _getch();
		}
	}
	cout << "\n";
	filtered_istream.str(accept_istream);
	return filtered_istream;
}
void Input_Control::set_accept_char(const std::string& accept_char)
{
	clear();
	String_Manipulation SM(accept_char);
	SM.chop_into_char();
	for (auto& piece : SM.char_pieces)
	{
		accept.insert(piece);
	}
}
void Input_Control::set_accept_range(const char& beg_char, const char& end_char)
{
	clear();
	for (char temp_char = beg_char; temp_char != end_char + 1; ++temp_char)
	{
		accept.insert(temp_char);
	}
}
void Input_Control::add_accept_char(const char& accept_char)
{
	accept.insert(accept_char);
}
void Input_Control::add_accept_char(const std::string& accept_chars)
{
	String_Manipulation SM(accept_chars);
	SM.chop_into_char();
	for (auto& piece : SM.char_pieces)
	{
		accept.insert(piece);
	}
}
void Input_Control::add_accept_range(const char& beg_char, const char& end_char) 
{
	for (char temp_char = beg_char; temp_char != end_char + 1; ++temp_char)
	{
		accept.insert(temp_char);
	}
}
void Input_Control::set_accept_amount(const unsigned& amount)
{
	this->amount = amount;
}
void Input_Control::set_echo(const char& echo) { this->echo = echo; }
Time::Time()
{
	set_time();
}
void Time::set_time()
{
	String_Manipulation SM;

	time_t now = time(nullptr);
	tm* local_time = localtime(&now);

	string year;
	string month;
	string day;
	string hour;
	string minute;
	string second;

	year = SM.num_to_str(local_time->tm_year + 1900);

	SM.num_to_str(local_time->tm_mon).size() == 2 ?
		month = SM.num_to_str(local_time->tm_mon + 1) :
		month = SM.extend_str(SM.num_to_str(local_time->tm_mon), "0");

	SM.num_to_str(local_time->tm_mday).size() == 2 ?
		day = SM.num_to_str(local_time->tm_mday) :
		day = SM.extend_str(SM.num_to_str(local_time->tm_mday), "0");

	SM.num_to_str(local_time->tm_hour).size() == 2 ?
		hour = SM.num_to_str(local_time->tm_hour) :
		hour = SM.extend_str(SM.num_to_str(local_time->tm_hour), "0");

	SM.num_to_str(local_time->tm_min).size() == 2 ?
		minute = SM.num_to_str(local_time->tm_min) :
		minute = SM.extend_str(SM.num_to_str(local_time->tm_min), "0");

	SM.num_to_str(local_time->tm_sec).size() == 2 ?
		second = SM.num_to_str(local_time->tm_sec) :
		second = SM.extend_str(SM.num_to_str(local_time->tm_sec), "0");

	SM.add_piece(year);
	SM.add_piece(month);
	SM.add_piece(day);
	date = SM.sewing("-");

	date_and_now = SM.sewing("-");
	SM.clear("string");
	SM.add_piece(hour);
	SM.add_piece(minute);
	SM.add_piece(second);
	date_and_now += '-';
	date_and_now += SM.sewing(":");
}
/*
 * Private Part
 */
void Input_Control::clear()
{
	accept.clear();
}
