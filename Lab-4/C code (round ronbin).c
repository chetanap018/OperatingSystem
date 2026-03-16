#include <stdio.h>

int main()
{
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n];
    int wt[n], tat[n], ct[n];

    // Input arrival and burst time
    for(int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time of P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];   // Remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    while(completed < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            // Process is ready and not finished
            if(at[i] <= time && rt[i] > 0)
            {
                found = 1;

                if(rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    ct[i] = time;
                    rt[i] = 0;
                    completed++;
                }
            }
        }

        // If no process is ready, move time forward
        if(found == 0)
            time++;
    }

    float total_wt = 0, total_tat = 0;

    // Calculate WT and TAT
    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Output table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
