// Aho-corasic
// Upper-case code임에 주의.

#include <bits/stdc++.h>
using namespace std;

#define NUM_ALPHA 26
#define N 10000

class node{
public:
    node* next[NUM_ALPHA]={NULL,};
    node* pphi; // parent of phi ; i.e. 최대 접미사의 가장 마지막 노드. 다음 원소는 직접 찾아야 함.
    int val; // 부모를 통해 찾아줘도 된다. // 0-based idx of character
    bool end_of_snippet=false; // End node of snippet. Propagated in BFS phase.
    int length_of_snippet; // Only valid of end of snippet is true. Propagated in BFS phase.
    int depth=0; // Actual length of the sequence
    bool end=true; // All next pointers are NULL
    node(){}
    node(int v){
        val=v; 
    }
};

class aho_trie{
public:
    node* root= new node();
    aho_trie(){}
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
    void get_phi(){
        queue<pair<node*,node*>> phi_q; // cur_pos, pphi
        // Unlike KMP, pphi is the deepest pointer that actually matched with cur
        phi_q.push({root,root});
        while(!phi_q.empty()){
            pair<node*,node*> temp=phi_q.front();
            phi_q.pop();
            node* cur=temp.first;
            node* ptar=temp.second;
            if(cur->depth>1){ // To prevent phi[self]=self
                while(ptar!=root && (ptar->next[cur->val]==NULL)) ptar=ptar->pphi;
                if(ptar->next[cur->val]!=NULL) ptar=ptar->next[cur->val];
            }
            cur->pphi=ptar;
            if(!cur->end_of_snippet && ptar->end_of_snippet){
                cur->end_of_snippet=true;
                cur->length_of_snippet=ptar->length_of_snippet;
            }

            for(int i=0; i<NUM_ALPHA; i++){
                if((cur->next[i])!=NULL){
                    phi_q.push({cur->next[i],ptar});
                }
            }
        }
    }
    void find_matching(string &s_ref, vector<int> &ans){
        int n=s_ref.size();
        ans.clear();
        node* ptar=root;
        for(int i=0; i<n; i++){
            int cur=s_ref[i]-'A'; // transition function
            while(ptar!=root && ptar->next[cur]==NULL) ptar=ptar->pphi;
            if(ptar->next[cur]!=NULL) ptar=ptar->next[cur];
            //cout<<(char)(ptar->val+'A')<<' '<<ptar->cnt<<' '<<ptar->depth<<endl;
            if(ptar->end_of_snippet) ans.push_back(i+1-(ptar->length_of_snippet));
            if(ptar->end) ptar=ptar->pphi;
        }
    }

private: 
    bool is_re(node *cur, int idx, string &s){
        if(idx==s.size()) return (cur->end_of_snippet);
        if((cur->next[s[idx]-'A'])==NULL) return false;
        return is_re(cur->next[s[idx]-'A'],idx+1,s);
    }
    void insert_re(node* cur, int idx, string &s){
        if(idx==s.size()){
            cur->end_of_snippet=true;
            cur->length_of_snippet=s.size();
            return;
        }
        cur->end=false;
        if((cur->next[s[idx]-'A'])==NULL){
            cur->next[s[idx]-'A']=new node(s[idx]-'A');
            cur->next[s[idx]-'A']->depth=idx+1;
        }
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

aho_trie aho;