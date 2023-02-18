//============================================================================
// Name        : mercury.cpp
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include "config.h"

#include "CLAs.h"
#include "Loan.h"
#include "LoanCalculator.h"

using namespace std;

int main(int argc, char **argv) {
	CLAs clas;
	int ret = clas.proc(argc, argv);
	if(ret==0) {
		// SETUP
		Loan loan;
		{
			LoanData& ld = loan.getLoanData();
			ld.principle = clas.getPrinciple();
			ld.term = clas.getTerm();
			ld.rate = clas.getRate();
			ld.date = clas.getFirstPaymentDate();
			ld.extraPrinciple = clas.getExtraPrinciple();
			ld.extraExtraPrincipleMap = clas.getExtraExtraPrincipleMap();
		}
		// CALCULATE
		loan.calculate();
		// OUTPUT RESULTS
		{
			string outputCsvFilename = clas.getOutputCsvFilename();
			if(outputCsvFilename.empty()) {
				loan.outputToConsole();
			} else {
				loan.outputToCsvFile(outputCsvFilename);
			}
		}

		ret = EXIT_SUCCESS;
	}
	return ret;
} // main()
