#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =========================================================
   CODE PATH MORTALITY TRACKER
   ========================================================= */

typedef struct {
    char path_name[50];
    int executions;
    int failures;
} CodePath;

void logEvent(const char *msg) {
    FILE *fp = fopen("cpmt_logs.txt", "a");
    if (!fp) return;

    time_t now = time(NULL);
    fprintf(fp, "%s - %s\n", ctime(&now), msg);
    fclose(fp);
}

void simulatePath(CodePath *p, int fail) {
    p->executions++;

    if (fail) {
        p->failures++;
        logEvent("Path failed.");
    } else {
        logEvent("Path succeeded.");
    }
}

void printStats(CodePath p) {
    printf("\nPath: %s\n", p.path_name);
    printf("Executions: %d\n", p.executions);
    printf("Failures: %d\n", p.failures);

    double mortality = 0.0;
    if (p.executions > 0)
        mortality = (100.0 * p.failures) / p.executions;

    printf("Mortality Rate: %.2f%%\n", mortality);
}

int main() {
    CodePath authPath = {"Authentication Path", 0, 0};
    CodePath transactionPath = {"Transaction Path", 0, 0};

    simulatePath(&authPath, 0);
    simulatePath(&authPath, 1);
    simulatePath(&transactionPath, 0);
    simulatePath(&transactionPath, 0);

    printStats(authPath);
    printStats(transactionPath);

    return 0;
}