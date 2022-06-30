#include<bits/stdc++.h>
using namespace std;

struct TreeNode{
    char character;
    int frequency;
    TreeNode* left;
    TreeNode* right;
    TreeNode(){}
    TreeNode(int frequency,TreeNode* left,TreeNode* right){
        this->frequency = frequency;
        this->left=left;
        this->right=right;
    }
};

struct cmp{
    bool operator()(TreeNode* &n1,TreeNode* &n2){
        return n1->frequency > n2->frequency;
    }
};


class HuffmanCompressor{
private:
    priority_queue<TreeNode*,vector<TreeNode*>,cmp> pq;
    map<char,string> prefixCodes;
    map<char,int> hashMap;
    TreeNode* root;
    string fileName;
public:
    HuffmanCompressor(string);
    void AssignPrefixCode(TreeNode*,string&);
    void HashInputFile();
    void Encode();
    void WriteDecodingFile();
    void ConstructPrefixTree();
};

HuffmanCompressor::HuffmanCompressor(string s){
    this->fileName= s;
    ifstream fin;
    fin.open(fileName);
    if(!fin){
        cout<<"Specified file does not exist !!!"<<endl;

    }
    else{
        HashInputFile();
        ConstructPrefixTree();
        string code = "";
        AssignPrefixCode(root,code);
        WriteDecodingFile();
        Encode();
        cout<<"File successfully compressed "<<endl;
    }
}

void HuffmanCompressor::AssignPrefixCode(TreeNode* node,string &code){
    if(node->left == NULL && node->right == NULL){
        prefixCodes[node->character] = code;
    }
    else{
        if(node->left){
            code.push_back('0');
            AssignPrefixCode(node->left,code);
            code.pop_back();
        }
        if(node->right){
            code.push_back('1');
            AssignPrefixCode(node->right,code);
            code.pop_back();
        }
    }
}

void HuffmanCompressor::HashInputFile(){
    ifstream fin;
    fin.open(fileName);
    char ch;
    ch = fin.get();
    while (fin.eof() == 0) {
        hashMap[ch]++;
        ch = fin.get();
    }
    fin.close();
}

void HuffmanCompressor::Encode(){
    ifstream fin;
    ofstream fout;
    string compressedFileName = fileName+"_compressed.txt";
    fout.open(compressedFileName);
    fin.open(fileName);
    char ch = fin.get();
    while(fin.eof() == 0){
        fout<<prefixCodes[ch]<<endl;
        ch = fin.get();
    }
    fin.close();
    fout.close();
}

void HuffmanCompressor::WriteDecodingFile(){
    ofstream fout;
    string decodingFileName = fileName+"_decode.txt";
    fout.open(decodingFileName);
    for(auto prefixCode : prefixCodes){
        fout<<prefixCode.second<<' '<<prefixCode.first<<endl;
    }
    fout.close();
}

void HuffmanCompressor::ConstructPrefixTree(){

    for(auto pair : hashMap){
        TreeNode* node = new TreeNode();
        node->character = pair.first;
        node->frequency = pair.second;
        node->left = NULL;
        node->right = NULL;
        pq.push(node);
    }

    while(pq.size() != 1){
        TreeNode* tree1 = pq.top();
        pq.pop();
        TreeNode* tree2 = pq.top();
        pq.pop();
        if(tree1->frequency > tree2->frequency) 
            swap(tree1,tree2);
        // tree 1 always comes left and tree 2 always right
        int sum = tree1->frequency+tree2->frequency;
        TreeNode* tree=new TreeNode(sum,tree1,tree2);
        pq.push(tree);
    }
    root = pq.top();
}
int main(int argc,char* argv[]){
    if(argc != 2){
        cout<<"Please provide file name in argument to compress !!!!"<<endl;
        return 0;
    }
    HuffmanCompressor huffmanCompressor(argv[1]);
    return 0;
}