#include "Chaining.h"
std::vector<std::vector<Account>> bankStorage2d;

Chaining::Chaining(){
    bankStorage2d.resize(1000039);
}
void Chaining::createAccount(std::string id, int count) {
    int idx = hash(id);
    Account A1 = {id,count};
    bankStorage2d[idx].push_back(A1);
    size++;
}

std::vector<Account> Chaining::merge(std::vector<Account>& l, std::vector<Account>& r, int k) {
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
std::vector<Account> Chaining::mergesort(std::vector<Account>& p, int k) {
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
std::vector<int> Chaining::getTopK(int k) {
    std::vector<Account> v;
    for (const std::vector<Account>& lst : bankStorage2d) {
        for (const Account& A1 : lst) {
            v.push_back(A1);
        }
    }
    std::vector<Account> acc_sorted = mergesort(v, k);
    std::vector<int> topk;
    for (int i = 0; i < k && i < acc_sorted.size(); ++i) {
        topk.push_back(acc_sorted[i].balance);
    }
    return topk;
}

int Chaining::getBalance(std::string id) {
    int idx = hash(id);
    const std::vector<Account>& lst = bankStorage2d[idx];
    for(auto itr = begin(lst); itr != end(lst); ++itr){
        if(itr->id == id){
            return itr->balance;
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    int idx = hash(id);
    std::vector<Account>& lst = bankStorage2d[idx];
    bool exists = false;
    for(auto itr = begin(lst); itr != end(lst); ++itr){
        if(itr->id == id){
            exists= true;
            itr->balance += count;
            break;
        }
    }
    if(!exists){
        createAccount(id,count);
    } 
}

bool Chaining::doesExist(std::string id) {
    int idx = hash(id);
    const std::vector<Account>& lst = bankStorage2d[idx];
    for(auto itr = begin(lst); itr != end(lst); ++itr){
        if(itr->id == id){
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int idx = hash(id);
    std::vector<Account>& lst = bankStorage2d[idx];
    for(auto itr = begin(lst); itr != end(lst); ++itr){
        if(itr->id == id){
            lst.erase(itr);
            size--;
            return true;
            
        }
    }
    return false; 
}

int Chaining::databaseSize() {
    return size; 
}

static const int prime = 7109;

int Chaining::hash(std::string id) {
    int sum = 0;
    int s = id.length();
    for(int i = 0; i<s; i++){
        sum = sum*7 + int(id[i]);
    }
    if(sum>=0){
        return sum% prime;}
    else{
        return (-sum)%prime;
    } 
}