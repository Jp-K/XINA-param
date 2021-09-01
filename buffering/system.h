#include "systemc.h"
#include "buffering.h"
#include "fifo_tb.h"

SC_MODULE(systemm){
    buffering<WIDTH, DEPTH> *fifo;
    fifo_tb *tb;

    sc_signal<sc_bv<WIDTH> >w_data_i,w_data_o;
    sc_signal<sc_bv<1>> w_rst, w_rd_i, w_wr_i, w_rok_o, w_wok_o;
    sc_clock clk;

    SC_CTOR(systemm){
        fifo = new buffering<WIDTH, DEPTH>("fifo");
        fifo->data_i(w_data_i);
        fifo->data_o(w_data_o);
        fifo->rst_i(w_rst);
        fifo->rd_i(w_rd_i);
        fifo->wr_i(w_wr_i);
        fifo->rok_o(w_rok_o);
        fifo->wok_o(w_wok_o);
        fifo->clk_i(clk);
        tb = new fifo_tb("tb");
        tb->data_i(w_data_i);
        tb->data_o(w_data_o);
        tb->rst_i(w_rst);
        tb->rd_i(w_rd_i);
        tb->wr_i(w_wr_i);
        tb->rok_o(w_rok_o);
        tb->wok_o(w_wok_o);
        tb->clk_i(clk);
    }
};
