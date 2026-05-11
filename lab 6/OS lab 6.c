#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
int id;
int execution;
int period;
int remaining;
int deadline;
int weight; // for proportional scheduling
} Task;

Task tasks[MAX_TASKS];
int n, sim_time;

// Reset tasks before each algorithm
void reset_tasks() {
for (int i = 0; i < n; i++) {
tasks[i].remaining = 0;
tasks[i].deadline = tasks[i].period;
}
}

/* ---------------- RATE MONOTONIC ---------------- */
void rate_monotonic() {
printf("\n--- Rate Monotonic Scheduling ---\n");
reset_tasks();

for (int t = 0; t < sim_time; t++) {

// Release tasks
for (int i = 0; i < n; i++) {
if (t % tasks[i].period == 0) {
tasks[i].remaining = tasks[i].execution;
}
}

int selected = -1;

// Select task with smallest period
for (int i = 0; i < n; i++) {
if (tasks[i].remaining > 0) {
if (selected == -1 ||
tasks[i].period < tasks[selected].period) {
selected = i;
}
}
}

if (selected != -1) {
printf("Time %d: Task %d\n", t, tasks[selected].id);
tasks[selected].remaining--;
} else {
printf("Time %d: Idle\n", t);
}
}
}

/* ---------------- EDF ---------------- */
void earliest_deadline_first() {
printf("\n--- Earliest Deadline First ---\n");

reset_tasks();

for (int t = 0; t < sim_time; t++) {

// Release tasks
for (int i = 0; i < n; i++) {
if (t % tasks[i].period == 0) {
tasks[i].remaining = tasks[i].execution;
tasks[i].deadline = t + tasks[i].period;
}
}

int selected = -1;

// Select task with earliest deadline
for (int i = 0; i < n; i++) {
if (tasks[i].remaining > 0) {
if (selected == -1 ||
tasks[i].deadline < tasks[selected].deadline) {
selected = i;
}
}
}

if (selected != -1) {
printf("Time %d: Task %d\n", t, tasks[selected].id);
tasks[selected].remaining--;
} else {
printf("Time %d: Idle\n", t);
}
}

}

/* ---------------- PROPORTIONAL ---------------- */
void proportional_scheduling() {
printf("\n--- Proportional Scheduling ---\n");
reset_tasks();

int total_weight = 0;
for (int i = 0; i < n; i++)
total_weight += tasks[i].weight;

int current = 0;

for (int t = 0; t < sim_time; t++) {

int count = 0;
while (count < n) {
int i = current % n;

if (tasks[i].remaining <= 0) {
tasks[i].remaining = tasks[i].execution;
}

if (tasks[i].remaining > 0) {
printf("Time %d: Task %d\n", t, tasks[i].id);
tasks[i].remaining--;
current = (i + 1) % n;
break;
}

current++;

count++;
}
}
}

/* ---------------- MAIN ---------------- */
int main() {
printf("Enter number of tasks: ");
scanf("%d", &n);

for (int i = 0; i < n; i++) {
tasks[i].id = i + 1;
printf("\nTask %d:\n", i + 1);
printf("Execution time: ");
scanf("%d", &tasks[i].execution);
printf("Period: ");
scanf("%d", &tasks[i].period);
printf("Weight (for proportional): ");
scanf("%d", &tasks[i].weight);
}

printf("\nEnter simulation time: ");
scanf("%d", &sim_time);

rate_monotonic();
earliest_deadline_first();
proportional_scheduling();

return 0;
}
