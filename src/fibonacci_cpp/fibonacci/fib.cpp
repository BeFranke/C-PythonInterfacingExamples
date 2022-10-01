#include "fib.h"

int* fibonacci(int n) {
    auto result = new int[n];
    for(auto i = 0; i < n; ++i) {
        if(i == 0) {
            result[i] = 0;
            continue; 
        }
        if(i == 1) {
            result[i] = 1;
            continue;
        }
        result[i] = result[i-1] + result[i-2];
    }
    return result;
}