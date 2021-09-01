#include "switch_tb.h"


int sc_main(int argc, char* argv[]){

    sc_switch_tb sw("tb");
    sc_start(150, SC_NS);

    return 0;
}