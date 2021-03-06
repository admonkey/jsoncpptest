/*
  The contents of this file are dedicated by all of its authors, including

    Michael S. Gashler,

  to the public domain (http://creativecommons.org/publicdomain/zero/1.0/).
*/

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <iostream>
#include <vector>
#ifdef WINDOWS
#	include <windows.h>
#else
#	include <unistd.h>
#endif

#include "json/json.h"
#include <fstream>

using std::cerr;
using std::cout;
using std::vector;


void mili_sleep(unsigned int nMiliseconds)
{
#ifdef WINDOWS
	MSG aMsg;
	while(PeekMessage(&aMsg, NULL, WM_NULL, WM_NULL, PM_REMOVE))
	{
		TranslateMessage(&aMsg);
		DispatchMessage(&aMsg);
	}
	SleepEx(nMiliseconds, 1);
#else
	nMiliseconds ? usleep(nMiliseconds*1024) : sched_yield(); // it is an error to sleep for more than 1,000,000
#endif
}



int main(int argc, char *argv[])
{
	int nRet = 0;
	try
	{
		cout << "executing...\n";
		/*
		// Read JSON file
		Json::Value root;
		std::ifstream config_doc("config_doc.json", std::ifstream::binary);
		config_doc >> root;
		cout << "my-encoding=" << root.get("my-encoding", "UTF-32" ).asString() << "\n";
		*/
		
		// Write JSON file
		vector<int> v;
		for (int i=0; i < 6; i++)
			v.push_back(i);
		Json::Value array;
		for (int i=0; i<v.size(); i++)
			array.append(v[i]);
		// write in a nice readible way
		Json::StyledWriter styledWriter;
		//std::cout << styledWriter.write(array);
		std::ofstream test("test.json", std::ofstream::binary);
		test << styledWriter.write(array);
		
		cout << "executed.\n";
	}
	catch(const std::exception& e)
	{
		cerr << e.what() << "\n";
		nRet = 1;
	}

	return nRet;
}

