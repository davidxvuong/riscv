#include "Vtb_top_verilator.h"
#include "verilated_vcd_c.h"
#include "verilated.h"

static vluint64_t t = 0;

int main(int argc, char **argv, char **env)
{
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    Vtb_top_verilator *top = new Vtb_top_verilator;

    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("tb_verilator.vcd");
    top->fetch_enable_i = 1;
    top->clk_i = 0;
    top->rst_ni = 0;
    while (!Verilated::gotFinish()) {
        if (t > 200)
            top->rst_ni = 1;
        top->clk_i = !top->clk_i;
        top->eval();
        tfp->dump(t);
        t += 5;
    }
    tfp->close();
    delete top;
    exit(0);
}

double sc_time_stamp()
{
    return t;
}
