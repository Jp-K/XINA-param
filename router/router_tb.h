#include <systemc.h>
#include "router.h"

#define x_id_p 0
#define y_id_p 1
#define data_width_p 8
SC_MODULE(router_tb){

    sc_clock clk_i;
    sc_signal<sc_bv<1>> rst_i;

    sc_signal<sc_bv<data_width_p>> l_in_data_i;
    sc_signal<sc_bv<1>> l_in_val_i;
    sc_signal<sc_bv<1>> l_in_ack_o;
    sc_signal<sc_bv<data_width_p>> l_out_data_o;
    sc_signal<sc_bv<1>> l_out_val_o;
    sc_signal<sc_bv<1>> l_out_ack_i;
    sc_signal<sc_bv<data_width_p>> n_in_data_i;
    sc_signal<sc_bv<1>> n_in_val_i;
    sc_signal<sc_bv<1>> n_in_ack_o;
    sc_signal<sc_bv<data_width_p>> n_out_data_o;
    sc_signal<sc_bv<1>> n_out_val_o;
    sc_signal<sc_bv<1>> n_out_ack_i;
    sc_signal<sc_bv<data_width_p>> e_in_data_i;
    sc_signal<sc_bv<1>> e_in_val_i;
    sc_signal<sc_bv<1>> e_in_ack_o;
    sc_signal<sc_bv<data_width_p>> e_out_data_o;
    sc_signal<sc_bv<1>> e_out_val_o;
    sc_signal<sc_bv<1>> e_out_ack_i;
    sc_signal<sc_bv<data_width_p>> s_in_data_i;
    sc_signal<sc_bv<1>> s_in_val_i;
    sc_signal<sc_bv<1>> s_in_ack_o;
    sc_signal<sc_bv<data_width_p>> s_out_data_o;
    sc_signal<sc_bv<1>> s_out_val_o;
    sc_signal<sc_bv<1>> s_out_ack_i;
    sc_signal<sc_bv<data_width_p>> w_in_data_i;
    sc_signal<sc_bv<1>> w_in_val_i;
    sc_signal<sc_bv<1>> w_in_ack_o;
    sc_signal<sc_bv<data_width_p>> w_out_data_o;
    sc_signal<sc_bv<1>> w_out_val_o;
    sc_signal<sc_bv<1>> w_out_ack_i;

    router<x_id_p, y_id_p, data_width_p> *router0;

    void rst(){
        rst_i.write("1");
        wait(1, SC_NS);
        rst_i.write("0");
        wait(1, SC_NS);
    }

    void in(){
        sc_bv<data_width_p> pack_n[4] = {"11111111", "00000100", "00010000", "10000000"};
        sc_bv<data_width_p> pack_n2[4] = {"10000000", "00000100", "00010000", "10000000"};
        l_in_val_i.write("0");
            wait(1, SC_NS);
        for(int i=0; i<4; i++){
            l_in_val_i.write("0");
            l_in_data_i.write(pack_n[i]);
            wait(1, SC_NS);
            l_in_val_i.write("1");
            while(l_in_ack_o.read() != "1"){
                wait(1, SC_NS);
            }
            l_in_val_i.write("0");
            while(l_in_ack_o.read() != "0"){
                wait(1, SC_NS);
            }
        }


        l_in_data_i.write("00000000");
        l_in_val_i.write("0");
            wait(1, SC_NS);
        for(int i=0; i<4; i++){
            l_in_val_i.write("0");
            l_in_data_i.write(pack_n2[i]);
            wait(1, SC_NS);
            l_in_val_i.write("1");
            while(l_in_ack_o.read() != "1"){
                wait(1, SC_NS);
            }
            l_in_val_i.write("0");
            while(l_in_ack_o.read() != "0"){
                wait(1, SC_NS);
            }
        }
        l_in_val_i.write("0");
        l_in_data_i.write("00000000");
        wait(50, SC_NS);
        sc_stop();
    }

    void e_o(){
        while(true){
            e_out_ack_i.write("0");
            wait(1, SC_NS);
            while (e_out_val_o.read() != "1")
            {
                wait(1, SC_NS);
            }
            e_out_ack_i.write("1");
            wait(1, SC_NS);
            while (e_out_val_o.read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    void s_o(){
        while(true){
            s_out_ack_i.write("0");
            while (s_out_val_o.read() != "1")
            {
                wait(1, SC_NS);
            }
            s_out_ack_i.write("1");
            wait(1, SC_NS);
            while (s_out_val_o.read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    void n_o(){
        while(true){
            n_out_ack_i.write("0");
            while (n_out_val_o.read() != "1")
            {
                wait(1, SC_NS);
            }
            n_out_ack_i.write("1");
            wait(1, SC_NS);
            while (n_out_val_o.read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    void w_o(){
        while(true){
            w_out_ack_i.write("0");
            while (w_out_val_o.read() != "1")
            {
                wait(1, SC_NS);
            }
            w_out_ack_i.write("1");
            wait(1, SC_NS);
            while (w_out_val_o.read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    void l_o(){
        while(true){
            l_out_ack_i.write("0");
            while (l_out_val_o.read() != "1")
            {
                wait(1, SC_NS);
            }
            l_out_ack_i.write("1");
            wait(1, SC_NS);
            while (l_out_val_o.read() != "0")
            {
                wait(1, SC_NS);
            }
        }
    }

    SC_CTOR(router_tb){
        
        SC_THREAD(n_o);
        SC_THREAD(e_o);
        SC_THREAD(s_o);
        SC_THREAD(w_o);
        SC_THREAD(l_o);
        SC_THREAD(in);
        SC_THREAD(rst);
        sensitive << clk_i << rst_i;

        router0 = new router<x_id_p, y_id_p, data_width_p>("router");

        router0->clk_i(clk_i);  
        router0->rst_i(rst_i);     
        router0->l_in_data_i(l_in_data_i);
        router0->l_in_val_i(l_in_val_i);
        router0->l_in_ack_o(l_in_ack_o);
        router0->l_out_data_o(l_out_data_o);
        router0->l_out_val_o(l_out_val_o);
        router0->l_out_ack_i(l_out_ack_i);
        router0->n_in_data_i(n_in_data_i);
        router0->n_in_val_i(n_in_val_i);
        router0->n_in_ack_o(n_in_ack_o);
        router0->n_out_data_o(n_out_data_o);
        router0->n_out_val_o(n_out_val_o);
        router0->n_out_ack_i(n_out_ack_i);
        router0->e_in_data_i(e_in_data_i);
        router0->e_in_val_i(e_in_val_i);
        router0->e_in_ack_o(e_in_ack_o);
        router0->e_out_data_o(e_out_data_o);
        router0->e_out_val_o(e_out_val_o);
        router0->e_out_ack_i(e_out_ack_i);
        router0->s_in_data_i(s_in_data_i);
        router0->s_in_val_i(s_in_val_i);
        router0->s_in_ack_o(s_in_ack_o);
        router0->s_out_data_o(s_out_data_o);
        router0->s_out_val_o(s_out_val_o);
        router0->s_out_ack_i(s_out_ack_i);
        router0->w_in_data_i(w_in_data_i);
        router0->w_in_val_i(w_in_val_i);
        router0->w_in_ack_o(w_in_ack_o);
        router0->w_out_data_o(w_out_data_o);
        router0->w_out_val_o(w_out_val_o);
        router0->w_out_ack_i(w_out_ack_i);

        sc_trace_file *wf = sc_create_vcd_trace_file("router_tb");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");

        sc_trace(wf, l_in_data_i, "l_in_data_i");
        sc_trace(wf, l_in_val_i,  "l_in_val_i");
        sc_trace(wf, l_in_ack_o,  "l_in_ack_o");
        sc_trace(wf, l_out_data_o,"l_out_data_o");
        sc_trace(wf, l_out_val_o, "l_out_val_o");
        sc_trace(wf, l_out_ack_i, "l_out_ack_i");

        sc_trace(wf, n_in_data_i, "n_in_data_i");
        sc_trace(wf, n_in_val_i,  "n_in_val_i");
        sc_trace(wf, n_in_ack_o,  "n_in_ack_o");
        sc_trace(wf, n_out_data_o,"n_out_data_o");
        sc_trace(wf, n_out_val_o, "n_out_val_o");
        sc_trace(wf, n_out_ack_i, "n_out_ack_i");

        sc_trace(wf, e_in_data_i, "e_in_data_i");
        sc_trace(wf, e_in_val_i,  "e_in_val_i");
        sc_trace(wf, e_in_ack_o,  "e_in_ack_o");
        sc_trace(wf, e_out_data_o,"e_out_data_o");
        sc_trace(wf, e_out_val_o, "e_out_val_o");
        sc_trace(wf, e_out_ack_i, "e_out_ack_i");

        sc_trace(wf, s_in_data_i, "s_in_data_i");
        sc_trace(wf, s_in_val_i,  "s_in_val_i");
        sc_trace(wf, s_in_ack_o,  "s_in_ack_o");
        sc_trace(wf, s_out_data_o,"s_out_data_o");
        sc_trace(wf, s_out_val_o, "s_out_val_o");
        sc_trace(wf, s_out_ack_i, "s_out_ack_i");

        sc_trace(wf, w_in_data_i, "w_in_data_i");
        sc_trace(wf, w_in_val_i,  "w_in_val_i");
        sc_trace(wf, w_in_ack_o,  "w_in_ack_o");
        sc_trace(wf, w_out_data_o,"w_out_data_o");
        sc_trace(wf, w_out_val_o, "w_out_val_o");
        sc_trace(wf, w_out_ack_i, "w_out_ack_i");


    }
};