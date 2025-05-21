#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

class HuffmanCoding
{
private:
    Node *root;
    unordered_map<char, string> huffmanCodes;
    unordered_map<char, int> frequencyMap;

    void generateCodes(Node *root, string str)
    {
        if (!root)
            return;

        if (!root->left && !root->right)
        {
            huffmanCodes[root->ch] = str;
        }

        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }

    void serializeTree(Node *node, string &bits)
    {
        if (!node)
            return;
        if (!node->left && !node->right)
        {
            bits += '1'; // лист
            for (int i = 7; i >= 0; i--)
            {
            }
        }
        else
        {
            bits += '0'; // внутренний узел
            serializeTree(node->left, bits);
            serializeTree(node->right, bits);
        }
    }

    int getSerializedTreeSize(Node *node)
    {
        if (!node)
            return 0;
        if (!node->left && !node->right)
        {
            return 1 + 8; // 1 бит + 8 бит для символа
        }
        else
        {
            return 1 + getSerializedTreeSize(node->left) + getSerializedTreeSize(node->right);
        }
    }

public:
    HuffmanCoding() : root(nullptr) {}

    void buildFrequencyMap(string text)
    {
        for (char ch : text)
        {
            frequencyMap[ch]++;
        }
    }

    void buildHuffmanTree()
    {
        priority_queue<Node *, vector<Node *>, Compare> pq;

        for (auto pair : frequencyMap)
        {
            pq.push(new Node(pair.first, pair.second));
        }

        while (pq.size() > 1)
        {
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();

            Node *internal = new Node('$', left->freq + right->freq);
            internal->left = left;
            internal->right = right;
            pq.push(internal);
        }

        root = pq.top();
        generateCodes(root, "");
    }

    string encode(string text)
    {
        string encoded = "";
        for (char ch : text)
        {
            encoded += huffmanCodes[ch];
        }
        return encoded;
    }

    string decode(string encoded)
    {
        string decoded = "";
        Node *current = root;

        for (char bit : encoded)
        {
            if (bit == '0')
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }

            if (!current->left && !current->right)
            {
                decoded += current->ch;
                current = root;
            }
        }

        return decoded;
    }

    double getCompressionRatio(string original, string compressed)
    {
        double originalBits = original.length() * 8;
        double compressedBits = compressed.length();
        return (originalBits - compressedBits) / originalBits * 100;
    }

    void printCodes()
    {
        cout << "\nHuffman codes:\n";
        for (auto pair : huffmanCodes)
        {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
    // сериализация дерева в виде строки битов
    string getSerializedTreeBits()
    {
        string bits;
        serializeTree(root, bits);
        return bits;
    }

    // размер сериализованного дерева
    int getSerializedTreeSize()
    {
        return getSerializedTreeSize(root);
    }
};

int main()
{
    system("color 0A");
    string text;
    cout << "text: ";
    getline(cin, text);

    HuffmanCoding huffman;

    huffman.buildFrequencyMap(text);
    huffman.buildHuffmanTree();
    huffman.printCodes();

    string encoded = huffman.encode(text);
    cout << "\nEncoded: " << encoded << endl;

    string treeBits = huffman.getSerializedTreeBits();
    int treeBitSize = huffman.getSerializedTreeSize();
    cout << "Serialized tree (bits): " << treeBits << endl;
    cout << "Serialized tree size: " << treeBitSize << " bits" << endl;

    int totalBits = encoded.length() + treeBitSize;
    cout << "Total bits (encoded + tree): " << totalBits << endl;

    string decoded = huffman.decode(encoded);
    cout << "Decoded: " << decoded << endl;

    double compressionRatio = huffman.getCompressionRatio(text, encoded);
    cout << "Comression ratio: " << compressionRatio << "%" << endl;

    double totalCompression = (text.length() * 8.0 - totalBits) / (text.length() * 8.0) * 100;
    cout << "Total compression ratio (with tree): " << totalCompression << "%" << endl;

    return 0;
}