# Define a Node class to represent a tree node
class Node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data

# Define a function to generate the Huffman tree
def generate_tree(data):
    # Count the frequency of each character in the data
    freq = {}
    for char in data:
        if char in freq:
            freq[char] += 1
        else:
            freq[char] = 1

    # Create a list of leaf nodes for each character in the data
    nodes = []
    for char, count in freq.items():
        nodes.append(Node((char, count)))

    # Build the Huffman tree by merging nodes with the lowest frequency
    while len(nodes) > 1:
        # Sort the nodes by frequency
        nodes = sorted(nodes, key=lambda x: x.data[1])

        # Merge the two nodes with the lowest frequency
        left = nodes[0]
        right = nodes[1]
        parent = Node((None, left.data[1] + right.data[1]))
        parent.left = left
        parent.right = right
        nodes = nodes[2:]
        nodes.append(parent)

    # Return the root node of the Huffman tree
    return nodes[0]

# Define a function to generate the Huffman codes for each character in the data
def generate_codes(node, code='', codes={}):
    # Traverse the tree and assign a binary code to each leaf node
    if node.data[0]:
        codes[node.data[0]] = code
    else:
        generate_codes(node.left, code + '0', codes)
        generate_codes(node.right, code + '1', codes)
    return codes

# Define a function to encode the data using the Huffman codes
def huffman_encode(data):
    # Generate the Huffman tree and codes
    root = generate_tree(data)
    codes = generate_codes(root)

    # Encode the data using the Huffman codes
    encoded_data = ''
    for char in data:
        encoded_data += codes[char]

    # Return the encoded data and the Huffman tree
    return encoded_data, root

# Define a function to decode the data using the Huffman tree
def huffman_decode(encoded_data, root):
    # Traverse the Huffman tree and decode the encoded data
    decoded_data = ''
    node = root
    for bit in encoded_data:
        if bit == '0':
            node = node.left
        else:
            node = node.right
        if node.data[0]:
            decoded_data += node.data[0]
            node = root

    # Return the decoded data
    return decoded_data

# Sample string to encode
data = 'hello world'

# Encode the data using Huffman encoding
encoded_data, tree = huffman_encode(data)
print('Encoded data:', encoded_data)

# Decode the encoded data using the Huffman tree
decoded_data = huffman_decode(encoded_data, tree)
print('Decoded data:', decoded_data)
