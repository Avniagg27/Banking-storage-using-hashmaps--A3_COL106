#include "LinearProbing.h"

Account LinearProbing::empty = {"",0};

LinearProbing::LinearProbing():siz(0){
    bankStorage1d.resize(prime);
    for(int i=0; i<prime;i++){
        bankStorage1d[i]= empty;
    }
}
void LinearProbing::createAccount(std::string id, int count) {    
    int idx = hash(id);
    while(bankStorage1d[idx].id != "" && bankStorage1d[idx].id !="!"){
        idx = (idx+1)%capacity;
    }
    bankStorage1d[idx] = {id,count};
    siz++;
    return;
}

std::vector<Account> LinearProbing::merge(std::vector<Account>& l, std::vector<Account>& r, int k) {
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

std::vector<Account> LinearProbing::mergesort(std::vector<Account>& p, int k) {
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
std::vector<int> LinearProbing::getTopK(int k) {
    std::vector<Account> v;
    for (int i = 0; i < capacity; ++i) {
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

int LinearProbing::getBalance(std::string id) {
    int idx = hash(id);
    while(bankStorage1d[idx].id!=""){
        if(bankStorage1d[idx].id == id){
            return bankStorage1d[idx].balance;
        }
        else{
            idx = (idx+1)%capacity;}
    }
    return -1; 
}

void LinearProbing::addTransaction(std::string id, int count) {
    int idx = hash(id);
    while(bankStorage1d[idx].id!=""){
        if(bankStorage1d[idx].id == id){
            bankStorage1d[idx].balance += count;
            return;
        }
        else{
        idx = (idx+1)%capacity;}
    }
    createAccount(id,count);
    
}

bool LinearProbing::doesExist(std::string id) {
    int idx = hash(id);
    while(bankStorage1d[idx].id!=""){
        if(bankStorage1d[idx].id == id){
            return true;
        }
        else{
        idx = (idx+1)%capacity;}
    }
    return false; 
}

bool LinearProbing::deleteAccount(std::string id) {
    int idx = hash(id);
    while(bankStorage1d[idx].id!=""){
        if(bankStorage1d[idx].id == id){
            bankStorage1d[idx]= {"!",0};
            siz--;
            return true;
        }
        else{
        idx = (idx+1)%capacity;}
    }
    return false; 
}

int LinearProbing::databaseSize() {
    return siz; 
}

static const int prime = 1000039;
int LinearProbing::hash(std::string id) {
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
