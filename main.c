#include <stdio.h>
#include <stdlib.h>

struct Patient {
    char id;
    int arrival_time;
    int treatment_time;
    int urgency_level;
};

void swap(struct Patient* a, struct Patient* b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

void FCFS(struct Patient patients[], int n) {
    printf("FCFS Scheduling:\n");
    printf("Order of Patients: ");
    
    for (int i = 0; i < n; i++) {
        printf("%c ", patients[i].id);
    }
    printf("\n");
}

void SJF(struct Patient patients[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (patients[j].treatment_time > patients[j + 1].treatment_time) {
                swap(&patients[j], &patients[j + 1]);
            }
        }
    }

    FCFS(patients, n);
}

void PriorityScheduling(struct Patient patients[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (patients[j].urgency_level > patients[j + 1].urgency_level) {
                swap(&patients[j], &patients[j + 1]);
            }
        }
    }

    FCFS(patients, n);
}

void RoundRobin(struct Patient patients[], int n, int time_quantum) {
    int remaining_patients = n;
    int current_time = 0;
    
    printf("Round Robin Scheduling (Time Quantum: %d):\n", time_quantum);
    printf("Order of Patients: ");
    
    while (remaining_patients > 0) {
        for (int i = 0; i < n; i++) {
            if (patients[i].treatment_time > 0) {
                printf("%c ", patients[i].id);
                if (patients[i].treatment_time <= time_quantum) {
                    current_time += patients[i].treatment_time;
                    patients[i].treatment_time = 0;
                    remaining_patients--;
                } else {
                    current_time += time_quantum;
                    patients[i].treatment_time -= time_quantum;
                }
            }
        }
    }
    printf("\n");
}

int main() {
    int n = 4;
    struct Patient patients[n];

    // Initialize patient data
    patients[0].id = 'A';
    patients[0].arrival_time = 0;
    patients[0].treatment_time = 30;
    patients[0].urgency_level = 3;

    patients[1].id = 'B';
    patients[1].arrival_time = 10;
    patients[1].treatment_time = 20;
    patients[1].urgency_level = 5;

    patients[2].id = 'C';
    patients[2].arrival_time = 15;
    patients[2].treatment_time = 40;
    patients[2].urgency_level = 2;

    patients[3].id = 'D';
    patients[3].arrival_time = 20;
    patients[3].treatment_time = 15;
    patients[3].urgency_level = 4;

    FCFS(patients, n);
    printf("\n");
    SJF(patients, n);
    printf("\n");
    PriorityScheduling(patients, n);
    printf("\n");
    RoundRobin(patients, n, 15);

    return 0;
}
