#include "router_tb.h"

#define data_width_p 8

int sc_main(int argc, char* argv[]){
    
    router_tb tb("tb");
    sc_start(100, SC_NS);
    
    return 0;

}