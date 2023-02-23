<p align="center">
<img src="https://github.com/thinkitdata/encdec/blob/main/huffman/huff_ex_2.png" alt="Huffman Tree" width="25%" height="25%" title="Huffman Tree">
</p>

### Readme info for implementations in Python3, C++, and Assembly (x86_64 NASM/Linux)

- huffman.py
- huffman.cpp
- huffman2.asm

Huffman coding is a lossless data compression algorithm that was developed by David A. Huffman in 1952. It is used to compress data by assigning variable-length codes to symbols in the input data. The more frequently occurring symbols are assigned shorter codes, while less frequent symbols are assigned longer codes. This results in a reduction in the amount of data required to represent the original input.

**Huffman Encoding**

The Huffman encoding process involves the following steps:

1. <markFrequency Count:</mark> First, the frequency of each symbol in the input data is counted.
2. Building the Huffman Tree: The next step is to construct a binary tree called the Huffman tree, where the leaves represent the symbols in the input data and the root represents the entire input data. The Huffman tree is built using the following algorithm:
- a. Create a leaf node for each symbol and assign the frequency count as the node weight.
- b. Sort the leaf nodes in ascending order of frequency.
- c. Take the two nodes with the lowest frequency count and merge them to form a new node, with the sum of the two frequencies as the weight.
- d. Add the new node to the list of leaf nodes and remove the two original nodes.
- e. Repeat steps c and d until only one node remains, which is the root of the Huffman tree.
3. Assigning Codes: Once the Huffman tree is constructed, each symbol is assigned a unique code based on the path taken to reach it from the root of the tree. The codes are assigned in such a way that no code is a prefix of another code, ensuring that the codes can be unambiguously decoded.
- a. Traverse the Huffman tree from the root to each leaf node, assigning a 0 to each left branch and a 1 to each right branch.
- b. The code for each symbol is the sequence of 0s and 1s that are encountered on the path from the root to the leaf node that represents the symbol.
- c. The codes can be represented as a binary tree with the symbols as the leaves and the codes as the paths from the root to the leaves.

Huffman Decoding

The Huffman decoding process involves the following steps:

1.  Start at the root of the Huffman tree.

2.  Read each bit of the encoded data, starting from the leftmost bit.

3.  Traverse the Huffman tree according to the value of each bit, going left for 0 and right for 1.

4.  When a leaf node is reached, output the corresponding symbol and return to the root of the Huffman tree.

5.  Continue this process until all the bits in the encoded data have been processed.

6.  The result of the decoding process is the original input data.

Huffman coding is an efficient compression algorithm that can achieve a high compression ratio by assigning shorter codes to more frequent symbols. It is widely used in many applications, including image and audio compression, data transmission, and storage.



