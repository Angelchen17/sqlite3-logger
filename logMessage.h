/*
Nianqi Chen
header file for logMessage class
Sep, 19, 2022
*/


#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <iostream>
#include <sqlite3.h>


class logMessage
{
private:
	std::string logmsg;
	std::string timestamp;
public:
	logMessage(std::string msgtxt, std::string timeStamp);
	~logMessage();
	std::string get_message();
	std::string get_timestamp();
};

#endif