#include <catch2/catch_test_macros.hpp>

#include "../main/CLAs.h"

#include <stdio.h>  // printf
#include <iostream> // std::cout
#include <iomanip>
#include <cmath>

using namespace std;

static const long double PRECISION =0.000001;

static const char* RES_LD_HOME = "../src/test/resources/ld_home_csv";
static const char* CLAS_q = "-?";
static const char* CLAS_h = "-h";
static const char* CLAS_help = "--help";
static const char* CLAS_v = "-v";
static const char* CLAS_version = "--version";

TEST_CASE( "CLAs.proc()", "[CLAs]" ) {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);

    char* argv0 = (char*)"tests.exe";
    char* argv1 = (char*)RES_LD_HOME;
    char* n_argv[] = { argv0, argv1 };
    
    CLAs clas;
    clas.proc((sizeof(n_argv) / sizeof(n_argv[0])), n_argv);

    REQUIRE( strcmp(RES_LD_HOME, clas.getInputLDFilename().c_str()) == 0 );
    REQUIRE( strcmp("5/1/2018", clas.getFirstPaymentDate().c_str()) == 0 );
    {
        bool same = fabs(157000.00-clas.getPrinciple()) < PRECISION;
        REQUIRE( true == same );
    }
    {
        bool same = fabs(15.0-clas.getTerm()) < PRECISION;
        REQUIRE( true == same );
    }
    {
        bool same = fabs(0.03875-clas.getRate()) < PRECISION;
        REQUIRE( true == same );
    }
    {
        bool same = fabs(662.38-clas.getExtraPrinciple()) < PRECISION;
        REQUIRE( true == same );
    }
    map<int/*payment number*/, long double/*$ amount*/> eepMap = clas.getExtraExtraPrincipleMap();
    REQUIRE( eepMap.size() == 4 );
    REQUIRE( eepMap.count(11) == 1 );
    REQUIRE( eepMap.count(23) == 1 );
    REQUIRE( eepMap.count(35) == 1 );
    REQUIRE( eepMap.count(44) == 1 );
    {
        bool same = fabs(10000-eepMap[11]) < PRECISION;
        REQUIRE( true == same );
    }
    {
        bool same = fabs(10000-eepMap[23]) < PRECISION;
        REQUIRE( true == same );
    }
    {
        bool same = fabs(13500-eepMap[35]) < PRECISION;
        REQUIRE( true == same );
    }
    {
        bool same = fabs(59596.94-eepMap[44]) < PRECISION;
        REQUIRE( true == same );
    }
    REQUIRE( strcmp("output.csv", clas.getOutputCsvFilename().c_str()) == 0 );
}

TEST_CASE( "CLAs.proc().outputConsoleUsage()-q", "[CLAs]" ) {
    char* argv0 = (char*)"tests.exe";
    char* argv1 = (char*)CLAS_q;
    char* n_argv[] = { argv0, argv1 };
    
    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    CLAs clas;
    clas.proc((sizeof(n_argv) / sizeof(n_argv[0])), n_argv);

    cout.rdbuf(rdbufCout);

    REQUIRE( clas.getInputLDFilename() == "" );

    std::string scout = ossCout.str(); 
    auto result = scout.find("USAGE: mercury [option...] inputLoanDataFilename");
    REQUIRE( result != std::string::npos );
}

TEST_CASE( "CLAs.proc().outputConsoleUsage()-h", "[CLAs]" ) {
    char* argv0 = (char*)"tests.exe";
    char* argv1 = (char*)CLAS_h;
    char* n_argv[] = { argv0, argv1 };
    
    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    CLAs clas;
    clas.proc((sizeof(n_argv) / sizeof(n_argv[0])), n_argv);

    cout.rdbuf(rdbufCout);

    REQUIRE( clas.getInputLDFilename() == "" );

    std::string scout = ossCout.str(); 
    auto result = scout.find("USAGE: mercury [option...] inputLoanDataFilename");
    REQUIRE( result != std::string::npos );
}

TEST_CASE( "CLAs.proc().outputConsoleUsage()--help", "[CLAs]" ) {
    char* argv0 = (char*)"tests.exe";
    char* argv1 = (char*)CLAS_help;
    char* n_argv[] = { argv0, argv1 };
    
    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    CLAs clas;
    clas.proc((sizeof(n_argv) / sizeof(n_argv[0])), n_argv);

    cout.rdbuf(rdbufCout);

    REQUIRE( clas.getInputLDFilename() == "" );

    std::string scout = ossCout.str(); 
    auto result = scout.find("USAGE: mercury [option...] inputLoanDataFilename");
    REQUIRE( result != std::string::npos );
}

TEST_CASE( "CLAs.proc().outputConsoleUsage() 0args", "[CLAs]" ) {
    char* argv0 = (char*)"tests.exe";
    char* n_argv[] = { argv0 };
    
    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    CLAs clas;
    clas.proc((sizeof(n_argv) / sizeof(n_argv[0])), n_argv);

    cout.rdbuf(rdbufCout);

    REQUIRE( clas.getInputLDFilename() == "" );

    std::string scout = ossCout.str(); 
    auto result = scout.find("USAGE: mercury [option...] inputLoanDataFilename");
    REQUIRE( result != std::string::npos );
}

TEST_CASE( "CLAs.proc().outputVersion()-v", "[CLAs]" ) {
    char* argv0 = (char*)"tests.exe";
    char* argv1 = (char*)CLAS_v;
    char* n_argv[] = { argv0, argv1 };
    
    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    CLAs clas;
    clas.proc((sizeof(n_argv) / sizeof(n_argv[0])), n_argv);

    cout.rdbuf(rdbufCout);

    REQUIRE( clas.getInputLDFilename() == "" );

    std::string scout = ossCout.str(); 
    auto result = scout.find("mercury version: ");
    REQUIRE( result != std::string::npos );
}

TEST_CASE( "CLAs.proc().outputVersion()-version", "[CLAs]" ) {
    char* argv0 = (char*)"tests.exe";
    char* argv1 = (char*)CLAS_version;
    char* n_argv[] = { argv0, argv1 };
    
    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    CLAs clas;
    clas.proc((sizeof(n_argv) / sizeof(n_argv[0])), n_argv);

    cout.rdbuf(rdbufCout);

    REQUIRE( clas.getInputLDFilename() == "" );

    std::string scout = ossCout.str(); 
    auto result = scout.find("mercury version: ");
    REQUIRE( result != std::string::npos );
}


