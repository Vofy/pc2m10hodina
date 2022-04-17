#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count_nums(FILE *file)
{
    int counter = 0;

    do
    {
        fscanf(file, "%*d");
        counter++;
    }
    while(!feof(file));

    rewind(file);

    return counter;
}

int *read_nums(FILE *file, int count)
{
    int *numbers = malloc(count * sizeof(int));

    int index = 0;
    do
    {
        fscanf(file, "%d", &numbers[index++]);
    }
    while(!feof(file));

    rewind(file);

    return numbers;
}

void print_array(int *numbers, int count)
{
    for(int i = 0; i < count; i++)
    {
        printf("%d\n", numbers[i]);
    }
}

int bubble_sort(int pole[], int delka)
{
    int pom, n, i;
    for (n = delka - 1; n > 0; n--)
        for (i = 0; i < n; i++)
            if (pole[i] > pole[i + 1])
            {
                pom = pole[i];
                pole[i] = pole[i + 1];
                pole[i + 1] = pom;
            }
    return 0;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selection_sort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

void insertion_sort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()

{
    FILE *input = fopen("file.txt", "r");
    int count = count_nums(input);
    int *numbers = read_nums(input, count);

    double cpu_time_used;
    clock_t start, end;

    start = clock();
    bubble_sort(numbers, count);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time (bubble sort):    %f\n", cpu_time_used);

    numbers = read_nums(input, count);

    start = clock();
    selection_sort(numbers, count);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time (selection sort): %f\n", cpu_time_used);

    numbers = read_nums(input, count);

    start = clock();
    insertion_sort(numbers, count);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time (insertion sort): %f\n", cpu_time_used);

    fclose(input);

    return 0;
}
