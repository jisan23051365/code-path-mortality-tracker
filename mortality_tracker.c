#include "mortality_tracker.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ------------------------------------------------------------------ */
/* Internal helpers                                                     */
/* ------------------------------------------------------------------ */

/* Returns a pseudo-random double in [0.0, 1.0).
 * Dividing by (RAND_MAX + 1.0) keeps the upper bound exclusive so that
 * a failure_probability of exactly 1.0 always triggers a failure while
 * a probability of 0.0 never does. */
static double rand_unit(void)
{
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

/* ------------------------------------------------------------------ */
/* Public API                                                           */
/* ------------------------------------------------------------------ */

void simulation_init(SimulationState *state)
{
    if (!state) return;
    memset(state, 0, sizeof(*state));
}

int simulation_add_path(SimulationState *state, const char *name,
                        double failure_probability)
{
    if (!state || !name) return -1;
    if (state->num_paths >= MAX_CODE_PATHS) return -1;

    /* Clamp probability to a valid range */
    if (failure_probability < 0.0) failure_probability = 0.0;
    if (failure_probability > 1.0) failure_probability = 1.0;

    CodePath *p = &state->paths[state->num_paths];
    strncpy(p->name, name, MAX_PATH_NAME - 1);
    p->name[MAX_PATH_NAME - 1] = '\0';
    p->total_executions   = 0;
    p->failures           = 0;
    p->failure_probability = failure_probability;

    state->num_paths++;
    return 0;
}

int simulation_execute(SimulationState *state, int path_index)
{
    if (!state) return -1;
    if (path_index < 0 || path_index >= state->num_paths) return -1;

    CodePath *p = &state->paths[path_index];

    p->total_executions++;
    state->total_executions++;

    int failed = (rand_unit() < p->failure_probability) ? 1 : 0;
    if (failed) {
        p->failures++;
        state->total_failures++;
    }

    return failed;
}

void simulation_run(SimulationState *state, long iterations_per_path)
{
    if (!state || iterations_per_path <= 0) return;

    for (int i = 0; i < state->num_paths; i++) {
        for (long j = 0; j < iterations_per_path; j++) {
            simulation_execute(state, i);
        }
    }
}

double path_mortality_rate(const CodePath *path)
{
    if (!path || path->total_executions == 0) return 0.0;
    return (double)path->failures / (double)path->total_executions;
}

double overall_mortality_rate(const SimulationState *state)
{
    if (!state || state->total_executions == 0) return 0.0;
    return (double)state->total_failures / (double)state->total_executions;
}

void simulation_print_report(const SimulationState *state)
{
    if (!state) return;

    printf("============================================================\n");
    printf("         Software Reliability – Mortality Rate Report       \n");
    printf("============================================================\n");
    printf("%-30s %12s %10s %14s\n",
           "Code Path", "Executions", "Failures", "Mortality Rate");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < state->num_paths; i++) {
        const CodePath *p = &state->paths[i];
        printf("%-30s %12ld %10ld %13.2f%%\n",
               p->name,
               p->total_executions,
               p->failures,
               path_mortality_rate(p) * 100.0);
    }

    printf("------------------------------------------------------------\n");
    printf("%-30s %12ld %10ld %13.2f%%\n",
           "OVERALL",
           state->total_executions,
           state->total_failures,
           overall_mortality_rate(state) * 100.0);
    printf("============================================================\n");
}
