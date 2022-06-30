#include<bits/stdc++.h>
using namespace std;

class HuffmanDecompressor{
private:
	map<string,char> m;
	string fileName;
public:
	HuffmanDecompressor(string);
	void Decode();
	void ReadDecodingFile();
};

HuffmanDecompressor::HuffmanDecompressor(string fileName){
	this->fileName=fileName;
	ReadDecodingFile();
	Decode();
}
void HuffmanDecompressor::ReadDecodingFile(){
	string decoderFile = fileName+"_decode.txt";
	ifstream fin;
	fin.open(decoderFile);
	char ch;
	string s;
	while(fin.eof() == 0){
	    fin>>s;
	    fin>>ch;
	    m[s] = ch;
	}
	fin.close();
}
void HuffmanDecompressor::Decode(){
	string decompressedFile = fileName+"_decompressed.txt";
	string compressedFile = fileName+"_compressed.txt";
	ofstream fout;
	ifstream fin;
	fout.open(decompressedFile);
	fin.open(compressedFile);
	string s;
	fin>>s;
	cout<<"Decoded file output : "<<endl;
	while(fin.eof() == 0){
		cout<<m[s];
		fout<<m[s];
		fin>>s;
	}
	cout<<endl<<endl;
}
int main(int argc,char* argv[]){
	if(argc != 2){
        cout<<"Please provide file name in argument to compress !!!!"<<endl;
        return 0;
    }
    HuffmanDecompressor huffmanDeompressor(argv[1]);
    cout<<"File successfully decompressed "<<endl;
	return 0;
}