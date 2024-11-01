#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>

#include "files.h"
#include "huffman.h"

std::unordered_map<std::string, std::string> huffmanCode;

huffmanNode* huffmanNode::allocateNode(std::string symbols, int weight, huffmanNode* left, huffmanNode* right)
{
	huffmanNode* node = new huffmanNode;

	node->symbols = symbols;
	node->weight  = weight;
	node->left	  = left;
	node->right   = right;

	return node;
}

std::string huffmanNode::getSymbols()
{
	return symbols;
}

int huffmanNode::getWeight()
{
	return weight;
}

bool huffmanNode::isLeaf(huffmanNode* node)
{
	return (node->left == nullptr && node->right == nullptr);
}

bool sortByWeights::operator()(huffmanNode* first, huffmanNode* second)
{
	return first->getWeight() > second->getWeight();	
}

huffmanNode* buildHuffmanTree(std::unordered_map<char, int> frequencies)
{
	std::priority_queue<huffmanNode*, std::vector<huffmanNode*>, sortByWeights> list;

	for(std::pair<char, int> entry : frequencies)
	{
		std::string symbols(1, entry.first);
		list.push(huffmanNode::allocateNode(symbols, entry.second, nullptr, nullptr));
	}

	while(list.size() > 1)
	{
		huffmanNode* left = list.top();
		list.pop();
		huffmanNode* right = list.top();
		list.pop();

		huffmanNode* newNode = huffmanNode::allocateNode(left->getSymbols() + right->getSymbols(), left->getWeight() + right->getWeight(), left, right);
		list.push(newNode);
	}
	
	huffmanNode* rootNode = list.top();

	return rootNode;
}

void buildCode(huffmanNode* root, std::string temporary, std::unordered_map<std::string, std::string> &code)
{
	if(root == nullptr)
		return;

	if(!root->left && !root->right)
	{
		code[root->getSymbols()] = temporary; 	
	}

	buildCode(root->left, temporary + "0", code);
	buildCode(root->right, temporary + "1", code);

}

void generateCode(const std::string path)
{
	const std::string file = readFile(path);
	std::unordered_map<char, int> frequencies = countFrequency(file);

	huffmanNode* tree = buildHuffmanTree(frequencies);
	buildCode(tree, "", huffmanCode);
	tree = 0;
	delete tree;
}


void printCode()
{
	for(std::pair<std::string, std::string> entry : huffmanCode)
	{
		std::cout << "Symbol \"" << entry.first << "\" : " << entry.second << "\n";
	}
}

void encode(const std::string path)
{
	const std::string file = readFile(path);
	if(huffmanCode.empty())
		generateCode(path);
	
	std::ofstream outfile;
	outfile.open(path + ".huf", std::ios::binary);

	char byte = 0;
	int bitCount = 0;

	for(char symbol : file)
	{
	
		std::string converted(1, symbol);
		for(char bits : huffmanCode[converted])
		{
			byte = (byte << 1) | (bits - '0');

			++bitCount;

			if(bitCount == 8)
			{
				outfile.put(byte);
				byte = 0;
				bitCount = 0;
			}
		}
	}
}

