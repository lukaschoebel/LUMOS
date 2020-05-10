class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.value)


class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        ''' Inserts an integer value in the BST
        :type: value: int
        :rtype: self: BinaryTree
        '''
        
        # Initialize node 
        insertNode = Node(value)

        if not self.root:
            self.root = insertNode
            return self
        else:
            # Define iterator variable to traverse the tree
            currentNode = self.root

            while True:
                if value < currentNode.value:
                    # Go left
                    if not currentNode.left:
                        currentNode.left = insertNode
                        return self
                    currentNode = currentNode.left
                else:
                    # Go right
                    if not currentNode.right:
                        currentNode.right = insertNode
                        return self
                    currentNode = currentNode.right


    def lookup(self, value):
        ''' Looks up if a provided value is contained in the binary tree or not
        :type: value: int
        :rtype: result: Bool
        '''

        # If there is no root, the value cannot be found
        if not self.root:
            return False
        
        currentNode = self.root
        
        # Otherwise: Traverse the tree and search for the value
        while currentNode is not None:
            # if value == currentNode.value:
            #     return True
            if value < currentNode.value:
                currentNode = currentNode.left
            elif value > currentNode.value:
                currentNode = currentNode.right
            else: 
                return True

        return False


    def remove(self, value):
        ''' Removes a provided integer value and its node from the BinaryTree
        :type: value: int
        '''

        if not self.root:
            return False
        

        parentNode = None
        currentNode = self.root

        # Check for value = self.root.value cases
        while currentNode:
            if value < currentNode.value:
                # Proceed to the left
                parentNode = currentNode
                currentNode = currentNode.left
            elif value > currentNode.value:
                # Proceed to the right
                parentNode = currentNode
                currentNode = currentNode.right
            elif value == currentNode.value:
                # C1: No right child
                if not currentNode.right:
                    # C1.1: + delete current root node
                    if not parentNode:
                        self.root = currentNode.left
                    else:
                        # C1.2: + currentNode < parentNode
                        # -> Proceed to the left
                        if currentNode.value < parentNode.value:
                            parentNode.left = currentNode.left
                        # C1.3: + currentNode > parentNode
                        # -> Proceed to the right
                        elif currentNode.value > parentNode.value:
                            parentNode.right = currentNode.left
                
                # C2: Right child only
                elif not currentNode.right.left:
                    currentNode.right.left = currentNode.left
                    # C2.1: + delete current root node
                    if not parentNode:
                        self.root = currentNode.right
                    else:
                        # C2.2: + currentNode < parentNode
                        if currentNode.value < parentNode.value:
                            parentNode.left = currentNode.right
                        # C2.3:
                        if currentNode.value > parentNode.value:
                            parentNode.right = currentNode.right
                
                # C3: Right child with a left child
                else:
                    # Initialize additional pointers to keep track of the
                    # leftmost nodes of the right child of currentNode
                    leftNode = currentNode.right.left
                    leftParent = currentNode.right

                    # Find leftmost node by traversing through
                    # the BST until leftNode.left == None
                    while leftNode.left is not None:
                        leftParent = leftNode
                        leftNode = leftNode.left

                    # Update leftParent and append 
                    # currentNode subtrees to leftNode
                    leftParent.left = leftNode.right
                    leftNode.left = currentNode.left
                    leftNode.right = currentNode.right

                    if not parentNode:
                        self.root = leftNode
                    else:
                        if currentNode.value < parentNode.value:
                            parentNode.left = leftNode
                        elif currentNode.value > parentNode.value:
                            parentNode.right = leftNode
                return True

    def print_tree(self):
        current_level = [self.root]

        while current_level:
            print(' '.join(str(node) for node in current_level))
            next_level = list()
            for n in current_level:
                if n.left:
                    next_level.append(n.left)
                if n.right:
                    next_level.append(n.right)
                current_level = next_level

if __name__ == '__main__':
    tree = BinaryTree()

    tree.insert(9)
    tree.insert(4)
    tree.insert(10)
    tree.insert(12)
    tree.insert(20)
    tree.insert(170)
    tree.insert(15)
    tree.insert(1)
    tree.print_tree()

    print("\n")

    # print(tree.remove(42))
    tree.remove(12)
    tree.print_tree()
    print("\n")
    print(f"{int('a', 26) - 9}")