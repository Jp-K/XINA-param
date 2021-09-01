#include <systemc.h>
#include "XINA.h"

#define data_width_c 8
#define cols_c 2
#define rows_c 2


SC_MODULE(tb){

    sc_clock clk_i;
    sc_signal<sc_bv<1>> rst_i;

    sc_signal<sc_bv<data_width_c>> l_in_data_i[cols_c][rows_c];
    sc_signal<sc_bv<1>> l_in_val_i[cols_c][rows_c];
    sc_signal<sc_bv<1>> l_in_ack_o[cols_c][rows_c];
    sc_signal<sc_bv<data_width_c>> l_out_data_o[cols_c][rows_c];
    sc_signal<sc_bv<1>> l_out_val_o[cols_c][rows_c];
    sc_signal<sc_bv<1>> l_out_ack_i[cols_c][rows_c];

    XINA<rows_c, cols_c, data_width_c> *xina;

    void rst(){
        rst_i.write("1");
        wait(1, SC_NS);
        rst_i.write("0");
        wait(1, SC_NS);
    }

    void test(){
        sc_bv<data_width_c> pack_n[4] = {"10000001", "00000100", "00010000", "10000000"};
        l_in_val_i[0][0].write("0");
            wait(1, SC_NS);
        for(int i=0; i<4; i++){
            l_in_val_i[0][0].write("0");
            l_in_data_i[0][0].write(pack_n[i]);
            wait(1, SC_NS);
            l_in_val_i[0][0].write("1");
            while(l_in_ack_o[0][0].read() != "1"){
                wait(1, SC_NS);
            }
            l_in_val_i[0][0].write("0");
            while(l_in_ack_o[0][0].read() != "0"){
                wait(1, SC_NS);
            }
        }
        l_in_data_i[0][0].write("00000000");
        wait(100, SC_NS);
    }

    void o_00(){
        while(true){
            l_out_ack_i[0][0].write("0");
            while (l_out_val_o[0][0].read() != "1")
            {
                wait(1, SC_NS);
            }
            l_out_ack_i[0][0].write("1");
            wait(1, SC_NS);
            while (l_out_val_o[0][0].read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    void o_01(){
        while(true){
            l_out_ack_i[0][1].write("0");
            while (l_out_val_o[0][1].read() != "1")
            {
                wait(1, SC_NS);
            }
            l_out_ack_i[0][1].write("1");
            wait(1, SC_NS);
            while (l_out_val_o[0][1].read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    void o_10(){
        while(true){
            l_out_ack_i[1][0].write("0");
            while (l_out_val_o[1][0].read() != "1")
            {
                wait(1, SC_NS);
            }
            l_out_ack_i[1][0].write("1");
            wait(1, SC_NS);
            while (l_out_val_o[1][0].read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    void o_11(){
        while(true){
            l_out_ack_i[1][1].write("0");
            while (l_out_val_o[1][1].read() != "1")
            {
                wait(1, SC_NS);
            }
            l_out_ack_i[1][1].write("1");
            wait(1, SC_NS);
            while (l_out_val_o[1][1].read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    SC_CTOR(tb){
        SC_THREAD(test);
        SC_THREAD(o_00);
        SC_THREAD(o_01);
        SC_THREAD(o_10);
        SC_THREAD(o_11);
        SC_THREAD(rst);
        sensitive << clk_i << rst_i;
        xina = new XINA<rows_c, cols_c, data_width_c>("tb");
        xina->clk_i(clk_i);
        xina->rst_i(rst_i);

        sc_trace_file *wf = sc_create_vcd_trace_file("XINA_tb");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");
        
        int each = 0;
        for(int i=0; i<cols_c; i++){
            for(int j=0; j<rows_c; j++){
                xina->l_in_data_i[i][j](l_in_data_i[i][j]);
                xina->l_in_val_i[i][j](l_in_val_i[i][j]);
                xina->l_in_ack_o[i][j](l_in_ack_o[i][j]);
                xina->l_out_data_o[i][j](l_out_data_o[i][j]);
                xina->l_out_val_o[i][j](l_out_val_o[i][j]);
                xina->l_out_ack_i[i][j](l_out_ack_i[i][j]);

                sc_trace(wf, l_in_data_i[i][j], "l_in_data_i"+each);
                sc_trace(wf, l_in_val_i[i][j],  "l_in_val_i"+each);
                sc_trace(wf, l_in_ack_o[i][j],  "l_in_ack_o"+each);
                sc_trace(wf, l_out_data_o[i][j],"l_out_data_o"+each);
                sc_trace(wf, l_out_val_o[i][j], "l_out_val_o"+each);
                sc_trace(wf, l_out_ack_i[i][j], "l_out_ack_i"+each);

                each++;
            }
        }
    }
};