#pragma once
#include <iostream>

struct pair {
public:

    int order;
    int index;
    pair(int a, int b) {
        order = a;
        index = b;
    }
    pair() {
        order = index = 0;
    }
};

class SuffixArray {
    const char* str;
    int* arr;
    int length;
    int freq[224] = { 0 };

    void mergeSort(pair array[], int size,int iteration) {

        if (size <= 1)
            return;

        pair* a = new pair[size / 2], * b = new pair[(size + 1) / 2];
        int j = 0;
        for (; j < size / 2; j++)
            a[j] = array[j];
        for (; j < size; j++)
            b[j - size / 2] = array[j];

        mergeSort(a, size / 2, iteration), mergeSort(b, (size + 1) / 2, iteration);

        int la = 0, lb = 0, i = 0;
        for (; la < size / 2 && lb < (size + 1) / 2; i++) {
            if (a[la].order < b[lb].order)
                array[i] = a[la], la++;
            else if (a[la].order == b[lb].order && arr[a[la].index + (1 << (iteration - 1))] < arr[b[lb].index + (1 << (iteration - 1))])
                array[i] = a[la], la++;
            else
                array[i] = b[lb], lb++;
        }

        for (; la < size / 2;i++) {
            array[i] = a[la], la++;
        }

        for (; lb < (size + 1) / 2; i++) {
            array[i] = b[lb], lb++;
        }

        delete[] a;
        delete[] b;
    }


public:

    explicit SuffixArray(const char* query) {
        this->str = query;
        length = 0;
        for (auto it = this->str; *it != '\0'; it++)
            length++, freq[*it - 32]++;

        for (int i = 0, j = 0; i < 224; i++) {
            if (freq[i])
                freq[i] = j, j++;
        }
        arr = new int[length];

        for (int i = 0; i < length; i++)
            arr[i] = freq[str[i] - 32];
    }

    void constructUsingPrefixDoubling() {

        pair a;
        int* temp = new int[length];
        pair* mergArray = new pair [length];
        for (int i = 1; true; i++) {
            for (int j = 0; j < length; j++) {
                a.order = arr[j];
                a.index = j;
                mergArray[j] = a;

                temp[j] = arr[j];
            }
            mergeSort(mergArray, length, i);
            int order = 0;                

            for (int j = 0; j < length - 1; j++) {
                 
                if (mergArray[j].order == mergArray[j + 1].order && temp[mergArray[j].index + (1 << (i - 1))] == temp[mergArray[j + 1].index + (1<< (i - 1))]) {
                    arr[mergArray[j].index] = order;
                }
                else {
                    arr[mergArray[j].index] = order;
                    order++;
                }
            }

            if (mergArray[length - 2].order == mergArray[length - 1].order && temp[mergArray[length - 2].index + (1 << (i - 1))] == temp[mergArray[length - 1].index + (1 << (i - 1))]) {
                arr[mergArray[length - 1].index] = order;
            }
            else {
                arr[mergArray[length - 1].index] = order;
            }

            if (order == length - 1)
                break;
        }

        for (int i = 0; i < length; i++)
            temp[arr[i]] = i;
        for (int i = 0; i < length; i++)
            arr[i] = temp[i];
    }

    void print() {
        for (int i = 0; i < length; i++)
            std::cout << arr[i] << ' ';
        std::cout << '\n';
    }

    ~SuffixArray() {
        delete arr;
    }
};
