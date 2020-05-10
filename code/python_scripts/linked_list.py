class Node:
    def __init__(self, value):
        self.value = value
        self.next = None # the pointer initially points to nothing


class LinkedList:
    def __init__(self, value):
        self.length = 1
        self.head = Node(value)
        self.tail = self.head


    def append(self, value):
        ''' Adds a value to the end of a singly linked list
        type: value
        '''
        
        postNode = Node(value)

        self.tail.next = postNode
        self.tail = postNode
        self.length += 1

    
    def prepend(self, value):
        ''' Adds a value to the beginning of a singly linked list
        type: value
        '''

        preNode = Node(value)

        preNode.next = self.head
        self.head = preNode
        self.length += 1
        

    def insert(self, value, index):
        ''' Inserts a value in the SLL at a provided index position
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

            # Init insertNode and introduce a temporary 
            # currentNode for traversing through the linked list
            insertNode = Node(value)
            currentNode = self.head 
            
            for position in range(self.length):
                if position == index - 1:
                    # Wire the insertNode and break the traversing
                    insertNode.next = currentNode.next
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
            self.head = self.head.next
        else:
            # Introduce a temporary node
            currentNode = self.head

            for position in range(self.length - 1):
                # Delete node by connecting the 'next' pointer 
                # of the previous node to the node after next
                if position == index - 1:
                    currentNode.next = currentNode.next.next

                # Set tail back one position
                if position == self.length - 1:
                    self.tail = currentNode 

                # Iterate through the list
                currentNode = currentNode.next
            
        # Decrease length of the list
        self.length -= 1


    def reverse(self):
        ''' Reverse a singly-linked list
        '''
        
        # CornerCase if SLL contains 
        # only out of one element:
        if not self.head.next:
            return self

        # Init iterator variables
        firstNode = self.head
        secondNode = firstNode.next

        # Set tail equal to head
        self.tail = self.head

        while secondNode:
            temp = secondNode.next
            secondNode.next = firstNode
            firstNode = secondNode
            secondNode = temp

        self.head.next = None
        self.head = firstNode
        return self

        # Init 
        # reversedList = LinkedList(self.tail.value)
        # reversedValues = []

        # # CornerCase if SLL contains 
        # # only out of one element:
        # if not self.head.next:
        #     return reversedList
        
        # # Define iterator node
        # currentNode = self.head

        # # Append value to array -> O(n)
        # for _ in range(self.length):
        #     reversedValues.append(currentNode.value)
        #     currentNode = currentNode.next

        # # Reverse array
        # reversedValues = reversedValues[::-1]
        
        # # Append all values to reversedList -> O(n)
        # for index in range(1, self.length):
        #     reversedList.append(reversedValues[index])
        
        # return reversedList

    def print_list(self):
        ''' 
        Print the linked list
        '''
        currentNode = self.head

        print(f"<<<<<<< {self.length} >>>>>>>")
        for index in range(self.length):
            nextValue = currentNode.next.value if currentNode.next else 'None'
            print(f"{index}: {currentNode.value}  ->  {nextValue}")
            currentNode = currentNode.next
        print(f"<<<<<<<< >>>>>>>>")

    def print_head(self):
        print(f">> head: {self.head.value}") if self.head else print(">> head: None")
    
    def print_tail(self):
        print(f">> tail: {self.tail.value}") if self.tail else print(">> tail: None")


if __name__ == '__main__':

    linkedList = LinkedList(10)
    linkedList.append(15)
    linkedList.append(12)
    linkedList.append(20)
    # linkedList.print_list()

    linkedList.prepend(42)
    # linkedList.print_list()

    linkedList.insert(value=-1, index=0)
    # linkedList.print_list()

    linkedList.remove(index=1)
    # linkedList.remove(2)

    linkedList.print_list()

    linkedList.reverse()
    linkedList.reverse()

    linkedList.print_list()
    linkedList.print_head()
    linkedList.print_tail()
