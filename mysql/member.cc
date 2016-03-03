/*
 * member.cc
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

 
#include <iostream>
using namespace std;
#include "member.h"

Member::Member()
{
	contents = new string[structure.size()];
}

Member::~Member()
{
	delete [] contents;
}

bool Member::auth(string _password) 
{
	if (password == _password) return true;
	else return false;
}

bool Member::checkValidEmail(string _email)
{
	for(int i=1; i < _email.length() - 1; i++) if(_email[i] == '@') return true;
	return false;
}

string Member::setInfo(string _email, string _password, Level _level, string _name, string _tel, string _follow)
{
	string errorMessage = "No Error";
	if(!checkValidEmail(_email)) errorMessage = "email is invalid!";
	else email = _email;
	if(_password.length() < 6 && _password.length() > 20) errorMessage = "password should be 6~20 letters!";
	else password = _password;
	level = _level;
	name = _name;
	tel = _tel;
	follow = _follow;
	return errorMessage;
}

void Member::show()
{
	cout << "email : " << email << endl;
	//cout << "level : " << Util::Ltos(level) << endl;
	cout << "name : " << name << endl;
	cout << "tel : " << tel << endl;
	cout << "follow : " << follow << endl;
}
