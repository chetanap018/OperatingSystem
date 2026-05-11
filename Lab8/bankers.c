#include <stdio.h>

int main() {
    int n, m, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], finish[n], safe[n];

    // Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Maximum Matrix
    printf("Enter Maximum Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < n; i++) {
        finish[i] = 0;

        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;

    while(count < n) {

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }

                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                }
            }
        }
    }

    // Output
    if(count == n) {
        printf("\nSafe Sequence:\n");

        for(i = 0; i < n; i++) {
            printf("P%d ", safe[i]);
        }
    }
    else {
        printf("\nSystem is not safe");
    }

    return 0;
}
