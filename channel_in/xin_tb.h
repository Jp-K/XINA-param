#include "channel_in.h"

#define data_width_p 8

SC_MODULE(tb){

    sc_clock clk_i;
    sc_signal<sc_bv<1>> rst_i;
    sc_signal<sc_bv<data_width_p>> data_i;
    sc_signal<sc_bv<1>> val_i;
    sc_signal<sc_bv<1>> ack_o;

    sc_signal<sc_bv<1>> req_l_o, req_n_o, req_e_o, req_s_o, req_w_o;
    sc_signal<sc_bv<4>> gnt_i;

    sc_signal<sc_bv<1>> rok_o;
    sc_signal<sc_bv<4>> rd_i;
    sc_signal<sc_bv<data_width_p>> data_o;

    channel_in<1,1,data_width_p,4> *tb0;

    void test(){
        sc_bv<data_width_p> pack_n[5] = {"11111111", "00000010", "00000100", "10000000"};
        wait(1, SC_NS);

        for(int i=0; i<4; i++){
            data_i.write(pack_n[i]);
            wait(1, SC_NS);
            gnt_i.write("0100");
            wait(3, SC_NS);
        }
        //wait(1, SC_NS);
        data_i.write("00000000");
        gnt_i.write("0000");
        wait(1,SC_NS);
    }

    void reset(){
        data_i.write("00000000");
        rst_i.write("1");
        wait(1, SC_NS);
        rst_i.write("0");
        wait(1, SC_NS);
    }
    void ack(){
        val_i.write("0");
        wait(1, SC_NS);
        while(true){
            if(ack_o.read()=="1"){
                val_i.write("0");
                wait(1, SC_NS);
            }else {
                val_i.write("1");
                wait(1,SC_NS);
            }
        }
    }
    void rd(){
        while(true){
            if(rok_o.read() == "1"){
                rd_i.write("0100");
                wait(1, SC_NS);
            } else {
                rd_i.write("0000");
                wait(1, SC_NS);
            }
        }
    }


    SC_CTOR(tb){
        SC_THREAD(ack);
        SC_THREAD(reset);
        SC_THREAD(test);
        SC_THREAD(rd);
        sensitive << clk_i << rst_i;

        tb0 = new channel_in<1,1,data_width_p,4>("xin-tb");

        tb0->rst_i(rst_i);
        tb0->clk_i(clk_i);
        tb0->data_i(data_i);
        tb0->val_i(val_i);
        tb0->ack_o(ack_o);
        tb0->req_l_o(req_l_o);
        tb0->req_n_o(req_n_o);
        tb0->req_e_o(req_e_o);
        tb0->req_s_o(req_s_o);
        tb0->req_w_o(req_w_o);
        tb0->gnt_i(gnt_i);
        tb0->rok_o(rok_o);
        tb0->rd_i(rd_i);
        tb0->data_o(data_o);

        sc_trace_file *wf = sc_create_vcd_trace_file("xin_tb");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");
        sc_trace(wf, data_i, "data_i");
        sc_trace(wf, val_i, "val_i");
        sc_trace(wf, ack_o, "ack_o");
        sc_trace(wf, req_l_o, "req_l_o");
        sc_trace(wf, req_n_o, "req_n_o");
        sc_trace(wf, req_e_o, "req_e_o");
        sc_trace(wf, req_s_o, "req_s_o");
        sc_trace(wf, req_w_o, "req_w_o");
        sc_trace(wf, gnt_i, "gnt_i");
        sc_trace(wf, rok_o, "rok_o");
        sc_trace(wf, rd_i, "rd_i");
        sc_trace(wf, data_o, "data_o");


    }
};