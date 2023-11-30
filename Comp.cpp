#include "Comp.h"

Comp::Comp(){
    bankStorage2d.resize(1000039);
}
void Comp::createAccount(std::string id, int count) {
    int idx = hash(id);
    Account A1 = {id,count};
    bankStorage2d[idx].push_back(A1);
    size++;
}

std::vector<Account> Comp::merge(std::vector<Account>& l, std::vector<Account>& r, int k) {
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
std::vector<Account> Comp::mergesort(std::vector<Account>& p, int k) {
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
std::vector<int> Comp::getTopK(int k) {
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

int Comp::getBalance(std::string id) {
    int idx = hash(id);
    const std::vector<Account>& lst = bankStorage2d[idx];
    for(auto itr = begin(lst); itr != end(lst); ++itr){
        if(itr->id == id){
            return itr->balance;
        }
    }
    return -1;
}

void Comp::addTransaction(std::string id, int count) {
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

bool Comp::doesExist(std::string id) {
    int idx = hash(id);
    const std::vector<Account>& lst = bankStorage2d[idx];
    for(auto itr = begin(lst); itr != end(lst); ++itr){
        if(itr->id == id){
            return true;
        }
    }
    return false;
}

bool Comp::deleteAccount(std::string id) {
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

int Comp::databaseSize() {
    return size; 
}

static const int prime = 7109;

int Comp::hash(std::string id) {
    int sum = 0;
    int s = id.length();
    for (int i = 0; i < s; i++) {
        if (id[i] != '_') {
            sum = (sum + (i + 1) * int(id[i])) % prime;
        }
    }
    return sum;
}