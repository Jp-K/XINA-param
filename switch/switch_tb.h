#include "switch.h"

#define data_width_p 8

struct sc_switch_tb : sc_module {
    sc_signal<sc_bv<4>> sel_i;
    sc_signal<sc_bv<data_width_p>> data3_i, data2_i, data1_i, data0_i;
    sc_signal<sc_bv<data_width_p>> data_o;
    sc_switch<data_width_p+1> *sw0;

    void logic(){
        sel_i.write("1000");
        data0_i.write("01100110");
        data1_i.write("01111110");
        data2_i.write("00000110");
        data3_i.write("11100111");
        wait(5, SC_NS);
        sel_i.write("0100");
        wait(5, SC_NS);
        sel_i.write("0001");
        wait(5, SC_NS);
        sel_i.write("0010");
        wait(5, SC_NS);
        sel_i.write("0100");
        wait(5, SC_NS);
        sc_stop();
    }

    SC_CTOR(sc_switch_tb){
        SC_THREAD(logic);
        sensitive << sel_i, data3_i, data2_i, data1_i, data0_i;

        sw0 = new sc_switch<data_width_p+1>("tb");
        sw0->data0_i(data0_i);
        sw0->data1_i(data1_i);
        sw0->data2_i(data2_i);
        sw0->data3_i(data3_i);
        sw0->sel_i(sel_i);
        sw0->data_o(data_o);

        sc_trace_file *wf = sc_create_vcd_trace_file("switch_tb");

        sc_trace(wf, data0_i, "data0");
        sc_trace(wf, data1_i, "data1");
        sc_trace(wf, data2_i, "data2");
        sc_trace(wf, data3_i, "data3");
        sc_trace(wf, data_o, "data_o");
        sc_trace(wf, sel_i, "sel");
    }
};