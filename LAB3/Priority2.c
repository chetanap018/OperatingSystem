#include <stdio.h>
#include <limits.h>

int main()
{
    int n, i, time = 0, count = 0;
    int at[20], bt[20], pr[20], rt[20];
    int wt[20], tat[20], ct[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter Arrival Time, Burst Time and Priority for P%d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    while(count < n)
    {
        int highest = -1;
        int highest_pr = INT_MAX;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(pr[i] < highest_pr)
                {
                    highest_pr = pr[i];
                    highest = i;
                }
            }
        }

        if(highest == -1)
        {
            time++;
            continue;
        }

        rt[highest]--;

        if(rt[highest] == 0)
        {
            count++;
            ct[highest] = time + 1;
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];
        }

        time++;
    }

    printf("\nProcess\tAT\tBT\tPR\tWT\tTAT\n");

    for(i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
