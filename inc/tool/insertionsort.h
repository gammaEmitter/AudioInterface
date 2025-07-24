#pragma once

template <typename T>
void insertionSort(T arr[], int size) {
    int j;
    T x;
    for (int i = 1; i < size; ++i) {
        x = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j]->start_time > x->start_time) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = x;
    }
}


