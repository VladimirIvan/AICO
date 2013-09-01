#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include "tinyxml2.h"


#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

// STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>

#include <memory>

#define ASSERT( x, y ) assert( (x) && (y) )

#if CONFIG_PLATFORM == CONFIG_PLATFORM_WIN32
#  define WIN32_LEAN_AND_MEAN
#  if !defined(NOMINMAX) && defined(_MSC_VER)
#	define NOMINMAX // required to stop windows.h messing up std::min
#  endif
#  include <windows.h>
#endif

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

extern "C" {

#   include <sys/types.h>
#   include <sys/stat.h>

}

#if CONFIG_PLATFORM == CONFIG_PLATFORM_WIN32
#  undef min
#  undef max
#endif

#if CONFIG_PLATFORM == CONFIG_PLATFORM_LINUX
extern "C" {

#   include <unistd.h>
#   include <dlfcn.h>

}
#endif


#include <string>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

// Integer formats of fixed bit width
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef char int8;
// define uint64 type
#if CONFIG_COMPILER == CONFIG__COMPILER_MSVC
	typedef unsigned __int64 uint64;
	typedef __int64 int64;
#else
	typedef unsigned long long uint64;
	typedef long long int64;
#endif

#define DELNULL(X) if(X!=NULL) delete X; X=NULL;

using namespace tinyxml2;

inline bool GetParam(XMLElement* Data, const char* Name, double& Value)
{
	XMLElement* Node;
	Node=Data->FirstChildElement(Name);
	if(Node)
	{
		if(Node->QueryDoubleAttribute("Value",&Value)==tinyxml2::XML_NO_ERROR) return true;
	}
	return false;
};
inline bool GetParam(tinyxml2::XMLElement* Data, const char* Name, int& Value)
{
	tinyxml2::XMLElement* Node;
	Node=Data->FirstChildElement(Name);
	if(Node)
	{
		if(Node->QueryIntAttribute("Value",&Value)==tinyxml2::XML_NO_ERROR) return true;
	}
	return false;
};
inline bool GetParam(tinyxml2::XMLElement* Data, const char* Name, uint& Value)
{
	tinyxml2::XMLElement* Node;
	Node=Data->FirstChildElement(Name);
	if(Node)
	{
		if(Node->QueryUnsignedAttribute("Value",&Value)==tinyxml2::XML_NO_ERROR) return true;
	}
	return false;
};
inline bool GetParam(tinyxml2::XMLElement* Data, const char* Name, bool& Value)
{
	tinyxml2::XMLElement* Node;
	Node=Data->FirstChildElement(Name);
	if(Node)
	{
		if(Node->QueryBoolAttribute("Value",&Value)==tinyxml2::XML_NO_ERROR) return true;
	}
	return false;
};

///////////// Class forward declarations ///////////
////////////////////////////////////////////////////

namespace SOC
{
	class AICO;
	class SystemAbstraction;
}

#endif
