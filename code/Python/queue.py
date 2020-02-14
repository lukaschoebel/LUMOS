class Node: 
    def __init__(self, value):
        self.value = value
        self.next = None

class Queue:
    def __init__(self):
        self.first = None
        self.last = None
        self.length = 0
            
    def peek(self):
        ''' Looks up the first element of the queue
        :rtype: self.first: Node()
        '''
        return self.first

    def enqueue(self, value):
        ''' Enqueues a node to the queue
        :type: value
        '''

        enqNode = Node(value)
        
        if not self.length:
            self.first = enqNode
            self.last = self.first
        else:
            enqNode.next = self.last
            self.last = enqNode
        self.length += 1
    

    def dequeue(self):

        if not self.length:
            return None
        
        deqNode = self.first

        if self.length == 1:
            self.first = None
            self.last = None
        else:
            # Define iterator node
            tmpNode = self.last

            # Iterate from the back to the (first-1) node 
            # = (first-2).next node
            for _ in range(self.length - 2):
                tmpNode = tmpNode.next

            # Set the new first equal to the iterator node
            self.first = tmpNode
            self.first.next = None

        self.length -= 1

        return deqNode


    def print_queue(self):
        queue = str(self.length) + ' >> '
        tmpNode = self.last
        for _ in range(self.length):
            queue += tmpNode.value 
            
            queue += " --> " if tmpNode.next else " << "

            tmpNode = tmpNode.next
        print(queue)
    

if __name__ == "__main__":
    myQueue = Queue()

    myQueue.enqueue("Zeus")
    myQueue.enqueue("Poseidon")
    myQueue.enqueue("Aphrodite")
    myQueue.enqueue("Hera")
    myQueue.enqueue("Hades")
    myQueue.print_queue()

    print("peek: ", myQueue.peek().value)

    myQueue.dequeue()
    myQueue.dequeue()
    myQueue.dequeue()
    myQueue.dequeue()
    myQueue.print_queue()
