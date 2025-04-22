#include <iostream>
#include <cmath>

struct Point {
    int id;
    double angle;
};

void merge(Point arr[], int left, int mid, int right);
void mergeSort(Point arr[], int left, int right);

int main(int argc, char const *argv[])
{
    int N;
    std::cin >> N;

    int x[N], y[N];
    for (int n = 0; n < N; ++n)
        std::cin >> x[n] >> y[n];

    int fp_id = 0;
    for (int i = 1; i < N; ++i)
        if (x[i] < x[fp_id])
            fp_id = i;

    Point phi[N - 1];
    for (int i = 0, j = 0; i < N; ++i, ++j) {
        if (i != fp_id) {
            phi[j].angle = atan2(y[i] - y[fp_id], x[i] - x[fp_id]);
            phi[j].id = i;
        }
        else --j;
    }
    mergeSort(phi, 0, N - 2);
    
    std::cout << ++fp_id << ' ' << ++phi[N / 2 - 1].id;
    
    return 0;
}

void merge(Point arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Point* L = new Point[n1];
    Point* R = new Point[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i].angle <= R[j].angle) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Point arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
