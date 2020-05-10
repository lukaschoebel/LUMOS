class HashTable:
    def __init__(self, size: int):
        self.data = [None] * size
        self.size = size
    

    def _hash(self, key) -> int:
        ''' Hashes a provided key 
        type: key: str
        rtype: hash: int
        '''

        hash = 0
        keyList = list(key)
        
        # TODO: Integrate better hash function
        for i, element in enumerate(keyList):
            hash = (hash + ord(element) * i) % self.size
        
        return hash


    def set(self, key, value):
        ''' Sets the HashTable value to provided value at hashed location
        type: key: str
        type: value: int
        rtype: None
        '''
        
        # DEBUG
        # print(f"Set value: {value} for key: {key}")
        
        hashedKey = self._hash(key)

        if self.data[hashedKey]: # collision handling

            collisionList = []

            # Add collisions to collisionList -> PROBLEM: O(n)
            # for collision in self.data[hashedKey][1]:
            #     collisionList.append(collision)

            [collisionList.append(collision) for collision in self.data[hashedKey][1]] 
            collisionList.append(value)
            
            self.data[hashedKey] = [key, collisionList]
        else:
            self.data[hashedKey] = [key, [value]]


    def get(self, key) -> int:
        ''' Returns the value of a provided key
        type: key: str
        rtype: value: int
        '''

        hashedKey = self._hash(key)
        value = self.data[hashedKey]

        print(f"Found value: {value} for key: {key}")

        return value


    def keys(self) -> [str]:
        keys = [element[0] for element in self.data if element is not None]

        print(keys)

        return keys


    def print(self):
        strippedList = [element for element in self.data if element is not None]
        print(strippedList)


if __name__ == '__main__':

    myHashTable = HashTable(50)
    myHashTable.set('grapes', 42)
    myHashTable.set('grapes', 21)
    myHashTable.set('grapes', 13)
    myHashTable.set('grapes', 1)
    myHashTable.set('grapes', 1)
    
    myHashTable.set('grapess', 14)
    
    myHashTable.get('grapes')
    myHashTable.set('apples', 9)
    
    myHashTable.get('apples')
    myHashTable.print()
    myHashTable.keys()