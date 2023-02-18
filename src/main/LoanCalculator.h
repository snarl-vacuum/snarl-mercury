#ifndef LOAN_CALCULATOR_H
#define LOAN_CALCULATOR_H
//============================================================================
// Name        : LoanCalculator.h
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include <cmath>

#include <time.h>

#include <string>
#include <vector>
#include <map>

using namespace std;

typedef map<int/*payment number*/, long double/*$ amount*/> ExtraExtraPrincipleMap;

struct LoanData {
	string date;	            // first payment due...
	long double principle = 0;	// $
	long double term = 0;		// number of years
	long double rate = 0;		// annual interest
	int ppy = 12;	            // payments per year
	long double extraPrinciple = 0;	// $ per installment
	ExtraExtraPrincipleMap extraExtraPrincipleMap;
};

struct LoanInstallmentData {
	int number;
	tm date;
	long double principle;			// $ amount starting...
	long double payment;			// $ ( = interestPayment + principlePayment )
	long double interestPayment;	// $
	long double principlePayment;	// $
	long double extraPrinciplePayment = 0;	// $
	long double remainingPrinciple;	// $ amount remaining...
};

typedef vector< LoanInstallmentData > LoanInstallmentDataVector;

struct LoanReimbursementData {
	long double sumInterest = 0;	// $ term (calculated)
	long double sumPrinciple = 0;	// $ term (calculated)
	long double sumExtraPrinciple = 0;	// $ term (calculated)
	long double sumLoanPayments = 0;	// $ term (calculated)
	long double totalPrinciple = 0;		// $ term (calculated)
	long double totalSavings = 0;		// $ term (calculated)
	LoanInstallmentDataVector installments;
};

class LoanCalculator {
	public:
	    LoanReimbursementData calculate(const LoanData&);
}; // CLASS LoanCalculator

#endif