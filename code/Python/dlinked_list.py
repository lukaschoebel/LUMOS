class Node:
    def __init__(self, value):
        self.value = value
        self.prev = None
        self.next = None

class DoublyLinkedList:
    def __init__(self, value):
        self.head = Node(value)
        self.tail = self.head
        self.length = 1


    def append(self, value):
        ''' Adds a value to the end of a doubly linked list
        type: value
        '''
        self.length += 1
        postNode = Node(value)

        # Wire the postNode
        self.tail.next = postNode
        postNode.prev = self.tail

        # Sets new tail node
        self.tail = postNode


    def prepend(self, value):
        ''' Adds a value to the beginning of a doubly linked list
        type: value
        '''

        self.length += 1
        preNode = Node(value)

        # Wire the preNode 
        preNode.next = self.head
        self.head.prev = preNode
        
        # Sets new head node
        self.head = preNode


    def insert(self, value, index):
        ''' Inserts a value in the DLL at a provided index position
        type: value
        type: index: str
        '''

        if not index in range(self.length):
            print("ERROR! This index does not exist!")
            return
        elif index == 0:
            self.prepend(value)
        else:
            self.length += 1
            
            insertNode = Node(value)
            currentNode = self.head 
            
            for position in range(self.length - 1):
                if position == index - 1:
                    insertNode.next = currentNode.next
                    
                    currentNode.next.prev = insertNode
                    insertNode.prev = currentNode
                    
                    currentNode.next = insertNode
                    break
                currentNode = currentNode.next


    def remove(self, index):
        ''' Removes a node from a given index 
        type: index: int
        '''
        
        if not index in range(self.length + 1):
            print("ERROR! This index does not exist!")
            return
        
        if index == 0:
            # Remove head of the DLL
            self.head = self.head.next
            self.head.prev = None
        elif index == self.length - 1:
            # Remove tail of the DLL
            self.tail = self.tail.prev
            self.tail.next = None
        else:
            # Introduce a temporary node for 
            # traversing through the list
            currentNode = self.head

            for position in range(self.length - 1):
                if position == index:
                    currentNode.prev.next = currentNode.next
                    currentNode.next.prev = currentNode.prev
                    break
                
                currentNode = currentNode.next

        # Decrease length of the list
        self.length -= 1

    def print_list(self):
        ''' 
        Print the linked list
        '''

        currentNode = self.head

        print(f"<<<<<<< {self.length} >>>>>>>")
        for index in range(self.length):
            nextValue = currentNode.next.value if currentNode.next else 'None'
            print(f"{index}: {currentNode.value}  <->  {nextValue}")
            currentNode = currentNode.next
        print(f"<<<<<<<<.>>>>>>>>")


    def print_head(self):
        print(f">> head: {self.head.value}") if self.head else print(">> head: None")


    def print_tail(self):
        print(f">> tail: {self.tail.value}") if self.tail else print(">> tail: None")


if __name__ == "__main__":
    dlinkedList = DoublyLinkedList(10)

    dlinkedList.append(20)
    dlinkedList.append(30)
    
    dlinkedList.prepend(-5)
    dlinkedList.prepend(-8)

    dlinkedList.insert(value=12, index=2)
    dlinkedList.print_list()

    
    dlinkedList.remove(index=5)
    dlinkedList.insert(value=30, index=4)
    dlinkedList.append(55)

    dlinkedList.print_list()
    dlinkedList.print_head()
    dlinkedList.print_tail()

