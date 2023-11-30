#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    Chaining();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    
    int size =0;
    static const int prime = 7109;
    std::vector<Account> mergesort(std::vector<Account>& p, int k);
    std::vector<Account> merge(std::vector<Account>& l, std::vector<Account>& r, int k);
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
