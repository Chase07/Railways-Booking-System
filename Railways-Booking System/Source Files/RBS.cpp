#define _CRT_SECURE_NO_WARNINGS
#include"System_Runing.h"
//#include<iostream>
//#include<conio.h>
//#include<fstream>
//#include<ctime>
using namespace::std;
int main()
{
	System RBS(
		"Data Files/Trains_Info/Trains.txt",
		"Data Files/Users_Info/passengers.txt",
		"Data Files/Users_Info/managers.txt");
	RBS.Run();

	//Input_Control IC('0', '9', 20);
	//IC.add_accept_char(' ');
	//IC.add_accept_char(27);
	//string temp_str;
	//cout << "PLZ input something:";

	//while (true)
	//{
	//	getline(IC.filtered_in(), temp_str);
	//	if (temp_str == "\x1b") { cout << "successful!\n"; }// [ESC]
	//	cout << temp_str << endl;
	//}

	/*string str("	 abc@@@babab@@@@@a@@fdasf@@fa@@fda  ");
	String_Manipulation SM(str);
	SM.chopping("@@");*/

	/*File_Managing FM;
	if (true == FM.mkdir("Data Files/1/2/3/4/5/6/7/8/9//"))
	{
		cout << "successful!";
	}
	else
	{
		cout << "failed!";
	}*/

	
	
	/*char c;
	while (true) {
		c = _getch();
		std::cout << (int)c << std::endl;
	}*/
	return 0;
}