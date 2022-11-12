/*
Nianqi Chen
generator is the first app created to input multiple messages and 
record the log into database. 
Oct 1, 2022
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <signal.h>
#include <ctime>
#include <thread>
#include <chrono>
#include "logger.h"
using namespace std;

volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

int main(int argc, char const *argv[])
{
	if (argc <= 1)
	{
		cout << "Please input at least one message!" << endl;
	}
	/*set random seed*/
	srand(time(0));

	/*get the input name of the app name from input argument 
	by eliminating the extra information before*/
	string inName = argv[0];
    string segment;
    stringstream makeStream(inName);
    vector<string> seglist;
    while(getline(makeStream, segment, '/'))
    {
    	seglist.push_back(segment);
    }
    string appName = seglist[seglist.size()-1]; //appName stores final app name to generate table in database

    /*the logger function is called to generate log messages in a new logger called newlogger*/
    logger newlogger(appName);

    /*fetch the input message from user input*/
    vector<string> input(argv + 1, argv + argc + !argc); //input is a vector stores all messages from input

    /*set the stop signal so that the program stops with ctrl C*/
	signal(SIGINT, inthand);
    while (!stop){
    	//select one random message each time
    	string randomMsg = input[rand() % input.size()];
    	//log the selected message into database
    	newlogger.write(randomMsg);
    	//sleep for a random period of time
    	/*set random int time from 1 to 10*/
    	int timesleep = rand() % 10 +1;
        std::this_thread::sleep_for(std::chrono::seconds(timesleep));
    }
    cout << "exiting the program safely\n" << endl;

    return 0;
}