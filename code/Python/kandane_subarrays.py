from collections import Counter

def maxSubArray(nums) -> int:
    """ Find the maximum int value
    :type nums: List[int]
    :rtype: int
    """
    subarray = []

    for i in range(1, len(nums)):
        if nums[i-1] > 0:
            nums[i] += nums[i-1]
            subarray.append(nums[i])
    return max(nums), subarray

def maxOccElement(nums) -> int:
    return Counter(nums).most_common(1)[0]
    
if __name__ == '__main__':
    testList = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

    _, subarray = maxSubArray(testList)
    print(f"mostcommon: {maxOccElement(testList)}")
    print(f"subarray is: {subarray}")