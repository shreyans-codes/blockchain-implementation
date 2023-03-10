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
    void setValuesFromUser()
    {
        cout << "Enter sender id: ";
        getline(cin, senderId);
        cout << "Enter reciever id: ";
        getline(cin, recieverId);
        cout << "Enter sender name: ";
        getline(cin, senderName);
        cout << "Enter reciever name: ";
        getline(cin, recieverName);
        cout << "Enter description: ";
        getline(cin, description);
        cout << "Enter date: ";
        getline(cin, transactionDate);
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
    void setTransactionValues()
    {
        int ch;
        cout << "Enter transaction details: \n";
        do
        {
            cout << "Enter 0 to stop: ";
            cin >> ch;
            if (ch != 0)
            {
                Transaction temp = Transaction();
                temp.setValuesFromUser();
                transactions.push_back(temp);
            }
        } while (ch != 0);
    }
    void setBlockHash(int pHash, int tHash)
    {
        hash<string> cHash;
        blockHash = cHash(to_string(pHash + tHash));
    }
    Block(int pHash, vector<Transaction> tr)
    {
        previousHash = pHash;
        transactions = tr;
        int transactionHash = generateTransactionHash();
        setBlockHash(previousHash, transactionHash);
    }
    Block(int pHash)
    {
        previousHash = pHash;
        setTransactionValues();
        int transactionHash = generateTransactionHash();
        setBlockHash(previousHash, transactionHash);
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

void buildBlockList(BlockNode *head)
{
    int choice;
    BlockNode *temp = head;
    do
    {
        cout << "Enter 1 to add a new block\nEnter 0 to exit\nYour choice: ";
        cin >> choice;
        if (choice == 1)
        {
            Block newBlock = Block(temp->block.blockHash);
            BlockNode *nextBlock = new BlockNode(newBlock);
            temp->next = nextBlock;
            temp = temp->next;
        }
    } while (choice != 0);
}

void printBlockList(BlockNode *head)
{
    BlockNode *temp = head;
    int i = 1;
    while (temp != NULL)
    {
        cout << "Details for block " << i << " : " << endl;
        cout << "Transactions: " << endl;
        for (int j = 0; j < temp->block.transactions.size(); j++)
        {
            cout << j + 1 << " -> " << temp->block.transactions[j].description << endl;
        }
        cout << "Hash Value: " << temp->block.blockHash << endl;
        temp = temp->next;
        i++;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    vector<Transaction> tr;
    Transaction t1;
    string vals[] = {"001", "010", "Shreyans", "Rudransh", "Shreyans sent 10 bitcoins to Rudransh", "08-03-2023"};
    t1.setValues(vals);
    tr.push_back(t1);
    Block genesisBlock = Block(1, tr);
    cout << "Hash = " << genesisBlock.blockHash << endl;
    BlockNode genesisBlockNode = BlockNode(genesisBlock);
    BlockNode *headNode = &genesisBlockNode;
    buildBlockList(headNode);
    printBlockList(headNode);
}