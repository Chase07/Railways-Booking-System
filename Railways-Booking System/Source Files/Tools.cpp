#include"Tools.h"

using namespace::std;
/*
 * Public Part
 */
String_Manipulation::String_Manipulation(const std::string& source) : str(source) {}
void String_Manipulation::chopping(const std::string& cut)
{
	string::size_type pos1 = 0, pos2 = 0;
	string::size_type size = str.size();
	string temp;
	for (; pos2 < size; pos1 = pos2 + 1)
	{

		pos2 = str.find(cut, pos1);
		pos2 == string::npos ? pos2 = size : pos2;// Judge whether pos2 points to the end of str
		temp = str.substr(pos1, pos2 - pos1);
		pieces.push_back(temp);
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
string String_Manipulation::sewing(const std::string& thread)
{
	string temp_str;
	for (auto& piece : pieces)
	{
		temp_str += (thread + piece);
	}
	return temp_str.erase(0, thread.size());// Cut the first substring of thread
}
std::string String_Manipulation::extend_str(const std::string& str, const std::string& prefix, const std::string& suffix)
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
	while ((curr_char = _getch()) != 13)
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
			_getch();
		}
	}
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
void Input_Control::set_accept_amount(const unsigned& amount)
{
	this->amount = amount;
}
void Input_Control::set_echo(const char& echo) { this->echo = echo; }
/*
 * Private Part
 */
void Input_Control::clear()
{
	accept.clear();
}
