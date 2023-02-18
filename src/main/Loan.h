#ifndef LOAN_H
#define LOAN_H
//============================================================================
// Name        : Loan.h
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include "CLAs.h"
#include "LoanCalculator.h"

#define FILENL fprintf(pFile, "\n")

class Loan {
	public:
	    virtual ~Loan() {};

        virtual LoanData& getLoanData();
        virtual bool wasCalculated();
	    
        virtual void calculate();

        virtual LoanReimbursementData& getLoanReimbursementData();

        virtual void outputToConsole();
        virtual void outputToCsvFile(const string& filename);

    private:
        // INPUT
        LoanData ld;
        // OUTPUT
        LoanReimbursementData lrd;
        bool calculated = false;

}; // CLASS Loan

#endif