#include "systemc.h"


enum ifc_fsm {
	ifcs0, ifcs1, ifcs2, ifcs3, ifcs4, ifcs5, ifcs6, ifcs7
};
template <int data_width_p>
struct flow_in: sc_module{
    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i, val_i, wok_i;
    sc_out<sc_bv<1>> ack_o, wr_o;
    sc_in<sc_bv<data_width_p>> data_i;
    sc_out<sc_bv<data_width_p>> data_o;
    sc_signal<ifc_fsm> state;

    void flow_in_logic(){
        if(rst_i.read() != "1" && clk_i.posedge()){
            switch(state){
                case ifcs0:
                wr_o.write("0");
                ack_o.write("0");
                if(val_i.read() == "1" and wok_i.read() == "1"){
                    state.write(ifcs1);
                } else {
                    state.write(ifcs0);
                }
                break;
                case ifcs1:
                ack_o.write("1");
                wr_o.write("1");
                if(val_i.read() == "0"){
                    state.write(ifcs0);
                } else {
                    state.write(ifcs2);
                }
                break;
                case ifcs2:
                ack_o.write("1");
                wr_o.write("0");
                if(val_i.read() == "0"){
                    state.write(ifcs0);
                } else {
                    state.write(ifcs2);
                } 
                break;
                default:
                    wr_o.write("0");
                    ack_o.write("0");
                    state.write(ifcs0);
                    break;

            }
        }
        data_o.write(data_i.read());
    }

    SC_CTOR(flow_in){
        SC_METHOD(flow_in_logic);
        sensitive << clk_i << rst_i << val_i << wok_i << data_i;
    }




};