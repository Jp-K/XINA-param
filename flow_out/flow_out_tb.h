#include "systemc.h"

#define data_width_p 8

SC_MODULE(flow_out_tb){

    sc_in_clk clk_i;
    sc_out<sc_bv<1>> rst_i, ack_i, rok_i;
    sc_in<sc_bv<1>> val_o, rd_o;
    sc_out<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<data_width_p>> data_o;

    void logic(){
        sc_bv<data_width_p> words[10] = {"00000001","00000011","00000111","00001111","00011111","00111111","01111111","11111111"};
        for(int i=0; i<10; i++){
        wait(1, SC_NS);
        data_i.write(words[i]);
        rok_i.write("1");
        wait(1, SC_NS);
        rok_i.write("0");
    }
    sc_stop();
    }
    void reset(){
        data_i.write("00000000");
        rst_i.write("1");
        wait(1, SC_NS);
        rst_i.write("0");
        wait(1, SC_NS);
    }
    void ack(){
        while(true){
            ack_i.write("0");
            while(val_o.read()!="1"){
                wait(1,SC_NS);
            }
            wait(1, SC_NS);
            ack_i.write("1");
            while(val_o.read()!="0"){
                wait(1,SC_NS);
            }
            wait(1,SC_NS);
        }
        
        
    }

    SC_CTOR(flow_out_tb){
        sensitive << clk_i;
        SC_THREAD(logic);
        SC_THREAD(reset);
        SC_THREAD(ack);
    }
};