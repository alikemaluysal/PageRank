#include <stdio.h>
#include <stdlib.h>

#define NUM_PAGES 4
#define DAMPING_FACTOR 0.85
#define NUM_ITERATIONS 100

void computePageRank(double **linkMatrix, double *pageRank) {
    double outboundLinkCount[NUM_PAGES];

    for (int i = 0; i < NUM_PAGES; i++) {
        outboundLinkCount[i] = 0.0;
        for (int j = 0; j < NUM_PAGES; j++) {
            outboundLinkCount[i] += linkMatrix[i][j];
        }
    }

    for (int i = 0; i < NUM_PAGES; i++) {
        pageRank[i] = 1.0 / NUM_PAGES;
    }

    for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
        double newPagerank[NUM_PAGES] = {0.0};

        for (int i = 0; i < NUM_PAGES; i++) {
            for (int j = 0; j < NUM_PAGES; j++) {
                if (linkMatrix[j][i] > 0) {
                    newPagerank[i] += DAMPING_FACTOR * pageRank[j] / outboundLinkCount[j];
                }
            }
            newPagerank[i] += (1.0 - DAMPING_FACTOR) / NUM_PAGES;
        }

        for (int i = 0; i < NUM_PAGES; i++) {
            pageRank[i] = newPagerank[i];
        }
    }
}

int main() {

    double **linkMatrix = malloc(NUM_PAGES * sizeof(double *));
    for (int i = 0; i < NUM_PAGES; i++)
        linkMatrix[i] = malloc(NUM_PAGES * sizeof(double));

    double exampleLinks[NUM_PAGES][NUM_PAGES] = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 0}
    };

    for (int i = 0; i < NUM_PAGES; i++)
        for (int j = 0; j < NUM_PAGES; j++)
            linkMatrix[i][j] = exampleLinks[i][j];

    double pageRank[NUM_PAGES];

    computePageRank(linkMatrix, pageRank);

    printf("PageRank Values:\n");
    for (int i = 0; i < NUM_PAGES; i++)
        printf("Page %d: %f\n", i, pageRank[i]);

    for (int i = 0; i < NUM_PAGES; i++)
        free(linkMatrix[i]);

    free(linkMatrix);

    return 0;
}
