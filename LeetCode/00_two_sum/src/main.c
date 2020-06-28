#include <stdio.h>
#include <stdlib.h>

/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
	*returnSize = 2;

	for (int i = 0; i < numsSize - 1; i++) {
		for (int j = i + 1; j < numsSize; j++) {
			if (nums[i] + nums[j] == target) {
				int* result = malloc(2 * sizeof(int));
				result[0] = i;
				result[1] = j;
				return result;
			}
		}
	}

	return NULL;
}

int main() {
	
	int nums[] = {3, 2, 4};
	int nums_len = sizeof(nums) / sizeof(int);
	int target = 6;

	int returnSize;
	int* result = twoSum(nums, nums_len, target, &returnSize);

	printf("result = %p\n", result);
	printf("returnSize = %d\n", returnSize);
	printf("result by idx = [%d, %d]", result[0], result[1]);

	return 0;
}