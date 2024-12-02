#include <stdio.h>

static inline void swap(int *a, int *b) {
    *a = *b ^ *a;
    *b = *a ^ *b;
    *a = *b ^ *a;
}

size_t divide(int *array, size_t left, size_t right) {
    size_t left_index = left;
    size_t right_index = right - 1;
    int pivot = array[right];

    while(left_index < right_index) {
        while(left_index < right_index && array[left_index] <= pivot) {
            left_index++;
        }

        while(right_index > left_index && array[right_index] > pivot) {
            right_index--;
        }

        if(array[left_index] > array[right_index]) {
            swap(&array[left_index], &array[right_index]);
        }
    }

    if(array[left_index] > pivot) {
        swap(&array[left_index], &array[right]);
    }
    else {
        left_index = right;
    }

    return left_index;
}


void quicksort(int *array, size_t left, size_t right) {
    if(left < right) {
        size_t pivot = divide(array, left, right);
        quicksort(array, left, pivot-1);
        quicksort(array, pivot+1, right);
    }
}

#define BUFFER_SIZE 0xffff
#define LINE_COUNT 1000

static inline int abs(int a) {
    return a < 0 ? -a : a;
}

int main() {
    FILE *finput = fopen("input.txt", "rb");

    if(!finput) {
        perror("Failed to open input file");
        return 1;
    }

    int left_list[LINE_COUNT];
    int right_list[LINE_COUNT];

    for(int i = 0; i < LINE_COUNT; i++) {
        fscanf(finput, "%d   %d\n", &left_list[i], &right_list[i]);
    }

    quicksort(left_list, 0, LINE_COUNT-1);
    quicksort(right_list, 0, LINE_COUNT-1);

    unsigned int sum = 0;

    for(int i = 0; i < LINE_COUNT; i++) {
        sum += abs(left_list[i] - right_list[i]);
    }

    printf("Distance: %d\n", sum);

    int left_index = 0;
    int right_index = 0;
    int appearance_in_right = 0;
    long int similarity = 0;

    for(left_index = 0; left_index < LINE_COUNT; left_index++) {
        while(left_list[left_index] > right_list[right_index]) {
            right_index++;

            if(right_index == LINE_COUNT) break;
        }

        while(left_list[left_index] == right_list[right_index]) {
            appearance_in_right++;
            right_index++;

            if(right_index == LINE_COUNT) break;
        }

        similarity += appearance_in_right * left_list[left_index];
        appearance_in_right = 0;
    }

    printf("Similarity: %ld\n", similarity);

    fclose(finput);
    return 0;
}