#ifndef LONGEST_INCREASING_SUBSEQUENCE_HPP
#define LONGEST_INCREASING_SUBSEQUENCE_HPP

#include <array>
#include <stdexcept>
#include <type_traits>
#include <iostream>

template<typename T>
concept uInt = std::is_same_v<T, unsigned int>;

template<size_t N, uInt T>
int maxEndingAt(const std::array<T, N>& nums, int left, int end) {
    int maxLen = 1;
    for (int i = left; i < end; ++i) {
        if (nums[i] < nums[end]) {
            maxLen = std::max(maxLen, maxEndingAt(nums, left, i) + 1);
        }
    }
    return maxLen;
}

template<size_t N, uInt T>
int maxStartingAt(const std::array<T, N>& nums, int start, int right) {
    int maxLen = 1;
    for (int i = start + 1; i <= right; ++i) {
        if (nums[start] < nums[i]) {
            maxLen = std::max(maxLen, maxStartingAt(nums, i, right) + 1);
        }
    }
    return maxLen;
}

template<size_t N, uInt T>
int divideAndConquerLIS(const std::array<T, N>& nums, int left, int right) {
    if (left == right) {
        return 1;
    }

    int mid = left + (right - left) / 2;
    int leftRes = divideAndConquerLIS(nums, left, mid);
    int rightRes = divideAndConquerLIS(nums, mid + 1, right);

    int cross = 0;
    for (int i = left; i <= mid; ++i) {
        for (int j = mid + 1; j <= right; ++j) {
            if (nums[i] < nums[j]) {
                int current = maxEndingAt(nums, left, i) + maxStartingAt(nums, j, right);
                cross = std::max(cross, current);
            }
        }
    }

    return std::max({ left, right, cross });
}

template<size_t N, uInt T>
int lengthOfLIS(const std::array<T, N>& nums) {
    try {
        if (N == 0) {
            return 0;
        }

        return divideAndConquerLIS(nums, 0, N - 1);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return -1;
    }
}

#endif // LONGEST_INCREASING_SUBSEQUENCE_H