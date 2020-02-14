import unittest

def merge_sorted_arrays(arr1, arr2) -> [str]:

    if not arr1 and not arr2:
        # Return empty array if both lists are empty
        return []
    elif not arr1:
        return arr2
    elif not arr2:
        return arr1
    else: 
        # Merge arrays
        result = arr1 + arr2
    
    # Return sorted and merged array
    return sorted(result)
    

class TestFunction(unittest.TestCase):
    def setUp(self):
        pass

    def test_1(self):
        self.assertEqual(merge_sorted_arrays([0, 3, 4, 31], [4, 6, 30]), [0, 3, 4, 4, 6, 30, 31])

    def test_2(self):
        self.assertEqual(merge_sorted_arrays([0, 3, 0, -12], [0, 3, 500]), [-12, 0, 0, 0, 3, 3, 500])

    def test_3(self):
        self.assertEqual(merge_sorted_arrays([], [1, 3, 3]), [1, 3, 3])

    def test_4(self):
        self.assertEqual(merge_sorted_arrays([], []), [])
    
if __name__ == '__main__':
    # print(merge_sorted_arrays([0, 3, 0, -12], [3, 500, 0]))
    unittest.main()