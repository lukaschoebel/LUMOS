class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class Stack:
    def __init__(self):
        self.top = None
        self.bottom = None
        self.length = 0

    def peek(self):
        ''' Returns the topmost value of the stack 
        :rtype: value
        '''
        if self.length == 0:
            return None
        return self.top.value


    def push(self, value):
        ''' Pushes a value to the top of the stack
        :type: value
        '''

        insertNode = Node(value)
        self.length += 1
        
        if self.length == 0:
            self.top = insertNode
            self.bottom = self.top
        else:
            insertNode.next = self.top
            self.top = insertNode


    def pop(self):
        ''' Returns the topmost value of the stack
        :rtype: topNode.value
        '''
        if self.length == 0:
            return

        self.length -= 1

        topNode = self.top
        self.top = self.top.next
        return topNode.value

    def is_empty(self):
        ''' Checks if the stack is empty or not
        rtype: result: bool
        '''
        if self.length == 0:
            return True 
        else: 
            return False

    def print_stack(self):
        ''' Prints the stack from top to bottom
        '''

        if self.length == 0:
            return None

        currentTop = self.top

        print(f"<<< {self.length} >>>")
        
        for idx in range(self.length):
            print(f"{idx}: {currentTop.value}")
            currentTop = currentTop.next
        
        print("<<<<->>>>")

if __name__ == "__main__":
    
    theStack = Stack()

    theStack.push("www.google.com")
    theStack.push("www.yahoo.com")
    theStack.push(3)
    theStack.push(4)
    theStack.push(5)
    
    theStack.print_stack()

    theStack.pop()
    theStack.pop()

    theStack.print_stack()

    print(f"peek: {theStack.peek()}")