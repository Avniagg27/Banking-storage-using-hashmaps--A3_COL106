#include "CubicProbing.h"

CubicProbing::CubicProbing(){
    int cap = 1000039;
    bankStorage1d.resize(cap);
}

void CubicProbing::createAccount(std::string id, int count) {
    int idx = hash(id);
    int i= 1;
    while(bankStorage1d[idx].id != "" && bankStorage1d[idx].id !="!"){
        idx = (idx+(i*i*i+i*i+i+1))%cap;
        i++;
    }
    bankStorage1d[idx] = {id,count};
    siz++;
}
 
std::vector<Account> CubicProbing::merge(std::vector<Account>& l, std::vector<Account>& r, int k) {
    std::vector<Account> final;
    int first = 0, last = 0;

    while (final.size() < k && (first < l.size() || last < r.size())) {
        if (first < l.size() && (last >= r.size() || l[first].balance >= r[last].balance)) {
            final.push_back(l[first]);
            first++;
        } else {
            final.push_back(r[last]);
            last++;
        }
    }

    return final;
}

std::vector<Account> CubicProbing::mergesort(std::vector<Account>& p, int k) {
    if (p.size() <= 1) {
        return p;
    }

    int mid = p.size() / 2;
    std::vector<Account> l(p.begin(), p.begin() + mid);
    std::vector<Account> r(p.begin() + mid, p.end());

    l = mergesort(l, k);
    r = mergesort(r, k);

    return merge(l, r, k);
}
std::vector<int> CubicProbing::getTopK(int k) {
    std::vector<Account> v;
    for (int i = 0; i < cap; ++i) {
        if (bankStorage1d[i].id != "" && bankStorage1d[i].id != "!") {
            v.push_back(bankStorage1d[i]);
        }
    }

    std::vector<Account> sortedAccounts = mergesort(v, k);

    std::vector<int> topKBalances;
    for (int i = 0; i < k && i < sortedAccounts.size(); ++i) {
        topKBalances.push_back(sortedAccounts[i].balance);
    }

    return topKBalances;
}

int CubicProbing::getBalance(std::string id) {
    int idx = find_idx(id);
    if(idx!= -1){
        return bankStorage1d[idx].balance;
    }
    return -1;
}

void CubicProbing::addTransaction(std::string id, int count) {
    int idx = find_idx(id);
    if(idx != -1){
        bankStorage1d[idx].balance += count;
    }
    else{
        createAccount(id,count);
    }
}

bool CubicProbing::doesExist(std::string id) {
    int idx = find_idx(id);
    if(idx==-1){
        return false;
    }
    return true; 
}

bool CubicProbing::deleteAccount(std::string id) {
    int idx = find_idx(id);
    if(idx != -1){
        bankStorage1d[idx]= {"!",0};
        siz--;
        return true;
    }
    return false;
}
int CubicProbing::databaseSize() {
    return siz;
}
int CubicProbing::find_idx(std::string id){
    int idx  = hash(id);
    while(!bankStorage1d[idx].id.empty()){
        if(bankStorage1d[idx].id == id){
            return idx;
        }
        else{
            for(int i =1; i<cap; i++){
                idx = (idx+(i*i*i + i*i + i + 1))%cap;
                if(bankStorage1d[idx].id==id){
                    return idx;
                }
                
            }
        }
    }
    return -1;
}
static const int prime = 7109;
int CubicProbing::hash(std::string id) {
     int sum = 0;
    int s = id.length();
    for(int i = 0; i<s; i++){
        sum = sum*7 + int(id[i]);
    }
    if(sum>=0){
        return sum%prime;
    }
    else{
        return (-sum)%prime;
    }
}