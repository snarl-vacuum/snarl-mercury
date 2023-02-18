#include <catch2/catch_test_macros.hpp>

#include "../main/Loan.h"

#include <stdio.h>  // printf
#include <iostream> // std::cout
#include <iomanip>
#include <cmath>

#include <vector>

using namespace std;

static const long double PRECISION =0.01;

TEST_CASE( "Loan.getLoanData().defaults", "[Loan]" ) {
    Loan loan;
    LoanData& ld = loan.getLoanData();

    REQUIRE( ld.date == "" );
    REQUIRE( ld.principle == 0 );
    REQUIRE( ld.term == 0 );
    REQUIRE( ld.rate == 0 );
    REQUIRE( ld.ppy == 12 );
    REQUIRE( ld.extraPrinciple == 0 );
    ExtraExtraPrincipleMap eepMap = ld.extraExtraPrincipleMap;
    REQUIRE( eepMap.size() == 0 );
}

TEST_CASE( "Loan.wasCalculated().default", "[Loan]" ) {
    Loan loan;
    REQUIRE( false == loan.wasCalculated() );
}

TEST_CASE( "Loan.calculate()", "[Loan]" ) {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);

    Loan loan;
    LoanData& ld = loan.getLoanData();

    ld.date = "5/1/2018";
    ld.rate = 0.03875 ;
    ld.principle = 157000;
    ld.term = 15;
    ld.extraPrinciple = 662.38 ;
    ExtraExtraPrincipleMap& eepMap = ld.extraExtraPrincipleMap;
    eepMap.insert(make_pair<int, long double>(11, 10000));
    eepMap.insert(make_pair<int, long double>(23, 10000));
    eepMap.insert(make_pair<int, long double>(35, 13500));
    eepMap.insert(make_pair<int, long double>(44, 59596.94));

    REQUIRE( false == loan.wasCalculated() );

    loan.calculate();

    REQUIRE( true == loan.wasCalculated() );

    LoanReimbursementData& lrd = loan.getLoanReimbursementData();

    REQUIRE( true == (fabs(15907.66-lrd.sumInterest) < PRECISION) );
    REQUIRE( true == (fabs(34758.34-lrd.sumPrinciple) < PRECISION) );
    REQUIRE( true == (fabs(122241.66-lrd.sumExtraPrinciple) < PRECISION) );
    REQUIRE( true == (fabs(172907.66-lrd.sumLoanPayments) < PRECISION) );
    REQUIRE( true == (fabs(157000.00-lrd.totalPrinciple) < PRECISION) );
    REQUIRE( true == (fabs(34362.34-lrd.totalSavings) < PRECISION) );

    LoanInstallmentDataVector& lidv = lrd.installments;
    REQUIRE( 44 == lidv.size() );

    //loan.outputToConsole();
}
