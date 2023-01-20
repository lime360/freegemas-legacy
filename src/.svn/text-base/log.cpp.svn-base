#include "log.h"

string Log::ToString(TLogLevel T){
	switch(T){
	case logERROR:
		return "ERROR";
		break;
	case logWARNING:
		return "WARNING";
		break;
	case logINFO:
		return "INFO";
		break;
	default:
		return "DEBUG";
		break;	
	}
}

string Log::cRojo = "\033[01;31m";
string Log::cVerde =  "\033[01;32m";
string Log::cAzul = "\033[01;34m";
string Log::cAmar = "\033[01;33m";
string Log::cDef = "\033[00m";

string Log::CON(string s){
    return cVerde + "[++ Constructor] " + s + cDef;
}

string Log::DES(string s){
    return cRojo + "[-- Destructor] " + s + cDef;
}

std::ostringstream& Log::Get(TLogLevel level){
    os << "[" << ToString(level) << "] ";
    return os;
}

Log::~Log(){
    os << Log::cDef << std::endl;
    if(salida){
	fprintf(stderr, "%s", os.str().c_str());
	fflush(stderr);
    }
}

bool Log::salida = true;
