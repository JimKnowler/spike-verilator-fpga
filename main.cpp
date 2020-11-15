#include <stdlib.h>
#include "VCounter.h"
#include "verilated.h"

int main(int argc, char **argv){
    // initialise Verilator's variables
    Verilated::commandArgs(argc, argv);

    // create an instance of the module under test
    VCounter* counter = new VCounter;

    printf("reset clock to 0\n");
    counter->i_clk = 0;
    counter->eval();

    // Tick the clock several times and output the value of the counter
    for (int i=0; i<10; i++) {
        counter->i_clk = 1;
        counter->eval();
        printf("clock at [%i] posedge => [%d]\n", i, counter->o_value);

        counter->i_clk = 0;
        counter->eval();
        printf("clock at [%i] negedge => [%d]\n", i, counter->o_value);
    }

    exit(0);
}