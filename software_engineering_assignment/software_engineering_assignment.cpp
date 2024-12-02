// main.cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

// 내가 작성한 버전 - 기본 QuickSort
namespace HumanCode {
    void quickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivot = arr[high];
            int i = low - 1;
            
            for (int j = low; j < high; j++) {
                if (arr[j] <= pivot) {
                    i++;
                    std::swap(arr[i], arr[j]);
                }
            }
            std::swap(arr[i + 1], arr[high]);
            
            quickSort(arr, low, i);
            quickSort(arr, i + 2, high);
        }
    }
}

// Copilot이 생성한 버전 - 최적화된 QuickSort
namespace CopilotCode {
    void insertionSort(std::vector<int>& arr, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    int medianOfThree(std::vector<int>& arr, int low, int high) {
        int mid = low + (high - low) / 2;
        if (arr[low] > arr[mid])
            std::swap(arr[low], arr[mid]);
        if (arr[low] > arr[high])
            std::swap(arr[low], arr[high]);
        if (arr[mid] > arr[high])
            std::swap(arr[mid], arr[high]);
        return mid;
    }

    void quickSort(std::vector<int>& arr, int low, int high) {
        while (low < high) {
            if (high - low < 10) {
                insertionSort(arr, low, high);
                break;
            }
            
            int pivotIndex = medianOfThree(arr, low, high);
            std::swap(arr[pivotIndex], arr[high]);
            
            int pivot = arr[high];
            int i = low - 1;
            
            for (int j = low; j < high; j++) {
                if (arr[j] <= pivot) {
                    i++;
                    std::swap(arr[i], arr[j]);
                }
            }
            std::swap(arr[i + 1], arr[high]);
            
            // 작은 부분을 먼저 처리
            if (i - low < high - (i + 2)) {
                quickSort(arr, low, i);
                low = i + 2;
            } else {
                quickSort(arr, i + 2, high);
                high = i;
            }
        }
    }
}

// 성능 테스트
void performanceTest() {
    const int SIZE = 100000;
    std::vector<int> arr1(SIZE), arr2(SIZE);
    
    // 랜덤 데이터 생성
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);
    
    for (int i = 0; i < SIZE; i++) {
        arr1[i] = arr2[i] = dis(gen);
    }
    
    // 내가 작성한 버전 테스트
    auto start = std::chrono::high_resolution_clock::now();
    HumanCode::quickSort(arr1, 0, SIZE - 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto human_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Copilot 버전 테스트
    start = std::chrono::high_resolution_clock::now();
    CopilotCode::quickSort(arr2, 0, SIZE - 1);
    end = std::chrono::high_resolution_clock::now();
    auto copilot_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Human Version Time: " << human_duration.count() << " microseconds\n";
    std::cout << "Copilot Version Time: " << copilot_duration.count() << " microseconds\n";
}

int main() {
    performanceTest();
    return 0;
}