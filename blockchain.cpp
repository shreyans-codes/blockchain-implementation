#include <bits/stdc++.h>

using namespace std;

class Transaction
{
private:
    string senderId;
    string recieverId;

public:
    string senderName;
    string recieverName;
    string description;
    string transactionDate;
    void setValues(string *vals)
    {
        senderId = vals[0];
        recieverId = vals[1];
        senderName = vals[2];
        recieverName = vals[3];
        description = vals[4];
        transactionDate = vals[5];
    }
    string *getValues()
    {
        string details[4];
        details[0] = senderName;
        details[1] = recieverName;
        details[2] = description;
        details[3] = transactionDate;
        return details;
    }
    int getHash()
    {
        string totalBlockValue = senderId + recieverId + description + transactionDate;
        hash<string> currentBlockHash;
        return currentBlockHash(totalBlockValue);
    }
};

class Block
{
private:
    int previousHash;
    int generateTransactionHash()
    {
        int size = transactions.size();
        if (size >= 1)
        {
            int totalHash = transactions[0].getHash();
            for (int i = 1; i < size; i++)
            {
                int currentHash = transactions[i].getHash();
                hash<string> calculatedHash;
                totalHash = calculatedHash(to_string(currentHash + totalHash));
            }
            return totalHash;
        }
        return -1;
    }

public:
    int blockHash;
    vector<Transaction> transactions;
    Block(int pHash, vector<Transaction> tr)
    {
        previousHash = pHash;
        transactions = tr;
        int transactionHash = generateTransactionHash();
        hash<string> cHash;
        cout << "Transaction Hash = " << transactionHash << endl;
        blockHash = cHash(to_string(previousHash + transactionHash));
    }
    Block() {}
};

class BlockNode
{
public:
    Block block;
    BlockNode *next;
    BlockNode(Block b)
    {
        block = b;
        next = NULL;
    }
};

int main()
{
    vector<Transaction> tr;
    Transaction t1;
    string vals[] = {"001", "010", "Shreyans", "Riya", "Shreyans gave 10 flowers to Riya", "08-03-2023"};
    t1.setValues(vals);
    tr.push_back(t1);
    Block genesisBlock = Block(1, tr);
    cout << "Hash = " << genesisBlock.blockHash << endl;
    BlockNode genesisBlockNode(genesisBlock);
}