#include <stdio.h>
#include <limits.h>

int main()
{
    int n, i, time = 0, smallest;
    int bt[20], at[20], rt[20];
    int ct[20], wt[20], tat[20];
    int count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];   // remaining time
    }

    rt[19] = INT_MAX;   // sentinel

    while(count != n)
    {
        smallest = 19;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0)
                smallest = i;
        }

        rt[smallest]--;

        if(rt[smallest] == 0)
        {
            count++;
            ct[smallest] = time + 1;

            tat[smallest] = ct[smallest] - at[smallest];
            wt[smallest] = tat[smallest] - bt[smallest];

            if(wt[smallest] < 0)
                wt[smallest] = 0;
        }

        time++;
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    return 0;
}
