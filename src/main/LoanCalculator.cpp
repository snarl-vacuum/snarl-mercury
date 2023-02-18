//============================================================================
// Name        : LoanCalculator.cpp
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include "LoanCalculator.h"

LoanReimbursementData LoanCalculator::calculate(const LoanData& ld) {
	LoanReimbursementData lrd;
	int totaln = ld.term * ld.ppy;
	LoanInstallmentDataVector installments(totaln);

	// number of periodic payments
	int npp = ld.ppy * ld.term;
	// periodic interest rate
	long double pir = ld.term == 0 ? 0 : ld.rate / ld.ppy;
	// discount factor D = {[(1 + i) ^n] - 1} / [i(1 + i)^n]
	long double df = ( pow(( 1 + pir ), npp) - 1) / ( pir * pow(( 1 + pir ), npp) );
	long double payment = df == 0 ? 0 : ld.principle / df;
	long double principle = ld.principle;
	tm date;
	strptime(ld.date.c_str(), "%m/%d/%Y", &date);

	lrd.sumPrinciple = 0;
	lrd.sumInterest = 0;

	// r = (rate / ppy)
	long double r = ld.rate / ld.ppy;
	for(int n=0; n<totaln; ++n) {
		LoanInstallmentData lid;

		lid.number = n+1;
		lid.date = date;
		lid.payment = payment;
		lid.principle = principle;

		lid.extraPrinciplePayment = 0;
		if(ld.extraPrinciple > 0) {
			lid.extraPrinciplePayment += ld.extraPrinciple;
		}
		unsigned int payNumber = n + 1;
		if(ld.extraExtraPrincipleMap.count(payNumber)>0) {
			lid.extraPrinciplePayment += ld.extraExtraPrincipleMap.at(payNumber);
		}

		// (rate / ppy) * principle
		lid.interestPayment = (r * principle);
		lid.principlePayment = payment - lid.interestPayment;

		long double cp = principle;
		principle -= lid.principlePayment;
		if(principle < 0) {
			lid.principlePayment = cp;
			lid.extraPrinciplePayment = 0;
			lid.payment = lid.principlePayment + lid.extraPrinciplePayment;
		} else {
			cp = principle;
			principle -= lid.extraPrinciplePayment;
			if(principle < 0) {
				lid.extraPrinciplePayment = cp;
			}
		}

		lid.remainingPrinciple = principle;
		// handle rounding issues once paid off... (for display purposes)
		if(lid.remainingPrinciple<0 && (int)(lid.remainingPrinciple * 100)/100==0) {
			lid.remainingPrinciple = 0;
		}

		lrd.sumPrinciple += lid.principlePayment;
		lrd.sumInterest += lid.interestPayment;
		lrd.sumExtraPrinciple += lid.extraPrinciplePayment;

		installments[n] = lid;

		++date.tm_mon;
		if(date.tm_mon > 11) {
			date.tm_mon = 0;
			++date.tm_year;
		}

		if(principle <= 0) {
			unsigned int size = n;
			if((int)(lid.payment * 100)/100>0) {
				++size;
			}
			installments.resize(size);
			break;
		}
	}

	lrd.totalPrinciple = lrd.sumPrinciple + lrd.sumExtraPrinciple;
	lrd.sumLoanPayments = lrd.sumPrinciple + lrd.sumInterest + lrd.sumExtraPrinciple;
	lrd.totalSavings = (npp * payment - ld.principle) - ( lrd.sumLoanPayments - lrd.totalPrinciple );

	lrd.installments = installments;

	return lrd;
    
} // calculate()