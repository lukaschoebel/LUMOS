class Trie(object):
    """ Trie implementation in python 
    """
    
    def __init__(self, ):
        """ 
        So we use a dictionary at each level to represent a level in the hashmap
        the key of the hashmap is the character and the value is another hashmap 
        """
        self.node = {}

    def add(self, str):
        """
        Takes a str and splits it character wise 
        Arguments:
        - 'str': The string to be stored in the trie
        """
        node = self.node
        for letter in str:
            # Hashmap: Lookup is O(1) 
            if letter in node:
                node = node[letter]
            else:
                node[letter] = {}
                node = node[letter]

    def search(self, str) -> bool:
        node = self.node
        print(f'this is node: {node}')
        for letter in str:
            if letter in node:
                node = node[letter]
            else:
                return False
        return True

    def find_gcd(self) -> str:
        node = self.node
        gcd = ''

        for key, value in node.items():
            print(f"key: {key} - value: {value}")
            node = node[key]
            # gcd += node[key]
        #for letter in 
        return 'gcd'

class Solution:
    def gcdOfStrings(self, str1: str, str2: str) -> str:
        trie = Trie()
        trie.add(str1)
        trie.add(str2)
        
        return trie.find_gcd()

if __name__ == '__main__': 
    sol = Solution()
    print(sol.gcdOfStrings('AB', 'ABAB'))
    # print(sol.gcdOfStrings('ABC', 'ABAB'))
    print(sol.gcdOfStrings('LEET', 'CODE'))
