/*
 * main.cpp
 *
 *  Created on: 14 Aug 2013
 *      Author: s0972326
 */

#include "aico.h"
#include <iostream>

using namespace SOC;
using namespace Eigen;
using namespace tinyxml2;
using namespace std;

int main(int argn,char **argv)
{
	XMLDocument doc;
	if (doc.LoadFile("../aico.xml")!=XML_SUCCESS || !doc.RootElement()) {cerr<<"Can't load xml file\n"; return 1;}

	AICO aico;
	if(aico.Init((SystemAbstraction*)0, doc.RootElement()))
	{
		aico.IterateToConvergence();
	}
	else
	{
		cerr << "Cannot initialise AICO!\n";
	}
	return 0;
}





