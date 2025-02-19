#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILDREN 3

pid_t child_pids[NUM_CHILDREN];

void spawn_child(int index) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        printf("[Child %d] PID: %d, Parent PID: %d\n", index, getpid(), getppid());
        while (1) {
            sleep(2);
        }
        exit(0);
    } else if (pid > 0) {
        // Parent process
        child_pids[index] = pid;
    } else {
        perror("fork");
        exit(1);
    }
}

void handle_child_exit(int sig) {
    int status, i;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (i = 0; i < NUM_CHILDREN; i++) {
            if (child_pids[i] == pid) {
                printf("[Parent] Child %d (PID: %d) exited, respawning...\n", i, pid);
                spawn_child(i);
            }
        }
    }
}

void terminate_children() {
    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (child_pids[i] > 0) {
            printf("[Parent] Terminating child PID: %d\n", child_pids[i]);
            kill(child_pids[i], SIGTERM);
        }
    }
}

void handle_parent_exit(int sig) {
    printf("[Parent] Received SIGTERM, terminating children...\n");
    terminate_children();
    exit(0);
}

int main() {
    signal(SIGCHLD, handle_child_exit); // Handle child termination
    signal(SIGTERM, handle_parent_exit); // Handle parent termination
    printf("[Parent] PID: %d spawning %d children...\n", getpid(), NUM_CHILDREN);
    
    for (int i = 0; i < NUM_CHILDREN; i++) {
        spawn_child(i);
    }
    
    while (1) {
        sleep(5);
    }
    return 0;
}
