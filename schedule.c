#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
    int n = 5; // Number of child processes
    int i;
    struct proc_stat stats[n];

    for (i = 0; i < n; i++) {
    int pid = fork();
    if (pid == 0) {
        // Child process
        char *args[3];
        if (i % 2 == 0) {
            // Call uniq uniqexample.txt
            args[0] = "uniq";
            args[1] = "uniqexample.txt";
            args[2] = 0;
            exec(args[0], args);
        } else {
            // Call kuniq uniqexample.txt
            args[0] = "kuniq";
            args[1] = "uniqexample.txt";
            args[2] = 0;
            exec(args[0], args);
        }
        exit();
    } else {
        // Parent process
        wait();
        getprocinfo(pid, &stats[i]);
    }
}


    // Calculate and report average wait and turnaround times
    int total_wait_time = 0;
    int total_turnaround_time = 0;

    for (i = 0; i < n; i++) {
        total_wait_time += (stats[i].start_time - stats[i].total_time);
        total_turnaround_time += (stats[i].start_time);
    }

    printf(1, "Average Wait Time: %d\n", total_wait_time / n);
    printf(1, "Average Turnaround Time: %d\n", total_turnaround_time / n);

    exit();
}
