#ifndef MORTALITY_TRACKER_H
#define MORTALITY_TRACKER_H

#include <stddef.h>

#define MAX_CODE_PATHS 16
#define MAX_PATH_NAME  64

/* Represents a single software code path being tracked */
typedef struct {
    char   name[MAX_PATH_NAME]; /* descriptive name of the code path */
    long   total_executions;    /* number of times this path was exercised */
    long   failures;            /* number of executions that resulted in failure */
    double failure_probability; /* probability [0.0, 1.0] that an execution fails */
} CodePath;

/* Holds the full simulation state */
typedef struct {
    CodePath paths[MAX_CODE_PATHS];
    int      num_paths;
    long     total_executions; /* sum across all paths */
    long     total_failures;   /* sum across all paths */
} SimulationState;

/* Initialise the simulation state */
void simulation_init(SimulationState *state);

/* Add a code path to the simulation.
 * Returns 0 on success, -1 if MAX_CODE_PATHS would be exceeded. */
int simulation_add_path(SimulationState *state, const char *name,
                        double failure_probability);

/* Execute a single code path by index.
 * Simulates a random execution and records success or failure.
 * Returns 1 if the execution failed, 0 if it succeeded, -1 on bad index. */
int simulation_execute(SimulationState *state, int path_index);

/* Run a batch of executions spread evenly across all registered paths.
 * 'iterations_per_path' executions are performed for each path. */
void simulation_run(SimulationState *state, long iterations_per_path);

/* Return the mortality rate (failure rate) for a single path.
 * Returns 0.0 if the path has never been executed. */
double path_mortality_rate(const CodePath *path);

/* Return the overall mortality rate across all paths.
 * Returns 0.0 if nothing has been executed yet. */
double overall_mortality_rate(const SimulationState *state);

/* Print a formatted report to stdout */
void simulation_print_report(const SimulationState *state);

#endif /* MORTALITY_TRACKER_H */
