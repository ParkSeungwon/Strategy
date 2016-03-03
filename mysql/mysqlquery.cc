/*
 * mysqlquery.cc
 * This file is part of dndd
 *
 * Copyright (C) 2015 - Seungwon Park
 *
 * dndd is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dndd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dndd. If not, see <http://www.gnu.org/licenses/>.
 */

 
#include <stdexcept>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "mysqlquery.h"
using namespace std;


bool Mysqlquery::myQuery(std::string str)
{
    bool ok = false;
	try
	{
        //cout << "Executing query....." << endl << endl;
        res = stmt->executeQuery(str);
		//cout << "Done." << endl;
        ok = true;
	}
	catch (sql::SQLException &e) 
	{
		cout << "# ERR: SQLException in " << __FILE__ ;
		cout << "(" << __FUNCTION__<< ") on line " << __LINE__  << endl;
		cout << "# ERR: " << e.what();
		cout << "  (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )"  << endl << endl;
	}
    return ok;
}

bool Mysqlquery::connect(string host, string user, string pass, string db)
{
    bool ok = false;
    try {
        //cout << "Connecting database to " << host << endl << endl;
        driver = get_driver_instance();
        con = driver->connect(host, user, pass);
        con->setSchema(db);
        stmt = con->createStatement();
        //std::cout << "done.." << std::endl;
        ok = true;
    }
    catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__ ;
		cout << "(" << __FUNCTION__<< ") on line " << __LINE__  << endl;
		cout << "# ERR: " << e.what();
		cout << "  (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )"  << endl << endl;
	}
    return ok;
}

void Mysqlquery::connect(Mysqlquery& copy)
{
	driver = copy.driver;
	con = copy.con;
	stmt = copy.stmt;
	res = copy.res;
}

Mysqlquery::Mysqlquery()
{
    con = NULL;
    stmt = NULL;
    res = NULL;
}

Mysqlquery::~Mysqlquery()
{
    if(con != NULL) delete con;
    if(stmt != NULL) delete stmt;
    if(res != NULL) delete res;
}
