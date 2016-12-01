using namespace std;
#define putstr(i,j) (i==j+1?"":s.substr(j+1,i-j-1))
vector<string> split(string s){
    vector<string> v; 
    for(int i=0,j=-1;i<=s.size();++i){
        if(i==s.size() || s[i] == ','){
            v.push_back(putstr(i,j));
            j = i;
        }
    }
    return v;
}

