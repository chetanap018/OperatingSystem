#include <stdio.h>

int main()
{
    int n, i, j, pos, temp;
    int at[20], bt[20], pr[20];
    int wt[20], tat[20], ct[20];
    int time = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter Arrival Time, Burst Time and Priority for P%d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
    }

    int completed = 0, visited[20] = {0};

    while(completed < n)
    {
        int highest = -1;
        int highest_pr = 9999;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && visited[i] == 0)
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
        }
        else
        {
            ct[highest] = time + bt[highest];
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];

            time = ct[highest];
            visited[highest] = 1;
            completed++;
        }
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
