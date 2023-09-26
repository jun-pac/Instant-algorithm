

#include <bits/stdc++.h>

using namespace std;

#define NUM_ALPHA 26

class node{
public:
    node* next[NUM_ALPHA]={NULL,};
    char val; // ��κ� �ʿ����.
    int cnt=0; // ���⼭ ������ �ܾ���� ����
    node(){}
    node(char c){
        val=c; 
    }
};

class trie{
public:
    node* root= new node();
    trie(){}
    bool is_s(string &s){
        return is_re(root, 0, s);
    }
    void insert_s(string &s){
        insert_re(root, 0, s);
    }
    void clear(){ // clear_all
        clear_re(root);
        for(int i=0; i<NUM_ALPHA; i++) root->next[i]=NULL;
    }

private: 
    bool is_re(node *cur, int idx, string &s){
        if(idx==s.size()) return ((cur->cnt)>=1); // ������� ������ �׳� true�ص� ���� �ʳ�? ó���� ���� �� �����ΰ�
        if((cur->next[s[idx]-'A'])==NULL) return false;
        return is_re(cur->next[s[idx]-'A'],idx+1,s);
    }
    void insert_re(node* cur, int idx, string &s){
        if(idx==s.size()){
            cur->cnt++;
            return;
        }
        if((cur->next[s[idx]-'A'])==NULL) cur->next[s[idx]-'A']=new node(s[idx]);
        insert_re(cur->next[s[idx]-'A'],idx+1,s);
    }
    void clear_re(node* cur){
        for(int i=0; i<NUM_ALPHA; i++){
            if((cur->next[i])!=NULL){
                clear_re(cur->next[i]);
                delete cur->next[i];
            }
        }
    }
};

trie tr;