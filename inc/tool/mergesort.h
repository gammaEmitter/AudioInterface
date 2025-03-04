#pragma once

template <typename T>
void merge(T* &arr, int left, int mid, int right) {
    int leftLen = mid - left + 1;
    int rightLen = right - mid;
    T leftArr[leftLen];
    T rightArr[rightLen];

    for (int i = 0; i < leftLen; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < rightLen; ++j) {
        rightArr[j] = arr[mid + j + 1];
    }
    int idxLeft{}, idxRight{};
    int idxArr = left;

    while (idxLeft < leftLen && idxRight < rightLen) {
        if (leftArr[idxLeft] <= rightArr[idxRight]) {
            arr[idxArr] = leftArr[idxLeft];
            idxLeft++;
        } else {
            arr[idxArr] = rightArr[idxRight];
            idxRight++;
        }
        idxArr++;
    }

    while (idxLeft < leftLen) {
        arr[idxArr] = leftArr[idxLeft];
        idxLeft++;
        idxArr++;
    }
    while (idxRight < rightLen) {
        arr[idxArr] = rightArr[idxRight];
        idxRight++;
        idxArr++;
    }

    return;
}

template <typename T>
void mergeSort(T** arr, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int mid = (begin + end) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

