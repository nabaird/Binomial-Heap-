#include <iostream>

using namespace std;

class BQ
{
private:
    struct node
    {
        node(int);

        int data;
        node* child;
        node* sibling;

    };

    BQ(BQ&);
    BQ& operator=(BQ&);

public:
    BQ();
    ~BQ();

    void Insert(int);
    int DeleteMin();
    void Merge(BQ&);
    int GetSize();

    void TestRoutine();
    void RecursionCheck(node*);

private:
    void Resize();
    void RecursiveInsert(node*);
    void ClearArray();
    void ClearTree(node*);
    node* CombineTrees(node*, node*);

    node **theArray;
    unsigned theCapacity;
    unsigned theSize;

};
