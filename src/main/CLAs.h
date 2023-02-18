#ifndef CLAS_H
#define CLAS_H
//============================================================================
// Name        : CLAs.h
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include "config.h"

#include <algorithm>

#include <fstream>
#include <sstream>

#include <string>
#include <cstring>
#include <vector>
#include <map>

#include "libneutils/include/StringUtils.h"

using namespace std;

class CLAs {
	public:
        string getInputLDFilename();

        string getFirstPaymentDate();
        long double getPrinciple();
        long double getTerm();
        long double getRate();
        long double getExtraPrinciple();
        map<int/*payment number*/, long double/*$ amount*/> getExtraExtraPrincipleMap();

        string getOutputCsvFilename();

	    int proc(int, char **);

    private:
        string inputLDFilename = "";

        string date;	            // first payment due...
        long double principle = 0;	// $
        long double term;		    // number of years
        long double rate;		    // annual interest
        long double extraPrinciple = 0;	// $ per installment
        map<int/*payment number*/, long double/*$ amount*/> extraExtraPrincipleMap;

        string outputCsvFilename = "";

        int processLDFileLine(const string&);
        void outputVersion();
        void outputConsoleUsage();
}; // CLASS CLAs

#endif