#include "system.h"
#include "systemc.h"

#define WIDTH  8



int sc_main(int argc, char* argv[]) {
    fifo_ring fifo("fifo");

    sc_signal<sc_bv<WIDTH> >w_data_i,w_data_o;
    sc_signal<sc_bv<1>> w_rst, w_rd_i, w_wr_i, w_rok_o, w_wok_o;
    sc_clock clk;
    sc_uint<4> teste;
    teste = 0b0110;
    cout << teste;

    fifo.data_i(w_data_i);
    fifo.data_o(w_data_o);
    fifo.rst_i(w_rst);
    fifo.rd_i(w_rd_i);
    fifo.wr_i(w_wr_i);
    fifo.rok_o(w_rok_o);
    fifo.wok_o(w_wok_o);
    fifo.clk_i(clk);

    fifo_tb tb("tb");
    tb.data_i(w_data_i);
    tb.data_o(w_data_o);
    tb.rst_i(w_rst);
    tb.rd_i(w_rd_i);
    tb.wr_i(w_wr_i);
    tb.rok_o(w_rok_o);
    tb.wok_o(w_wok_o);
    tb.clk_i(clk);

    sc_trace_file *wf = sc_create_vcd_trace_file("fifo");

    sc_trace(wf, w_data_i, "w_input");
    sc_trace(wf, w_data_o, "w_output");
    sc_trace(wf, w_rst, "w_rst");
    sc_trace(wf, w_rd_i, "w_rd_i");
    sc_trace(wf, w_wr_i, "w_wr_i");
    sc_trace(wf, w_rok_o, "w_rok_o");
    sc_trace(wf, w_wok_o, "w_wok_o");
    sc_trace(wf, clk, "clk");


    sc_start();

    sc_close_vcd_trace_file(wf);

    /*
    sc_signal<sc_bv<WIDTH> >w_data_i,w_data_o;
    sc_signal<sc_bv<1>> w_rst, w_rd_i, w_wr_i, w_rok_o, w_wok_o;
    sc_clock clk;

    fifo_shift fifo("fifo_shift");

    sc_trace_file *wf = sc_create_vcd_trace_file("fifo");

    fifo.data_i(w_data_i);
    fifo.data_o(w_data_o);
    fifo.rst_i(w_rst);
    fifo.rd_i(w_rd_i);
    fifo.wr_i(w_wr_i);
    fifo.rok_o(w_rok_o);
    fifo.wok_o(w_wok_o);
    fifo.clk_i(clk);

    sc_trace(wf, w_data_i, "w_input");
    sc_trace(wf, w_data_o, "w_output");
    sc_trace(wf, w_rst, "w_rst");
    sc_trace(wf, w_rd_i, "w_rd_i");
    sc_trace(wf, w_wr_i, "w_wr_i");
    sc_trace(wf, w_rok_o, "w_rok_o");
    sc_trace(wf, w_wok_o, "w_wok_o");
    sc_trace(wf, clk, "clk");


    sc_bv<WIDTH> words[10] = {"00000001", "00000011", "00000111", "00001111", "00011111", "00111111", "01111111", "11111111", "11111110", "11111100"};

    //sc_start(0.5, SC_NS);
    w_rst.write("1");
    sc_start(1,SC_NS);
    w_rst.write("0");
    sc_start(1,SC_NS);
    w_wr_i.write("0");
    w_rd_i.write("0");
    w_data_i.write("00000000");
    sc_start(1,SC_NS);

    for(int i=0; i<10; i++){
        if(w_wok_o.read()=="1"){
            w_data_i.write(words[i]);
            w_wr_i.write("1");
            sc_start(1,SC_NS);
        }
        if(w_rok_o.read()=="1"){
            w_rd_i.write("1");
            sc_start(1,SC_NS);
        }
        if(w_rok_o.read()=="0"){
            w_rd_i.write("0");
            sc_start(1,SC_NS);
        }
        w_wr_i.write("0");
        sc_start(1,SC_NS);
    }

    sc_stop();

     cout << "@ " << sc_time_stamp() <<" Terminating simulation\n" << endl;

    sc_close_vcd_trace_file(wf);
    */
    return 0;
}