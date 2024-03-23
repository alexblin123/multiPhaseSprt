#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void multiPhaseSort(int* arr, int size);
void mergeArrays(int* arr, int left, int middle, int right);
void multiwayMergeSort(int* arr, int left, int right, int phase);

int main() {

    srand(time(0));
    system("chcp 1251 > Null");

    int size = 25;
    int *arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 - 20;
        /*cout << "Введите " << i + 1 << " элемент массива: "; cin >> arr[i];*/
    }

    cout << "Исходный массив:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    auto start = high_resolution_clock::now();

    multiPhaseSort(arr, size);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nОтсортированный массив : " << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "\nВремя сортировки (в микросекундах): " << duration.count() << endl;

    delete[] arr;

    return 0;
}

void multiPhaseSort(int *arr, int size) {
    multiwayMergeSort(arr, 0, size - 1, 1);
}

void mergeArrays(int* arr, int left, int middle, int right) {

    int *tempArr = new int[right - left + 1];
    int i = left, j = middle + 1, k = 0;

    // слияние двух половин во временный массив
    while (i <= middle && j <= right) {
        if (arr[i] <= arr[j]) {
            tempArr[k++] = arr[i++];
        }
        else {
            tempArr[k++] = arr[j++];
        }
    }

    while (i <= middle) {
        tempArr[k++] = arr[i++];
    }

    while (j <= right) {
        tempArr[k++] = arr[j++];
    }

    // копирование элементов из временного массива обратно в arr
    for (k = 0, i = left; i <= right; ++i, ++k) {
        arr[i] = tempArr[k];
    }

    delete[] tempArr;
}

void multiwayMergeSort(int* arr, int left, int right, int phase) {

    if (left < right) {
        int middle = (left + right) / 2;

        multiwayMergeSort(arr, left, middle, phase);
        multiwayMergeSort(arr, middle + 1, right, phase);

        mergeArrays(arr, left, middle, right);
    }
}