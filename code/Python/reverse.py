import unittest

def reverse(str) -> str:
    
    if len(str) < 2:
        return str
    else:
        result = ''

        for character in reversed(str):
            result += character 

        return result

class TestReverse(unittest.TestCase):
    def setUp(self):
        pass

    def test_string(self):
        self.assertEqual(reverse('Hi my name is Lukas!'), '!sakuL si eman ym iH')

    def test_empty_string(self):
        self.assertEqual(reverse(''), '')

    def test_crazy_string(self):
        self.assertEqual(reverse('!.!!'), '!!.!')

    def test_single_string(self):
        self.assertEqual(reverse('a'), 'a')

if __name__ == '__main__':
    print(reverse('Hi my name is Lukas!'))
    # unittest.main()