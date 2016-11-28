#include<iostream>
#include<vector>
#include<cstdio>
#include<thread>

using namespace std;

vector<int> x;

void bitonic_compare(bool up, int b, int e){
    int dist = (e-b) / 2, tmp;
    for(int i=b;i<b+dist;++i)
        if ((x[i] > x[i + dist]) == up){
            tmp = x[i + dist];
            x[i + dist] = x[i];
            x[i] = tmp;
        }
}

void bitonic_merge(bool up, int b, int e){
    if(e-b > 1){
        bitonic_compare(up, b, e);
        bitonic_merge(up, b, (b+e)/2);
        bitonic_merge(up, (b+e)/2, e);
    }
}

void bitonic_sort(bool up, int b, int e){
    if(e-b > 1){
        bitonic_sort(1, b, (b+e)/2);
        bitonic_sort(0, (b+e)/2, e);
        bitonic_merge(up, b, e);
    }
}

/*
void bitonic_sort_thread(bool up, int b, int e, int l){
    if(l>0){
        thread fir(bitonic_sort_thread, 1, b, (b+e)/2, l-1);
        thread sec(bitonic_sort_thread, 0, (b+e)/2, e, l-1);
        fir.join();
        sec.join();
    }
    else{
        bitonic_sort(1, b, (b+e)/2);
        bitonic_sort(0, (b+e)/2, e);
    }
    bitonic_merge(up, b, e);
}
*/

int main(){
    int n = (1<<10),tmp,k,j;

    for(int i=1;i<=n;++i){
        x.push_back(i);
    }
    
    for(int i=0;i<n;++i){
        k = rand()%n;
        j = rand()%n;
        tmp = x[k];
        x[k] = x[j];
        x[j] = tmp;
    }

    bitonic_sort(1, 0, n);
    
}
