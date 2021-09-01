#include "flow_in.h"

#define data_width_p 8

SC_MODULE(flow_in_tb){

    sc_in_clk clk_i;
    sc_out<sc_bv<1>> rst_i, val_i, wok_i;
    sc_in<sc_bv<1>> ack_o, wr_o;
    sc_out<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<data_width_p>> data_o;

    void logic(){
        sc_bv<data_width_p> words[10] = {"00000001","00000011","00000111","00001111","00011111","00111111","01111111","11111111"};
        for(int i=0; i<10; i++){
        wait(1, SC_NS);
        data_i.write(words[i]);
        wok_i.write("1");
        wait(1, SC_NS);
        wok_i.write("0");
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

    SC_CTOR(flow_in_tb){
        sensitive << clk_i;
        SC_THREAD(logic);
        SC_THREAD(reset);
        SC_THREAD(ack);
    }
};