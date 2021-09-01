#include "channel_out.h"

SC_MODULE(tb){

    sc_clock clk_i;
    sc_signal<sc_bv<1>> rst_i;

    sc_signal<sc_bv<8>> data_o;
    sc_signal<sc_bv<1>> val_o;
    sc_signal<sc_bv<1>> ack_i;

    sc_signal<sc_bv<4>> req_i;
    sc_signal<sc_bv<4>> gnt_o;

    sc_signal<sc_bv<4>> rok_i;
    sc_signal<sc_bv<1>> rd_o;
    sc_signal<sc_bv<8>> data3_i, data2_i, data1_i, data0_i;

    channel_out<8> *xoutb;

    void test(){
        sc_bv<8> pack_n[5] = {"11100111", "00000010", "00000100", "10000000", "00000000"};
        wait(2, SC_NS);
        for(int i=0; i<5; i++){
            rok_i.write("0100");
            req_i.write("0100");
            wait(3, SC_NS);
            data2_i.write(pack_n[i]);
            wait(1, SC_NS);
        }
        rok_i.write("0000");
        req_i.write("0000");
        wait(1, SC_NS);
    }

    void reset(){
        data3_i.write("00000000");
        data2_i.write("00000000");
        data1_i.write("00000000");
        data0_i.write("00000000");
        rst_i.write("1");
        wait(1, SC_NS);
        rst_i.write("0");
        wait(1, SC_NS);
    }
    void ack(){
        while(true){
            ack_i.write("0");
            while (val_o.read() != "1")
            {
                wait(1, SC_NS);
            }
            ack_i.write("1");
            wait(1, SC_NS);
            while (val_o.read() != "0")
            {
                wait(1, SC_NS);
            }
            //wait(1, SC_NS);
        }
    }

    SC_CTOR(tb){
        SC_THREAD(test);
        SC_THREAD(reset);
        SC_THREAD(ack);
        sensitive << clk_i;
        xoutb = new channel_out<8>("tb");


        xoutb->clk_i(clk_i);
        xoutb->rst_i(rst_i);
        xoutb->data_o(data_o);
        xoutb->val_o(val_o);
        xoutb->ack_i(ack_i);
        xoutb->req_i(req_i);
        xoutb->gnt_o(gnt_o);
        xoutb->rok_i(rok_i);
        xoutb->rd_o(rd_o);
        xoutb->data3_i(data3_i);
        xoutb->data2_i(data2_i);
        xoutb->data1_i(data1_i);
        xoutb->data0_i(data0_i);

        sc_trace_file *wf = sc_create_vcd_trace_file("xout_tb");

        sc_trace(wf, clk_i, "clk_i");
        sc_trace(wf, rst_i, "rst_i");
        sc_trace(wf, data_o, "data_o");
        sc_trace(wf, val_o, "val_o");
        sc_trace(wf, ack_i, "ack_i");
        sc_trace(wf, req_i, "req_i");
        sc_trace(wf, gnt_o, "gnt_o");
        sc_trace(wf, rok_i, "rok_i");
        sc_trace(wf, rd_o, "rd_o");
        sc_trace(wf, data3_i, "data3_i");
        sc_trace(wf, data2_i, "data2_i");
        sc_trace(wf, data1_i, "data1_i");
        sc_trace(wf, data0_i, "data0_i");

    }
};