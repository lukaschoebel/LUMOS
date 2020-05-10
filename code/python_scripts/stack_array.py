class Stack:
    def __init__(self):
        self.stack = []
        self.top = None
        self.bottom = None

    def push(self, value):
        ''' Pushes an element to the stack array
        '''
        
        if len(self.stack) == 0:
            self.stack.append(value)
        else:
            self.stack[:0] = [value]

        self.top = self.stack[0]
        self.bottom = self.stack[len(self.stack) - 1]


    def pop(self):
        ''' Returns None or the topmost stack node
        :rtype: topNode
        '''

        if len(self.stack) == 0:
            return None
        
        topNode = self.top

        if len(self.stack) == 1:
            self.top = None
            self.stack = []
        else:
            self.top = self.stack[1]
            self.stack = self.stack[1:]

        return topNode


    def is_empty(self):
        ''' Checks whether a given stack is empty or not
        :rtype: result: bool
        '''
        return True if not len(self.stack) else False


    def print_stack(self):
        ''' Prints the stack from top to bottom
        '''

        print(f"<<< {len(self.stack)} >>>")
        
        for idx, element in enumerate(self.stack):
            print(f"{idx}: {element}")
        
        print("<<<<->>>>\n")

if __name__ == "__main__":
    myStack = Stack()

    myStack.push(1)
    myStack.push(2)
    myStack.push(3)
    myStack.print_stack()

    myStack.push(4)
    myStack.print_stack()
    
    myStack.pop()
    myStack.print_stack()

    print(myStack.is_empty())