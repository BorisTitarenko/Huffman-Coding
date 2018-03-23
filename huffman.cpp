#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;
map <char, string> m;
string answer = "";
string table = "";
struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r){return (l->freq > r->freq);}
};

void printCodes(struct MinHeapNode* root, string str)
{
     if (!root)
        return;
 
    if (root->data != '$'){
		string s(1, root->data);
        table +=  ( s + ": " + str + "\n");
        m[root->data] = str;
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
    
}
void HuffmanCodes(char data[], int freq[], int size)
{
	struct MinHeapNode *left, *right, *top;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
 
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
 
        top->left = left;
        top->right = right;
 
        minHeap.push(top);
    }
	if(size == 1){printCodes(minHeap.top(), "0"); return;}
    
    printCodes(minHeap.top(), "");
}
int mas(string a, char arr[], int freq[]){
    int size_arr = 1, i = 0, j = 0;
    arr[0] = a[0];
    freq[0] = 1;
    for(i = 1; i != a.size(); ++i){
        int flag = 0;
        for(j = 0; j < size_arr; j++){
            if(a[i] == arr[j]) {++freq[j]; flag = 1;}
        }
        if(!flag){arr[size_arr] = a[i]; freq[size_arr] = 1; size_arr++;}
    }
    return size_arr;
}
void output_string(string a){
	for(int i = 0; i != a.size(); ++i){
		map <char, string> ::iterator j = m.begin();
	
		for(j; j != m.end(); ++j){
			if(a[i] == j->first){
				answer+= j->second;
				//cout << j->second;
			}
		}
	}
}
int main() {
    string a;
    cin >> a;
    char arr[100];
    int freq[100];
    int size = mas(a, arr, freq);
	HuffmanCodes(arr, freq, size);
	output_string(a);
    cout << size << " " << answer.size() << endl;
    cout << table;
    cout << answer;
    
  return 0;
}