#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double entropy_calculator(int *, int); // Function for calculating the entropy.

void display_entropy(int *, int, double); // Function for displaying contents of the bucket and entropy.


int main() {
    srand(time(NULL));

    int *bucket;
    int ball_num;
    double entropy;

    printf("\nPlease enter number of balls in the bucket. (N): ");
    scanf("%d", &ball_num);

    // Dynamic memory allocation for the bucket array with size of (N).
    bucket = (int *) malloc(sizeof(int) * ball_num);

    for (int i = 0; i < ball_num; i++) {
        *(bucket + i) = 1 + rand() % 6; // Put random colored "N" balls in the bucket.
    }

    entropy = entropy_calculator(bucket, ball_num); // Calculate entropy.
    display_entropy(bucket, ball_num, entropy); // Display.

    return 0;
}


double entropy_calculator(int *system, int size) {
    int col_occur[6]; /* Array to track how many times each colour
                       occurred in the bucket.
                       */
    double entropy = 0.0;

    for (int i = 0; i < 6; i++) { // Set the number of colors occurred to 0 for each color.
        col_occur[i] = 0;
    }

    for (int i = 0; i < size; i++) { // Check the color of the ball, increase the corresponding color by 1.
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
        /* If one of the colors is not in the bucket, entropy cannot be calculated.
         * In this case, exit(1) */
        if (col_occur[i] == 0) {
            printf("\nCan't calculate entropy, please try again.");
            exit(1);
        } else {
            entropy += (*(system + i) * 1.0 / size) * (log10(*(system + i) * 1.0 / size) / log10(2));
        }

    }

    return entropy * -1.0;
}


void display_entropy(int *system, int size, double entropy) {
    printf("\nWith %d samples, you have the following balls in the bucket:", size);

    printf("\n{");
    for (int i = 0; i < size; i++) { // Display contents of bucket in form of {#1, #2, #3, ... , #N}
        if (i == size - 1)
            printf("%d}", *(system + i));
        else
            printf("%d, ", *(system + i));
    }

    printf("\nAnd the entropy is = %.2lf", entropy);
}