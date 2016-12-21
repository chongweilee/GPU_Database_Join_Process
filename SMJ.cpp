#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "util.h"

using namespace std;

struct data{
    data(){}
    data(string k, string v){
        key = k;
        val = v;
    }
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

data input(vector<data>& ent, vector<bool>& lb, string f, string cmp){
    string tmp,hdr;
    ifstream rin(f);
    getline(rin,hdr);
    lb = target(cmp,hdr);
    while(getline(rin,tmp)){
        ent.emplace_back(lb,tmp);
    }
    sort(ent.begin(),ent.end(),compare);
    return data(lb,hdr);
}

int main(){
    string tmp,cmp;
    vector<bool> lbR,lbS;
    ofstream jout("J.csv");
    data hR,hS;
    vector<data> entR,entS,entJ;
    cin>>cmp;
    hR = input(entR,lbR,"R.csv",cmp);
    hS = input(entS,lbS,"S.csv",cmp);
    int r=0,s=0;
    while(r<entR.size() && s<entS.size()){
        //cout<<entR[r].key<<"    "<<entS[s].key<<endl;
        if(entR[r].key<entS[s].key){
            r+=1;
        }
        else if(entR[r].key>entS[s].key){
            s+=1;
        }
        else{
            entJ.emplace_back(entR[r].key,entR[r].val+","+entS[s].val);
            r+=1;
            s+=1;
        }
    }
    /*
    jout<<hR.key<<","<<hR.val<<","<<hS.val<<endl;
    for(int i=0;i<entJ.size();++i){
        jout<<entJ[i].key<<","<<entJ[i].val<<endl;
    }
    */
}
