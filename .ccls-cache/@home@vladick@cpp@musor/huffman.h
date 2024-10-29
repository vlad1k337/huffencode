#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <queue>
#include <unordered_map>


class huffmanNode {
	public:

		std::string getSymbols();
		int getWeight();

		static bool isLeaf(huffmanNode* node);
		static huffmanNode* allocateNode(std::string symbols, int weight, huffmanNode* left, huffmanNode* right);

		huffmanNode* left = nullptr;
		huffmanNode* right = nullptr;
	private:
		std::string symbols;
		int weight;
};

// Custom comparator for priority_queue to sort huffmanNodes by weight
class sortByWeights {
	public:
		bool operator()(huffmanNode* first, huffmanNode* second);
};

huffmanNode* buildHuffmanTree(std::unordered_map<char, int> frequencies);

void buildCode(huffmanNode* root, std::string temporary, std::unordered_map<std::string, std::string> &code);
void generateCode(const std::string path);
void printCode();

void encode(const std::string path);
void decode(const std::string path);

#endif
