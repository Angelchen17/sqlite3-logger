/*
Nianqi Chen
header for logger class
from the table
Oct 1, 2022
*/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <sqlite3.h>
#include <ctime>
#include <vector>
#include "logMessage.h"

class logger
{
private:
	std::string appname;
public:
	logger(std::string app);
	~logger();
	void write(std::string logMessage);
	std::vector<logMessage> read_all();
};

#endif