//============================================================================
// Name        : CLAs.cpp
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include "CLAs.h"

string CLAs::getInputLDFilename() {
    return inputLDFilename;
} // getInputLDFilename()

string CLAs::getFirstPaymentDate() {
    return date;
} // getFirstPaymentDate()

long double CLAs::getPrinciple() {
    return principle;
} // getPrinciple()

long double CLAs::getTerm() {
    return term;
} // getTerm()

long double CLAs::getRate() {
    return rate;
} // getRate()

long double CLAs::getExtraPrinciple() {
    return extraPrinciple;
} // getExtraPrinciple()

map<int/*payment number*/, long double/*$ amount*/> CLAs::getExtraExtraPrincipleMap() {
    return extraExtraPrincipleMap;
} // getExtraExtraPrincipleMap()

string CLAs::getOutputCsvFilename() {
    return outputCsvFilename;
} // getOutputCsvFilename()

int CLAs::processLDFileLine(const string& line) {

    if(line.empty()) {
        return 0;
    }

    //cout << line << endl;
    string::difference_type nLineComment = count(line.begin(), line.end(), '#');
    if(nLineComment==1 && line.find("#")==0) {
        return 0;
    }

    string::difference_type nEqual = count(line.begin(), line.end(), '=');
    if(nEqual!=1) {
        return 1;
    }

    vector<string> resultsEqual;
    split(line, "=", resultsEqual);
    string name = resultsEqual[0];
    // HANDLE ALL name CASES by trasforming to lower!!!
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    vector<string> resultsValue;
    split(resultsEqual[1], " ", resultsValue);
    string value = resultsValue[0];
    
    if(strcmp("extraextraprinciple", name.c_str())==0) {
        return 0;
    }
    
    if(strcmp("principle", name.c_str())==0) {
        pair<int, long double> v = convStringToLongDouble(value);
        if(v.first!=0) {
            return v.first;
        } else {
            principle = v.second;
        }
        if(principle<=0) {
            cout << "principle cannot be <= 0!" << endl;
            return 1;
        }
    }

    if(strcmp("term", name.c_str())==0) {
        pair<int, long double> v = convStringToLongDouble(value);
        if(v.first!=0) {
            return v.first;
        } else {
            term = v.second;
        }
        if(term<=0) {
            cout << "term cannot be <= 0!" << endl;
            return 1;
        }
    }

    if(strcmp("rate", name.c_str())==0) {
        pair<int, long double> v = convStringToLongDouble(value);
        if(v.first!=0) {
            return v.first;
        } else {
            rate = v.second;
        }
        if(rate<=0.0) {
            cout << "rate cannot be <= 0!" << endl;
            return 1;
        }
        if(rate>1.0) {
            cout << "rate cannot be > 1!" << endl;
            return 1;
        }
    }

    if(strcmp("date", name.c_str())==0) {
        if(validateStringDateFormat(value, "%m/%d/%Y")==0) {
            date = value;
        } else {
            cout << "date not correct format: MM/DD/YYYY!" << endl;
            return 1;
        }
    }

    if(strcmp("extraprinciple", name.c_str())==0) {
        pair<int, long double> v = convStringToLongDouble(value);
        if(v.first!=0) {
            return v.first;
        } else {
            extraPrinciple = v.second;
        }
        if(extraPrinciple<=0) {
            cout << "extraPrinciple cannot be <= 0!" << endl;
            return 1;
        }
    }

    if(strcmp("outputcsvfilename", name.c_str())==0) {
        // EMPTY is OK, will not output to csv file!
        outputCsvFilename = value;
    }

    if(isNumber(name)&&isNumber(value)) {
        pair<int, long double> v = convStringToLongDouble(value);
        if(v.first!=0) {
            return v.first;
        } else {
            int n = atoi(name.c_str());
            extraExtraPrincipleMap.insert(make_pair(n, v.second));
            if(v.second<=0) {
                cout << "payment:" << n << " extraExtraPrinciple cannot be <= 0!" << endl;
                return 1;
            }
        }
    }

    return 0;

} // processLDFileLine()

int CLAs::proc(int argc, char **argv) {
    string::difference_type nDash = 0;
    if(argc == 2) {
        string arg(argv[1]);
        nDash = count(arg.begin(), arg.end(), '-');
    }

    if(argc == 2 && nDash == 0 && !(strcmp(argv[1], "-?")==0 || strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")==0 || strcmp(argv[1], "-v")==0 || strcmp(argv[1], "--version")==0)) {
        // ASSUME second argument is input loan data filename ALWAYS!
        inputLDFilename = argv[1];

        ifstream infile(inputLDFilename);
        if(!infile.good()) {
            cout << "Filename: " << inputLDFilename << " not good!" << endl;
            return 1;
        }
        extraExtraPrincipleMap.clear();
        bool parseFileGood = true;
        string line;
        while(getline(infile, line)) {
            if(processLDFileLine(line)!=0) {
                parseFileGood = false;
                break;
            }
        } // while

        if(!parseFileGood) {
            return 1;
        }

     } else if(argc == 2 && (strcmp(argv[1], "-v")==0 || strcmp(argv[1], "--version")==0)) {
         outputVersion();
         return 1;
     } else {
         outputConsoleUsage();
         return 1;
     }

    return 0;
} // proc()

void CLAs::outputVersion() {
    cout << endl;
    cout << "------------------------------------------------------------------" << endl;
	cout << PROJECT_NAME << " version: " << PROJECT_VER << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << endl;
}

void CLAs::outputConsoleUsage() {
    cout << endl << endl;
    cout << "USAGE: mercury [option...] inputLoanDataFilename" << endl << endl;
    cout << "-?, -h, --help         Shows this help message." << endl;
    cout << "-v, --version          Print version info." << endl;
    cout << endl;
} // outputConsoleUsage()