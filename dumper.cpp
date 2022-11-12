/*
Nianqi Chen
dumper is the second app created to display all logs in the databse
and close the database
Oct 1, 2022
*/

#include <iostream>
#include <string>
#include "logger.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/*
	get the name of app need dump from input and handle the situation 
	when the input does not contain only 2 arguments
	*/
	if (argc < 2)
	{
		cout << "Please input the app name you want to display log message of! " << endl;
	}else if (argc > 2)
	{
		cout << "Please input only one app name in a time" << endl;
	}

	//get the name of the app that need to dump from input
	string appName = argv[1];

	//create new logger object to access the desired table in the database
	logger newlogger(appName);

	//read all the logs from table and print
	vector<logMessage> loggingFile = newlogger.read_all();
	for (auto element: loggingFile)
	{
		/* go through the vector list and print out all the logs */
		string m = element.get_message();
		string t = element.get_timestamp();
		cout << t << ":" << m << endl;
	}

	/*call the destructor to close and database*/
	newlogger.~logger();

	return 0;
}