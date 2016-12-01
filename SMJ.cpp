#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "util.h"

using namespace std;

struct data{
    data(vector<bool>& lb, string line){
        vector<string> col = split(line);
        if(col.size()!=lb.size()){
            cerr<<"wrong! "<<line<<endl;
        }
        else{
            for(int i=0;i<lb.size();++i){
                (lb[i]?key:val) += col[i] + ",";
            }
            if(!key.empty()) key.pop_back();
            if(!val.empty()) val.pop_back();
        }
    }
    string key,val;
};

vector<bool> target(string sref,string shdr){
    vector<string> ref = split(sref);
    vector<string> hdr = split(shdr);
    vector<bool> lb(hdr.size());
    for(int i=0;i<ref.size();++i){
        for(int j=0;j<hdr.size();++j){
            if(ref[i] == hdr[j]){
                lb[j] = 1;
            }
        }
    }
    return lb;
}

bool compare(data& a, data& b){
    return a.key < b.key;
}

void input(vector<data>& ent, vector<bool>& lb, string f, string cmp){
    string tmp;
    ifstream rin(f);
    getline(rin,tmp);
    lb = target(cmp,tmp);
    while(getline(rin,tmp)){
        ent.emplace_back(lb,tmp);
    }
    sort(ent.begin(),ent.end(),compare);
}

int main(){
    string tmp,cmp;
    vector<bool> lbR,lbS;
    vector<data> entR,entS;
    cin>>cmp;
    input(entR,lbR,"R.csv",cmp);
    input(entS,lbS,"S.csv",cmp);
}
