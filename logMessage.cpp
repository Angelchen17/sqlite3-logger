/*
Nianqi Chen
logger class is created for class logMessage storing a message and timstamp
Oct 1, 2022
*/
#include <string>
#include "logMessage.h"

using namespace std;

	string logmsg;
	string timestamp;

	/*
	constructor of logMessage
	logMessage is the message text
	timeStamp is the timestamp string
	taking strings for the message and timestamp as parameters to initialize the object.
	*/
	logMessage::logMessage(string msgtxt, string timeStamp){
		logmsg = msgtxt;
		timestamp = timeStamp;
	}

	/*
	destructor
	doing everything necessary to tear down the object.
	*/
	logMessage::~logMessage(){
	}

	/*
	get_message is function to get logmessage
	no parameter needed
	return a string with logmessage from logMessage object
	*/
	string logMessage::get_message(){
		return logmsg;
	}

	/*
	get_timestamp is function to get timestamp
	no parameter needed
	return a string with timestamp from logMessage object
	*/
	string logMessage::get_timestamp(){
		return timestamp;
	}
