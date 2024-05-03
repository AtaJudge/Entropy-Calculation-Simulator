#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10

double entropy_calculator(int[N]);

void display_entropy(int[N], double);


int main() {
    srand(time(NULL));

    int bucket[N];
    double entropy;

    for (int i = 0; i < N; i++) {
        bucket[i] = 1 + rand() % 6;
    }

    entropy = entropy_calculator(bucket);
    display_entropy(bucket, entropy);

    return 0;
}


double entropy_calculator(int system[N]) {
    int col_occur[6]; /* Array to track how many times each colour
                       occurred in the bucket.
                       */
    double entropy = 0.0;

    for (int i = 0; i < 6; i++) {
        col_occur[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        if (system[i] == 1)
            col_occur[0]++;
        else if (system[i] == 2)
            col_occur[1]++;
        else if (system[i] == 3)
            col_occur[2]++;
        else if (system[i] == 4)
            col_occur[3]++;
        else if (system[i] == 5)
            col_occur[4]++;
        else if (system[i] == 6)
            col_occur[5]++;
        else
            printf("\nInvalid color detected!");
    }

    for (int i = 0; i < 6; i++) {
        if (*(col_occur + i) == 0) {
            printf("\nCan't calculate entropy, please try again.");
            exit(1);
        } else {
            entropy += (col_occur[i] * 1.0 / N) * (log10(col_occur[i] * 1.0 / N) / log10(2));
        }

    }

    return entropy * -1.0;
}


void display_entropy(int system[N], double entropy) {
    printf("\nWith %d samples, you have the following balls in the bucket:", N);

    printf("\n{");
    for (int i = 0; i < N; i++) {
        if (i == N - 1)
            printf("%d}", system[i]);
        else
            printf("%d, ", system[i]);
    }

    printf("\nAnd the entropy is = %.2lf", entropy);
}