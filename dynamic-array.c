#include <stdio.h>
#include <stdlib.h>

struct dynamic_array {
    int *loc;
    int size;
    int cap;
};

/* function prototypes */
struct dynamic_array *init_array();
int get(struct dynamic_array *, int);
void set(struct dynamic_array*, int, int);
void push_back(struct dynamic_array *, int);
void remove_element(struct dynamic_array *, int);
int size(struct dynamic_array *);

int main(void)
{
    struct dynamic_array *arr = init_array();
    push_back(arr, 1);
    push_back(arr, 2);
    push_back(arr, 3);
    remove_element(arr, 0);
    printf("the size: %d\n", size(arr));
    printf("0th: %d\n", get(arr, 0));
    printf("1th: %d\n", get(arr, 1));

    free(arr->loc);
    free(arr);
    return 0;
}

struct dynamic_array *init_array()
{
    struct dynamic_array *arr = malloc(sizeof(struct dynamic_array)); 
    arr->size = 0;
    arr->cap = 2;
    arr->loc = malloc(sizeof(int) * arr->cap);
    return arr;
}

void push_back(struct dynamic_array *arr, int val)
{
    /**
     * if dynamic array is full, allocate a new block of memory whose
     * size is the double of its capacity, fill it with the elements
     * and then free old memory location.
     *
     * If not, just add it to the
     * back of the array whose position is determine by size variable.
     */
    if (arr->size == arr->cap) {
        int *new_mem = malloc(sizeof(int) * 2 * arr->cap);
        for (int i = 0; i < arr->size; ++i) {
            new_mem[i] = arr->loc[i];
        }
        free(arr->loc);
        arr->loc = new_mem;
        arr->cap = 2 * arr->cap;
    }
    arr->loc[arr->size] = val;
    arr->size++;
}

void remove_element(struct dynamic_array *arr, int i)
{
    if (i < 0 || i >= arr->size) {
        fprintf(stderr, "index out of range\n");
        exit(1);
    }
    for (int j = i; j <= arr->size - 2; ++j) {
        arr->loc[j] = arr->loc[j + 1];
    }
    arr->size--;
}

int get(struct dynamic_array *arr, int i)
{
    if (i < 0 || i >= arr->size) {
        fprintf(stderr, "index out of range\n");
        exit(1);
    }
    return arr->loc[i];
}

void set(struct dynamic_array *arr, int i, int val)
{
    if (i < 0 || i >= arr->size) {
        fprintf(stderr, "index out of range\n");
        exit(1);
    }
    arr->loc[i] = val;
}

int size(struct dynamic_array *arr)
{
    return arr->size;
}
