/*
Nianqi Chen
logger class is created to connect the database, open, insert and read 
from the table
Oct 1, 2022
*/

#include "logger.h"
using namespace std;

	static string appName; //the name of the app pass to all function
	const char* FILENAME= "/home/nchen65/cs3307/nchen65_indi_asn/logger.db"; //the database will created in a fixed place
	sqlite3 *db; //database handle keeping the database open all the time

	/*
	logger constructor
	parameter string app is the input name of the table name
	logger set up the databse and create table
	return a logger class object
	*/
	logger::logger(string app){
		appName = app; //the table generated will have name of the input string
		int exit = 0;
		char* errmsg; //string to store error message

		/*open the database*/
		exit = sqlite3_open(FILENAME,&db);
		if (exit)
		{
			/* report error if the database is not open */
			cerr << "Error open db" << sqlite3_errmsg(db) << endl;
		}

		/*if not exist create the table use the name passed by parameter*/
		int data = 0;
		string createstr = "create table if not exists "+ appName + " (timestamp varchar(255), message varchar(255));";
		char *sqlcreate = const_cast<char*>(createstr.c_str());
		data = sqlite3_exec(db, sqlcreate, NULL, 0, &errmsg);
		if (data != SQLITE_OK)
		{
			/* report error if the table is not created */
			cerr << "Error create table" << endl;
		}
	}

	/*
	destructor
	close the database and tear down the object.
	*/
	logger::~logger(){
		sqlite3_close(db);
	}

	/*
	write is the function to insert log records
	parameter string logMessage is the input string selected to put in database
	does not return 
	*/
	void logger::write(string logMessage){
		int insert = 0;
		char* errmsg;

		/*create time stamp when writing into database */
		time_t now = time(0);  // current date/time based on current system
		string timestamp = ctime(&now);

		/*generate sql and insert messsage+timestamp into table*/
		string insertstr = "insert into "+appName+" values (\""+ timestamp +"\"," "\""+ logMessage +"\");";
		char *sqlinsert = const_cast<char*>(insertstr.c_str());
		insert = sqlite3_exec(db,sqlinsert,NULL,0,&errmsg);
		if (insert != SQLITE_OK)
		{
			/* report error if the data is not inserted */
			cerr << "Error insert data" << endl;
		}
	}


	/*
	read_all is a function to read all log element from databse 
	no parameter needed
	return a vector of logMessage object 
	*/
	vector<logMessage> logger::read_all(){
		int rc = 0;
        sqlite3_stmt *stmt;

        //create a vector to store the return value
        vector<logMessage> logRecord;
        string selectstr = "select * from "+appName + ";";
        char *sqlselect = const_cast<char*>(selectstr.c_str());
        rc = sqlite3_prepare_v2(db,sqlselect,-1,&stmt, NULL);
        if (rc != SQLITE_OK){
                cerr << "select failed" << sqlite3_errmsg(db) << endl;
        }

        /*
        select all elements from table and save them into 
        a vector of logMessage class
        */
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
            const char* timestp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* msg = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string stamp = string(timestp);
            string logmsg = string(msg);
            logMessage newElement(logmsg,stamp);
            logRecord.push_back(newElement);
        }
        if (rc != SQLITE_DONE){
                cerr << "select failed" << endl;
        }
        sqlite3_finalize(stmt);
        return logRecord;
	}




