#include "arbitration.h"

SC_MODULE(arbitration_tb){

    sc_clock clk_w;
    sc_signal<sc_bv<1>> rst_w;
    sc_signal<sc_bv<4>> req_w;
    sc_signal<sc_bv<4>> gnt_w;
    arbitration *oc_mre0;

    void logic(){
        sc_bv<4> count[8] = {"0000", "0011", "0100", "0111", "1010", "1101", "1111", "0101"};
        for(int i=0; i<8; i++){
            req_w.write(count[i]);
            wait(5,SC_NS);
        }
        wait(10,SC_NS);
        sc_stop();
    }

    void reset(){
        rst_w.write("1");
        wait(1, SC_NS);
        rst_w.write("0");
        wait(1, SC_NS);
    }

    SC_CTOR(arbitration_tb){
        oc_mre0 = new arbitration("tb");

        oc_mre0->clk_i(clk_w);
        oc_mre0->rst_i(rst_w);
        oc_mre0->req_i(req_w);
        oc_mre0->gnt_o(gnt_w);

        sensitive << clk_w << rst_w << req_w << gnt_w;
        SC_THREAD(logic);
        SC_THREAD(reset);

        sc_trace_file *wf = sc_create_vcd_trace_file("oc_tb");

        sc_trace(wf, req_w, "req_i");
        sc_trace(wf, gnt_w, "gnt_i");
        sc_trace(wf, rst_w, "rst_i");
        sc_trace(wf, clk_w, "clk_i");
    }
};