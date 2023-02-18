#include <catch2/catch_test_macros.hpp>

//#include <stdio.h>  // printf
//#include <iostream> // std::cout
#include <iomanip>
#include <experimental/filesystem>

#include "../main/Loan.h"

namespace fs = std::experimental::filesystem;

using namespace std;

static const long double PRECISION =0.01;

static const char* RES_LD_HOME = "../src/test/resources/ld_home";
static const char* RES_LD_HOME_CSV = "../src/test/resources/ld_home_csv";

static const char* RES_OUTPUT_TXT = "output.txt";
static const char* RES_OUTPUT_CSV = "output.csv";

TEST_CASE( "mercury.main().outputToConsole", "[mercury]" ) {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    
    {
        fs::file_status s = fs::status(RES_OUTPUT_TXT);
        if(fs::exists(s)) {
            fs::remove(RES_OUTPUT_TXT);
            s = fs::status(RES_OUTPUT_TXT);
        }
        REQUIRE( fs::exists(s)==false );
    }

    char command[50];
    sprintf(command, "./mercury.exe %s > %s", RES_LD_HOME, RES_OUTPUT_TXT);
    system(command);

    {
        fs::file_status s = fs::status(RES_OUTPUT_TXT);
        REQUIRE( fs::exists(s)==true );
    }

    ifstream t(RES_OUTPUT_TXT);
    stringstream buffer;
    buffer << t.rdbuf();

    REQUIRE( buffer.str().find("44 12/01/2021 $1151.50 $197.67 $953.83 $60259.32 $61213.15 $0.00")!=string::npos );

    fs::remove(RES_OUTPUT_TXT);
}

TEST_CASE( "mercury.main().outputToCsvFile", "[mercury]" ) {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    
    {
        fs::file_status s = fs::status(RES_OUTPUT_CSV);
        if(fs::exists(s)) {
            fs::remove(RES_OUTPUT_CSV);
            s = fs::status(RES_OUTPUT_CSV);
        }
        REQUIRE( fs::exists(s)==false );
    }

    char command[50];
    sprintf(command, "./mercury.exe %s", RES_LD_HOME_CSV);
    system(command);

    {
        fs::file_status s = fs::status(RES_OUTPUT_CSV);
        REQUIRE( fs::exists(s)==true );
    }

    ifstream t(RES_OUTPUT_CSV);
    stringstream buffer;
    buffer << t.rdbuf();

    REQUIRE( buffer.str().find("44,12/01/2021,$1151.50,$197.67,$953.83,$60259.32,$61213.15,$0.00")!=string::npos );

    fs::remove(RES_OUTPUT_CSV);
}
