#include <stdio.h>

void fcfs(int n, int at[], int bt[], int ct[], int tat[], int wt[], int start_time) {
    int time = start_time;

    for(int i = 0; i < n; i++) {
        if(time < at[i])
            time = at[i];

        time += bt[i];
        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

int main() {
    int n, i;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], type[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for(i = 0; i < n; i++) {
        scanf("%d %d", &at[i] ,&bt[i]);
    }     

    printf("Enter Process Type (1 = System, 0 = User):\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &type[i]);
    }

    // Separate queues
    int sys_at[n], sys_bt[n], user_at[n], user_bt[n];
    int sys_index[n], user_index[n];
    int sys_n = 0, user_n = 0;

    for(i = 0; i < n; i++) {
        if(type[i] == 1) {
            sys_at[sys_n] = at[i];
            sys_bt[sys_n] = bt[i];
            sys_index[sys_n] = i;
            sys_n++;
        } else {
            user_at[user_n] = at[i];
            user_bt[user_n] = bt[i];
            user_index[user_n] = i;
            user_n++;
        }
    }

    // Arrays for results
    int ct[n], tat[n], wt[n];

    // Process system queue first
    int sys_ct[sys_n], sys_tat[sys_n], sys_wt[sys_n];
    fcfs(sys_n, sys_at, sys_bt, sys_ct, sys_tat, sys_wt, 0);

    // Last completion time of system queue
    int last_time = (sys_n > 0) ? sys_ct[sys_n - 1] : 0;

    // Process user queue after system queue
    int user_ct[user_n], user_tat[user_n], user_wt[user_n];
    fcfs(user_n, user_at, user_bt, user_ct, user_tat, user_wt, last_time);

    // Merge results back
    for(i = 0; i < sys_n; i++) {
        int idx = sys_index[i];
        ct[idx] = sys_ct[i];
        tat[idx] = sys_tat[i];
        wt[idx] = sys_wt[i];
    }

    for(i = 0; i < user_n; i++) {
        int idx = user_index[i];
        ct[idx] = user_ct[i];
        tat[idx] = user_tat[i];
        wt[idx] = user_wt[i];
    }

    // Output
    float total_tat = 0, total_wt = 0;

    printf("\nP\tAT\tBT\tType\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%s\t%d\t%d\t%d\n",
               i+1, at[i], bt[i],
               (type[i] == 1) ? "SYS" : "USR",
               ct[i], tat[i], wt[i]);

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);

    return 0;
}