#include "pch.h"

#include "Sorter.h"

#include <algorithm>
#include <vector>

using namespace std;

void Sorter::insertionSort(vector<string>& data, const size_t fi, const size_t n) {
    if (n < 2 || fi >= data.size()) {
        return;
    }

    const size_t last = min(fi + n, data.size());

    for (size_t i = fi + 1; i < last; ++i) {
        string value = data[i];
        size_t j = i;

        while (j > fi && data[j - 1] > value) {
            data[j] = data[j - 1];
            --j;
        }

        data[j] = value;
    }
}

void Sorter::quickSort(vector<string>& data, const size_t fi, const size_t n) {
    if (n < 2 || fi >= data.size()) {
        return;
    }

    const size_t actualN = min(n, data.size() - fi);

    const size_t pivotIndex = partition(data, fi, actualN);

    const size_t leftCount = pivotIndex - fi;
    const size_t rightCount = fi + actualN - pivotIndex - 1;

    quickSort(data, fi, leftCount);
    quickSort(data, pivotIndex + 1, rightCount);
}

size_t Sorter::partition(vector<string>& data, const size_t fi, const size_t n) {
    if (n < 2 || fi >= data.size()) {
        return fi;
    }

    const size_t actualN = min(n, data.size() - fi);
    const size_t last = fi + actualN - 1;
    const size_t mid = fi + actualN / 2;

    if (data[mid] < data[fi]) {
        swap(data[mid], data[fi]);
    }

    if (data[last] < data[fi]) {
        swap(data[last], data[fi]);
    }

    if (data[last] < data[mid]) {
        swap(data[last], data[mid]);
    }

    swap(data[fi], data[mid]);

    const string pivot = data[fi];

    size_t left = fi + 1;
    size_t right = last;

    while (true) {
        while (left <= right && data[left] < pivot) {
            ++left;
        }

        while (left <= right && data[right] > pivot) {
            --right;
        }

        if (left >= right) {
            break;
        }

        swap(data[left], data[right]);
        ++left;
        --right;
    }

    swap(data[fi], data[right]);

    return right;
}

void Sorter::mergeSort(vector<string>& data, const size_t fi, const size_t n) {
    if (n < 2 || fi >= data.size()) {
        return;
    }

    const size_t actualN = min(n, data.size() - fi);

    const size_t leftCount = actualN / 2;
    const size_t rightCount = actualN - leftCount;

    mergeSort(data, fi, leftCount);
    mergeSort(data, fi + leftCount, rightCount);

    merge(data, fi, leftCount, rightCount);
}

void Sorter::merge(vector<string>& data, const size_t fi, const size_t nl, const size_t nr) {
    if (fi >= data.size() || nl == 0 || nr == 0) {
        return;
    }

    const size_t leftEnd = fi + nl;
    const size_t rightEnd = min(leftEnd + nr, data.size());

    vector<string> merged;
    merged.reserve(rightEnd - fi);

    size_t left = fi;
    size_t right = leftEnd;

    while (left < leftEnd && right < rightEnd) {
        if (data[left] <= data[right]) {
            merged.push_back(data[left]);
            ++left;
        }
        else {
            merged.push_back(data[right]);
            ++right;
        }
    }

    while (left < leftEnd) {
        merged.push_back(data[left]);
        ++left;
    }

    while (right < rightEnd) {
        merged.push_back(data[right]);
        ++right;
    }

    move(merged.begin(), merged.end(), data.begin() + fi);
}

static void siftDown(vector<string>& data, size_t root, const size_t heapSize) {
    while (true) {
        const size_t leftChild = 2 * root + 1;

        if (leftChild >= heapSize) {
            return;
        }

        size_t largerChild = leftChild;
        const size_t rightChild = leftChild + 1;

        if (rightChild < heapSize && data[largerChild] < data[rightChild]) {
            largerChild = rightChild;
        }

        if (data[root] >= data[largerChild]) {
            return;
        }

        swap(data[root], data[largerChild]);
        root = largerChild;
    }
}

void Sorter::heapSort(vector<string>& data) {
    if (data.size() < 2) {
        return;
    }

    heapify(data);

    for (size_t heapSize = data.size(); heapSize > 1; --heapSize) {
        swap(data[0], data[heapSize - 1]);
        siftDown(data, 0, heapSize - 1);
    }
}

void Sorter::heapify(vector<string>& data) {
    if (data.size() < 2) {
        return;
    }

    for (size_t i = data.size() / 2; i > 0; --i) {
        siftDown(data, i - 1, data.size());
    }
}
