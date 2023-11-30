#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    LinearProbing();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
private:
    // Other data members and functions specific to Linear Probing
    int find_idx(std::string id);
    int siz = 0;
    int capacity= 1000039;
    static const int prime = 1000039;
    std::vector<Account> mergesort(std::vector<Account>& p, int k);
    std::vector<Account> merge(std::vector<Account>& l, std::vector<Account>& r, int k);
    static Account empty;
};

#endif // LINEARPROBING_H
