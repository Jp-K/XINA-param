#include "arbitration_tb.h"

int sc_main(int argc, char* argv[]){
    arbitration_tb tb("tb");
    sc_start(100, SC_NS);

    return 0;
}