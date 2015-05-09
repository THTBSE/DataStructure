#include <map>
#include <memory>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

class HuffmanNode
{
public:
	HuffmanNode(int w,shared_ptr<HuffmanNode> l=nullptr,shared_ptr<HuffmanNode> r=nullptr);
	shared_ptr<HuffmanNode> left,right;
	string code;
	int weight;
	void setWord(const string& w);
	string getWord();
	void SetCode(string c = "");

	friend bool operator< (shared_ptr<HuffmanNode> a,shared_ptr<HuffmanNode> b);
private:
	string word;
};


shared_ptr<HuffmanNode> createHuffmanTree(const map<string,int>& wordCount);
shared_ptr<HuffmanNode> mergeHuffmanTree(shared_ptr<HuffmanNode> left,shared_ptr<HuffmanNode> right);