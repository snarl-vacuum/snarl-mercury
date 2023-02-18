//============================================================================
// Name        : Loan.cpp
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include "Loan.h"

LoanData& Loan::getLoanData() {
    return ld;
} // getLoanData()

bool Loan::wasCalculated() {
    return calculated;
} // wasCalculated()

void Loan::calculate() {
    LoanCalculator lc;
    lrd = lc.calculate(ld);
    calculated = true;
} // calculate()

void Loan::outputToConsole() {
    cout << endl;
    printf("principle: $%2.2Lf\n", ld.principle);
    printf("term: %2.1Lf\n", ld.term);
    printf("rate: %1.4Lf%%\n", ld.rate * 100);
    printf("extraPrinciple: $%2.2Lf\n", ld.extraPrinciple);
    printf("paymentNumber extraExtraPrinciple\n");
    if(ld.extraExtraPrincipleMap.size() > 0) {
        for(ExtraExtraPrincipleMap::const_iterator it=ld.extraExtraPrincipleMap.begin(); it!=ld.extraExtraPrincipleMap.end(); ++it) {
            printf("%1i $%2.2Lf\n", it->first, it->second);
        }
    }
    cout << endl;
    printf("sumInterest: $%2.2Lf\n", lrd.sumInterest);
    printf("sumPrinciple: $%2.2Lf\n", lrd.sumPrinciple);
    printf("sumExtraPrinciple: $%2.2Lf\n", lrd.sumExtraPrinciple);
    printf("sumLoanPayments: $%2.2Lf\n", lrd.sumLoanPayments);
    printf("totalPrinciple: $%2.2Lf\n", lrd.totalPrinciple);
    printf("totalSavings: $%2.2Lf\n", lrd.totalSavings);
    cout << endl;

    LoanInstallmentDataVector installments = lrd.installments;
    printf("Number Date Payment Interest Principle ExtraPrinciple StartingPrinciple RemainingPrinciple\n");
    for(auto &lid : installments) {
        char str_date[256];
        strftime(str_date, sizeof(str_date), "%m/%d/%Y", &lid.date);
        //if(lid.date.tm_year==2018-1900) {
        //	printf("*");
        //}
        printf("%1i %s $%2.2Lf $%2.2Lf $%2.2Lf $%2.2Lf $%2.2Lf $%2.2Lf\n", lid.number, str_date, lid.payment, lid.interestPayment, lid.principlePayment, lid.extraPrinciplePayment, lid.principle, lid.remainingPrinciple);
    }
    cout << endl;
} // outputToConsole()

LoanReimbursementData& Loan::getLoanReimbursementData() {
    return lrd;
} // getLoanReimbursementData()

void Loan::outputToCsvFile(const string& filename) {
    if(filename.empty() || filename.size()==0) { 
        cout << "Filename is empty, no csv file created!" << endl;
        return; 
    }

    FILE * pFile;
    cout << "Outputting file: " << filename << endl;
    pFile = fopen(filename.c_str(), "w");

    FILENL;
    fprintf(pFile, "principle:,$%2.2Lf\n", ld.principle);
    fprintf(pFile, "term:,%2.1Lf\n", ld.term);
    fprintf(pFile, "rate:,%1.4Lf%%\n", ld.rate * 100);
    fprintf(pFile, "extraPrinciple:,$%2.2Lf\n", ld.extraPrinciple);
    fprintf(pFile, ",paymentNumber,extraExtraPrinciple\n");
    if(ld.extraExtraPrincipleMap.size() > 0) {
        for(ExtraExtraPrincipleMap::const_iterator it=ld.extraExtraPrincipleMap.begin(); it!=ld.extraExtraPrincipleMap.end(); ++it) {
            fprintf(pFile, ",%1i,$%2.2Lf\n", it->first, it->second);
        }
    }
    FILENL;
    fprintf(pFile, "sumInterest:,$%2.2Lf\n", lrd.sumInterest);
    fprintf(pFile, "sumPrinciple:,$%2.2Lf\n", lrd.sumPrinciple);
    fprintf(pFile, "sumExtraPrinciple:,$%2.2Lf\n", lrd.sumExtraPrinciple);
    fprintf(pFile, "sumLoanPayments:,$%2.2Lf\n", lrd.sumLoanPayments);
    fprintf(pFile, "totalPrinciple,$%2.2Lf\n", lrd.totalPrinciple);
    fprintf(pFile, "totalSavings:,$%2.2Lf\n", lrd.totalSavings);
    FILENL;

    LoanInstallmentDataVector installments = lrd.installments;
    fprintf(pFile, "Number,Date,Payment,Interest,Principle,ExtraPrinciple,StartingPrinciple,RemainingPrinciple\n");
    for(auto &lid : installments) {
        char str_date[256];
        strftime(str_date, sizeof(str_date), "%m/%d/%Y", &lid.date);
        //if(lid.date.tm_year==2018-1900) {
        //	printf("*");
        //}
        fprintf(pFile, "%1i,%s,$%2.2Lf,$%2.2Lf,$%2.2Lf,$%2.2Lf,$%2.2Lf,$%2.2Lf\n", lid.number, str_date, lid.payment, lid.interestPayment, lid.principlePayment, lid.extraPrinciplePayment, lid.principle, lid.remainingPrinciple);
    }
    FILENL;

    fclose(pFile);
    cout << "Done!" << endl;
} // outputToCsvFile
