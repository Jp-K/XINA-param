#include "flow_out.h"
#include "flow_out_tb.h"

#define data_width_p 8

int sc_main(int argc, char* argv[]){
    flow_out<data_width_p> ofc_par_mre0("ofc_par_mre");
    flow_out_tb ofc_par_mre_tb("ofc_par_mre_tb");

    sc_clock w_clk_i;
    sc_signal<sc_bv<1>> w_rst_i, w_ack_i, w_rok_i;
    sc_signal<sc_bv<1>> w_val_o, w_rd_o;
    sc_signal<sc_bv<data_width_p>> w_data_i;
    sc_signal<sc_bv<data_width_p>> w_data_o;

    ofc_par_mre0.data_i(w_data_i);
    ofc_par_mre0.data_o(w_data_o);
    ofc_par_mre0.clk_i(w_clk_i);
    ofc_par_mre0.rst_i(w_rst_i);
    ofc_par_mre0.val_o(w_val_o);
    ofc_par_mre0.rok_i(w_rok_i);
    ofc_par_mre0.ack_i(w_ack_i);
    ofc_par_mre0.rd_o(w_rd_o);

    ofc_par_mre_tb.data_i(w_data_i);
    ofc_par_mre_tb.data_o(w_data_o);
    ofc_par_mre_tb.clk_i(w_clk_i);
    ofc_par_mre_tb.rst_i(w_rst_i);
    ofc_par_mre_tb.val_o(w_val_o);
    ofc_par_mre_tb.rok_i(w_rok_i);
    ofc_par_mre_tb.ack_i(w_ack_i);
    ofc_par_mre_tb.rd_o(w_rd_o);


    sc_trace_file *wf = sc_create_vcd_trace_file("ofc_par_mre");

    sc_trace(wf, w_data_i, "w_data_i");
    sc_trace(wf, w_data_o, "w_data_o");

    sc_trace(wf, w_clk_i, "w_clk_i");
    sc_trace(wf, w_rst_i, "w_rst_i");
    sc_trace(wf, w_val_o, "w_val_o");
    sc_trace(wf, w_rok_i, "w_rok_i");
    sc_trace(wf, w_ack_i, "w_ack_i");
    sc_trace(wf, w_rd_o, "w_rd_o");

    sc_start(100, SC_NS);
/*
    sc_bv<data_width_p> words[10] = {"00000001","00000011","00000111","00001111","00011111","00111111","01111111","11111111"};

    w_rst_i.write("1");
    sc_start(1, SC_NS);
    w_rst_i.write("0");
    sc_start(1, SC_NS);

    
    w_val_i.write("0");
    sc_start(1, SC_NS);
    w_data_i.write("00000000");
    sc_start(1, SC_NS);
    w_val_i.write("1");
    w_wok_i.write("1");

    for(int i=0; i<10; i++){
        w_val_i.write("0");
        w_wok_i.write("0");
        sc_start(1, SC_NS);
        w_data_i.write(words[i]);
        sc_start(1, SC_NS);
        w_val_i.write("1");
        w_wok_i.write("1");
        sc_start(1, SC_NS);
    }
    cout << w_data_o.read();

    sc_stop();
    */
    sc_close_vcd_trace_file(wf);
    
    return 0;

}