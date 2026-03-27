#include "mortality_tracker.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Demonstration simulation:
 *
 * Five representative code paths are registered, each with a different
 * inherent failure probability.  The simulation runs 10 000 executions
 * per path and then prints a mortality-rate report.
 */

int main(void)
{
    /* Seed the PRNG once at program start */
    srand((unsigned int)time(NULL));

    SimulationState state;
    simulation_init(&state);

    /* Register code paths: (name, failure_probability) */
    simulation_add_path(&state, "Authentication Module",   0.02);
    simulation_add_path(&state, "Database Query Handler",  0.05);
    simulation_add_path(&state, "File I/O Processor",      0.08);
    simulation_add_path(&state, "Network Request Handler", 0.12);
    simulation_add_path(&state, "Memory Allocation Path",  0.03);

    /* Run 10 000 iterations per code path */
    const long ITERATIONS_PER_PATH = 10000;
    simulation_run(&state, ITERATIONS_PER_PATH);

    /* Display the results */
    simulation_print_report(&state);

    return EXIT_SUCCESS;
}
