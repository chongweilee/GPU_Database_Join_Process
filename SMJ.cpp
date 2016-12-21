#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <thread>
#include "util.h"
#define snd (i+1)*entS.size()/tnum-1
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
    bool operator< (const data& b)const{
        return key < b.key;
    }
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
    sort(ent.begin(),ent.end());
    return data(lb,hdr);
}
bool comp(data r, data s){
    return r.key<s.key;
}

vector<data> entR,entS;
int tnum=16;
vector< vector<data> > entJ(tnum);
void run (int i){
    int s = i*entS.size()/tnum;
    int r = lower_bound(entR.begin(),entR.end(),entS[s])-entR.begin();
    int rnd = upper_bound(entR.begin(),entR.end(),entS[snd])-entR.begin();

    while(r<rnd && s<(i+1)*entS.size()/tnum){
        //cout<<entR[r].key<<"    "<<entS[s].key<<endl;
        if(entR[r].key<entS[s].key){
            r+=1;
        }
        else if(entR[r].key>entS[s].key){
            s+=1;
        }
        else{
            entJ[i].emplace_back(entR[r].key,entR[r].val+","+entS[s].val);
            r+=1, s+=1;
        }
    }
}
int main(){
    string tmp,cmp;
    vector<bool> lbR,lbS;
    ofstream jout("J.csv");
    data hR,hS;
    cin>>cmp;
    hR = input(entR,lbR,"R.csv",cmp);
    hS = input(entS,lbS,"S.csv",cmp);

    vector<thread> thrd;
    for(int i=0;i<tnum;++i){ 
        thrd.emplace_back(run,i);
    }

    for(int i=0;i<tnum;++i){ 
        thrd[i].join();
    }
    /* 
    jout<<hR.key<<","<<hR.val<<","<<hS.val<<endl;
    for(int i=0;i<entJ.size();++i){
        for(int j=0;j<entJ[i].size();++j){
            jout<<entJ[i][j].key<<","<<entJ[i][j].val<<endl;
        }
    }
    */
}
