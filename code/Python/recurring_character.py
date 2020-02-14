import unittest

def find_recurring_char(strs: [int]) -> int:
    ''' Return the first recurring integer for a provided list of integers
    type: strs: [int]
    rtype: result: int
    '''

    hashTable = {}
    
    # Will provide O(n) time 
    # complexity due to for loop
    for element in strs:
        if hashTable.get(element):
            return element
        
        # Update boolean value in hasTable
        hashTable.update({element: True})
            
    return None

class TestFunction(unittest.TestCase):
    def setUp(self):
        pass

    def test_1(self):
        self.assertEqual(find_recurring_char([2, 3, 4, 2, 3, 4, 5, 2]), 2)
    
    def test_2(self):
        self.assertEqual(find_recurring_char([2, 3, 3, 2, 6]), 3)
    
    def test_3(self):
        self.assertEqual(find_recurring_char([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]), None)

if __name__ == '__main__':
    # theList = [2, 3, 2, 2, 3, 4, 5, 2]
    # theList = [2, 3, 4, 5]


    # print(f"list:\t {theList}")
    # print(find_recurring_char(theList))

    # find_recurring_char([2, 3, 4, 2, 3, 4, 5, 2])
    unittest.main()