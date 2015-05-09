#include "huffman.h"
#include <iostream>

HuffmanNode::HuffmanNode(int w,shared_ptr<HuffmanNode> l,shared_ptr<HuffmanNode> r):weight(w),
left(l),right(r)
{

}

bool operator< (shared_ptr<HuffmanNode> a, shared_ptr<HuffmanNode> b)
{
	return a->weight > b->weight;
}

void
HuffmanNode::setWord(const string& w)
{
	word = w;
}

string
HuffmanNode::getWord()
{
	return word;
}

void HuffmanNode::SetCode(string c)
{
	if (this->left)
		this->left->SetCode(c + '0');
	if (this->right)
		this->right->SetCode(c + '1');
	
	if (!this->left && !this->right)
		code = c;
}

shared_ptr<HuffmanNode>
mergeHuffmanTree(shared_ptr<HuffmanNode> left,shared_ptr<HuffmanNode> right)
{	
	int sumWeight = left->weight + right->weight;
	shared_ptr<HuffmanNode> newRoot = make_shared<HuffmanNode>(sumWeight,left,right);
	return newRoot;

}

shared_ptr<HuffmanNode> 
createHuffmanTree(const map<string,int>& wordCount)
{
	priority_queue<shared_ptr<HuffmanNode>> forest;
	for (const auto& wc:wordCount)
	{
		shared_ptr<HuffmanNode> node = make_shared<HuffmanNode>(wc.second);
		node->setWord(wc.first);
		forest.push(node);
	}


	while (forest.size() > 1)
	{
		auto minTree = forest.top();
		forest.pop();
		auto nextTree = forest.top();
		forest.pop();

		cout << "left:" << minTree->weight << "  right:" << nextTree->weight << endl;
		auto newTree = mergeHuffmanTree(minTree,nextTree);
		forest.push(newTree);
	}

	auto Tree = forest.top();
	Tree->SetCode();
	return Tree;
}

void traverseTree(shared_ptr<HuffmanNode> root)
{
	if (root->left)
		traverseTree(root->left);
	if (root->right)
		traverseTree(root->right);

	if (!root->left && !root->right)
	{
		cout << root->getWord() << ":" << root->code << endl;
	}
}

int main()
{
	map<string,int> wordCount;
	wordCount.insert(make_pair("a",10));
	wordCount.insert(make_pair("e",15));
	wordCount.insert(make_pair("i",12));
	wordCount.insert(make_pair("s",3));
	wordCount.insert(make_pair("t",4));
	wordCount.insert(make_pair("sp",13));
	wordCount.insert(make_pair("nl",1));

	auto huffmanTree = createHuffmanTree(wordCount);
	traverseTree(huffmanTree);

	return 0;
}




