#include <stdlib.h>
#include "VCounter.h"
#include <verilated.h>
#include <verilated_vcd_c.h>

const char* VCD_FILENAME = "counter_trace.vcd";

int main(int argc, char **argv){
    // initialise Verilator's variables
    Verilated::commandArgs(argc, argv);

    // initialise Verilator's Tracing
    Verilated::traceEverOn(true);

    // create an instance of the module under test
    VCounter* counter = new VCounter;

    // create an instance of Trace
    VerilatedVcdC* trace = new VerilatedVcdC;
    counter->trace(trace, 99);
    trace->open(VCD_FILENAME);

    printf("reset clock to 0\n");
    counter->i_clk = 0;
    counter->eval();

    // Tick the clock several times and output the value of the counter
    for (int i=0; i<10; i++) {
        counter->i_clk = 1;
        counter->eval();
        printf("clock at [%i] posedge => [%d]\n", i, counter->o_value);

        trace->dump(2 * i);

        counter->i_clk = 0;
        counter->eval();
        printf("clock at [%i] negedge => [%d]\n", i, counter->o_value);

        trace->dump((2 * i) + 1);

        // why is this required? 
        // ... so that assert() can be used?
        trace->flush();
    }

    // finish generating trace
    trace->close();

    exit(0);
}