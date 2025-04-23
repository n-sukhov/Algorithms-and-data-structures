#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

struct Point {
    unsigned short id;
    double angle;
    short r;
};

void merge(Point arr[], int left, int mid, int right);
void mergeSort(Point arr[], int left, int right);

int main(int argc, char const *argv[])
{
    int N;
    std::cin >> N;
    short x[N], y[N];
    for (int i = 0; i < N; ++i)
        std::cin >> x[i] >> y[i];

    Point* phi = new Point[N - 1];
    for (int i = 1; i < N; ++i) {
        (phi + i - 1)->id = i;
        (phi + i - 1)->angle = atan2(y[i] - y[0], x[i] - x[0]);
        (phi + i - 1)->r = std::sqrt((y[i] - y[0]) * (y[i] - y[0]) + (x[i] - x[0]) * (x[i] - x[0]));
    }

    mergeSort(phi, 0, N - 2);
    Point* phi2 = nullptr;
    for (int i = 1; i < N - 1; ++i)
        if ((phi + i)->angle - (phi + i - 1)->angle >= PI) {
            phi2 = new Point [N-1];
            for (int j = i; j < N - 1; ++j)
                *(phi2 + j - i) = *(phi + j);
            for (int j = 0; j < i; ++j)
                *(phi2 + j + N - 1 - i) = *(phi + j);
            delete[] phi;
            break;
        }

    Point* phi3 = nullptr;
    Point* phi_temp = phi2 ? phi2 : phi;
    int size;
    for (int i = 1; i < N - 1; ++i)
        if ((phi_temp + i)->angle - (phi_temp + i - 1)->angle > - PI - 0.00000001 &&
        (phi_temp + i)->angle - (phi_temp + i - 1)->angle < - PI + 0.00000001) {
            if (i > (N - 1) / 2) {
                size = i;
                phi3 = new Point [size];
                for (int j = 0; j < i; ++j)
                    *(phi3 + j) = *(phi_temp + j);
            }
            else {
                size = N - 1 - i;
                phi3 = new Point [size];
                for (int j = 0; j < N - 1 - i; ++j)
                    *(phi3 + j) = *(phi_temp + j + i);
            }
            if (phi2) delete[] phi2;
            break;
        }


    Point* result_phi = phi3 ? phi3 : (phi2 ? phi2 : phi);
    int result_size = phi3 ? size + 1 : N;
    std::cout << result_size << std::endl << 1 << std::endl;
    for (int i = 0; i < result_size - 1; ++i)
        std::cout << (result_phi + i)->id + 1 << std::endl;

    if (phi_temp == phi) delete[] phi;
    else delete[] phi2;
    delete[] phi3;

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
        if (L[i].angle < R[j].angle) {
            arr[k] = L[i];
            i++;
        }
        else if (L[i].angle > R[j].angle) {
            arr[k] = R[j];
            j++;
        }
        else if (L[i].r < R[j].r) {
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
