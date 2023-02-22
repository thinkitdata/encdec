/*
This C++ program defines a `HuffmanCoding` class that has methods to compress and decompress text using the Huffman encoding algorithm. 
In the `main()` function, it compresses a string ("Hello, World!") and then decompresses it to verify that the original text was recovered. 
The compressed data is written to a binary file, and the decompressed data is written to a text file.
*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <fstream>
#include <string>
using namespace std;

class HuffmanCoding {
    struct HeapNode {
        char data;
        int freq;
        HeapNode* left, * right;
        HeapNode(char data, int freq) {
            left = right = nullptr;
            this->data = data;
            this->freq = freq;
        }
    };
    struct compare {
        bool operator()(HeapNode* left, HeapNode* right) {
            return (left->freq > right->freq);
        }
    };

    HeapNode* root;
    unordered_map<char, string> codes;
    unordered_map<string, char> reverse_mapping;

    void make_frequency_map(string text, unordered_map<char, int>& frequency) {
        for (char c : text) {
            frequency[c]++;
        }
    }

    void build_huffman_tree(unordered_map<char, int>& frequency) {
        priority_queue<HeapNode*, vector<HeapNode*>, compare> min_heap;

        for (auto pair : frequency) {
            min_heap.push(new HeapNode(pair.first, pair.second));
        }

        while (min_heap.size() != 1) {
            HeapNode* left = min_heap.top(); min_heap.pop();
            HeapNode* right = min_heap.top(); min_heap.pop();

            HeapNode* parent = new HeapNode('$', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            min_heap.push(parent);
        }

        root = min_heap.top();
    }

    void build_codes(HeapNode* root, string code) {
        if (root == nullptr) return;

        if (root->data != '$') {
            codes[root->data] = code;
            reverse_mapping[code] = root->data;
        }

        build_codes(root->left, code + "0");
        build_codes(root->right, code + "1");
    }

    string get_encoded_text(string text) {
        string encoded_text = "";
        for (char c : text) {
            encoded_text += codes[c];
        }
        return encoded_text;
    }

    string pad_encoded_text(string encoded_text) {
        int padding = 8 - (encoded_text.length() % 8);
        for (int i = 0; i < padding; i++) {
            encoded_text += "0";
        }
        bitset<8> padding_bits(padding);
        string padded_info = padding_bits.to_string();
        encoded_text = padded_info + encoded_text;
        return encoded_text;
    }

    unsigned char get_byte(string byte) {
        return bitset<8>(byte).to_ulong();
    }

    string get_decoded_text(string encoded_text) {
        string decoded_text = "";
        string current_code = "";
        for (char c : encoded_text) {
            current_code += c;
            if (reverse_mapping.find(current_code) != reverse_mapping.end()) {
                decoded_text += reverse_mapping[current_code];
                current_code = "";
            }
        }
        return decoded_text;
    }

public:
    HuffmanCoding() {
        root = nullptr;
    }

    void compress(string text, string compressed_file) {
        unordered_map<char, int> frequency;
        make_frequency_map(text, frequency);
        build_huffman_tree(frequency);
        build_codes(root, "");

        string encoded_text = get_encoded_text(text);
        string padded_encoded_text = pad_encoded_text(encoded_text);

        ofstream outfile(compressed_file, ios::binary);
        for (int i = 0; i < padded_encoded_text.length(); i += 8) {
            string byte = padded_encoded_text.substr(i, 8);
            outfile << get_byte(byte);
        }
        outfile.close();
    }

    void decompress(string compressed_file, string decompressed_file) {
        ifstream infile(compressed_file, ios::binary);
        string encoded_text = "";
        char c;
        while (infile.get(c)) {
            encoded_text += bitset<8>(c).to_string();
        }
        infile.close();

        int padding = stoi(encoded_text.substr(0, 8), nullptr, 2);

        string encoded_text_without_padding = encoded_text.substr(8, encoded_text.size() - padding - 8);
        string decoded_text = get_decoded_text(encoded_text_without_padding);

        ofstream outfile(decompressed_file);
        outfile << decoded_text;
        outfile.close();
    }
};

int main() {
    HuffmanCoding huffman;
    string text = "Hello, World!";
    cout << "Original text: " << text << endl;

    string compressed_file = "compressed.bin";
    huffman.compress(text, compressed_file);
    cout << "Text compressed and saved to file " << compressed_file << endl;

    string decompressed_file = "decompressed.txt";
    huffman.decompress(compressed_file, decompressed_file);
    cout << "Text decompressed and saved to file " << decompressed_file << endl;

    ifstream infile(decompressed_file);
    string output_text = "";
    getline(infile, output_text);
    infile.close();
    cout << "Decompressed text: " << output_text << endl;

    return 0;
}
