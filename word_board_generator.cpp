#include <bits/stdc++.h>
#define lint long long
#define st first
#define nd second
#define MAXN 10000

using namespace std;

class TrieNode{
public:
    bool isEnd;
    map<char,TrieNode*> child;
    string word;
    
    TrieNode(){
        isEnd = false;
        word="";
    } 
    void insertNode(TrieNode* root,string &word){
        TrieNode* it = root;
        
        for(int i=0; i < word.size(); i++){
            if(it->child.find(word[i]) == it->child.end()){
                it->child[word[i]]= new TrieNode();   
            }
            it = it->child[word[i]];
        }
            
        it->word = word;
        it->isEnd =true;
    }
        
};



class boardGenerator {
public:


    vector<vector<char>> randomBoard(int numRows, int numCols, int idx){
        vector<vector<char>>board(numRows, vector<char>(numCols));
        
        unsigned seed = idx;

        srand(seed);
        for(int i=0;i<numRows;i++){
            for(int j=0;j<numCols;j++){
                board[i][j] = char(97 +rand()% 26);
            }
        
        }
        return board;

    }
    void dfs(vector<vector<char>> &board, vector<string> &ans, int i, int j, TrieNode* root){

        if(root->isEnd){
            ans.push_back(root->word);
            root->isEnd = false; 
            return;
        }
        if(board[i][j]=='#')
            return;

        char letter = board[i][j];
        if(root->child.find(letter) != root->child.end()){
            board[i][j]='#';
            for(int di:{1, 0, -1}){
                for(int dj:{1, 0, -1}){
                    if(!di && !dj) continue;
                    int pi = di + i;
                    int pj = dj + j;
                    if( pi>=0 && pi < board.size() && pj >= 0 && pj < board[0].size()){
                        dfs(board, ans, pi, pj, root->child[letter]);
                        
                    }
                }
            }

            board[i][j]=letter;
        }

 
    }
    void findWords (int numRows, int numCols, vector<string>& words, int idx){

        vector<vector<char>>board = this->randomBoard(numRows, numCols, idx);
        vector<string> ans;
        TrieNode* root = new TrieNode();
        for(string &word : words){

            root->insertNode(root,word);
        }
    
        
        for(int i=0;i<numRows;i++){    
            for(int j=0;j<numCols;j++){
                this->dfs(board, ans, i, j, root);
            }
        }
       
        if(ans.size() >= 5){
            cout << "indice: " << idx << '\n';
            for(string s:ans){
                cout << s << ' ';
            }
            cout << '\n';
            for(int i=0;i<numRows;i++){    
                for(int j=0;j<numCols;j++){
                    cout << board[i][j] << ' ';
                }
                cout << '\n';
            }
        } 



    }
};


int main(){
    boardGenerator* generator = new boardGenerator();
    string word;
    vector<string>words;
    int boardsToGenerate = 30;
    int idx = 0;
    while(cin >> word){
       words.push_back(word);
    }
    while (boardsToGenerate--){
        generator->findWords(4, 4, words, idx);
        idx++;
    }
    


    return 0;
}