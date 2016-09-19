#include <iostream>
#include <stack>

#include "BinomialQueue.h"

using namespace std;

BQ::node::node(int x=0)
{
    data=x;
    child = nullptr;
    sibling = nullptr;
}

BQ::BQ()
{
    theArray = new node*[1];

    theArray[0]= nullptr;

    theCapacity = 1;
    theSize =0;
}

BQ::~BQ()
{
    ClearArray();

    delete theArray;
}

void BQ::Insert(int val)
{
    node *newNode  = new node(val);//the binomial tree we want to insert

    bool isFull=true;
    int i =0;
    if(!theArray[0])
    {
        theArray[0]=newNode;
    }
    else
    {
        while (isFull)
        {
            newNode = CombineTrees(theArray[i],newNode);
            theArray[i]=nullptr;
            if(i+1==theCapacity)
            {
                Resize();
            }
            if(!theArray[i+1])//if there is an empty space we insert the tree
            {
                theArray[i+1]=newNode;
                isFull = false;
            }
            i++;
        }
    }

    theSize++;
}

void BQ::Merge(BQ &otherBQ)
{
    theSize+=otherBQ.theSize;
    for(int i=0;i<otherBQ.theCapacity;i++)
    {
        if(theArray[i]&&otherBQ.theArray[i])//if neither index is null
        {
            bool isFull=true;
            int j =i;
            node *newNode = otherBQ.theArray[i];
            while (isFull)
            {
                newNode = CombineTrees(theArray[j],newNode);
                theArray[j]=nullptr;
                if(j+1==theCapacity)
                {
                    Resize();
                }
                if(!theArray[j+1])//if there is an empty space we insert the tree
                {
                    theArray[j+1]=newNode;
                    isFull = false;
                }
                j++;
            }
        }
        else if(otherBQ.theArray[i])
        {
            theArray[i]=otherBQ.theArray[i];
        }
        otherBQ.theArray[i]=nullptr;
    }
    otherBQ.theSize =0;
}

int BQ::DeleteMin()
{
    if(theSize<1)
    {
        return false;
    }

    int minIndex=-1;
    int minVal;
    int originalSize= theSize;//we keep track of the original size to cancel out the theSize change made by the call to Merge() below
    for(int i=0; i<theCapacity; i++)//we scan theArray to find the smallest root of all binomial trees
    {
        if(minIndex<0)
        {
            if(theArray[i])
            {
                minIndex=i;
                minVal=theArray[i]->data;
            }
        }
        else if(theArray[i]&&theArray[i]->data<=minVal)
        {
            minIndex=i;
            minVal=theArray[i]->data;
        }
    }

    node *reader = theArray[minIndex]->child;
    theArray[minIndex] = nullptr;//We want 2 BQ's. The original BQ now has the relevant root's tree missing.
    BQ temp;//The temporary BQ which we merge with the relevant BQ is composed of all the nodes removed from the original BQ
    stack<node*> p;//We use a stack to simulate recursion
    unsigned index=0;//The index at which we insert the relevant TREE (we do not use Insert(), which inserts values, not trees)

    while(reader)
    {
        p.push(reader);
        reader=reader->sibling;//each sibling will be turned into the root of a tree in the temporary BQ
    }
    while(!p.empty())
    {
        if(index==temp.theCapacity)
        {
            temp.Resize();
        }
        temp.theArray[index] = p.top();
        temp.theArray[index]->sibling = nullptr;
        p.pop();
        index++;
    }

    Merge(temp);
    theSize=originalSize;
    theSize--;

    return minVal;
}

int BQ::GetSize()
{
    return theSize;
}

BQ::node* BQ::CombineTrees(node* t1, node* t2)
{
    if(t1->data<=t2->data)//inclusions of '=' accounts for equivalent root values
    {
        t2->sibling = t1->child;
        t1->child = t2;
    }
    else if(t2->data<t1->data)
    {
        t1->sibling = t2->child;
        t2->child = t1;
    }
}

void BQ::TestRoutine()//prints all the values in the queue
{
    for(int i =0; i<theCapacity; i++)
    {
        node *reader = theArray[i];
        if(theArray[i])
        {
            RecursionCheck(reader);
        }
    }
}

void BQ::RecursionCheck(node *reader)
{
    cout<<reader->data<<"\n";
    if(reader->child)
    {
        RecursionCheck(reader->child);
    }
    if(reader->sibling)
    {
        RecursionCheck(reader->sibling);
    }
}

void BQ::ClearArray()
{
    for(int i=0; i<theCapacity; i++)
    {
        if(theArray[i])
        {
            ClearTree(theArray[i]);
            theArray[i]=nullptr;
        }
    }
}

void BQ::ClearTree(node *reader)
{
    if(reader->child)
    {
        ClearTree(reader->child);
    }
    if(reader->sibling)
    {
        ClearTree(reader->sibling);
    }
    delete reader;
}

void BQ::Resize()
{
    node **tempArray = new node*[theCapacity*2];

    for(int i=0; i<theCapacity*2; i++)
    {
        if(i<theCapacity)
        {
            tempArray[i]=theArray[i];
        }
        else
        {
            tempArray[i]=nullptr;
        }
    }

    delete theArray;
    theArray = tempArray;

    theCapacity*=2;
}

int main()
{
    BQ p;



    p.Insert(5);
        p.Insert(6);
p.Insert(-4);
           p.Insert(8);
             p.Insert(10);
               p.Insert(12);
                 p.Insert(1);
                 p.Insert(121);
                   p.Insert(1211);

//
    BQ g;
    g.Insert (80);
    g.Insert(5000);
    g.Insert(41);
    g.Insert(891);
    g.Insert(-4);

    g.Insert(599);
        g.Insert(47476);
            g.Insert(31);
    p.Merge(g);
int nowSize = p.GetSize();

    for(int i=0;i<nowSize;i++)
    {
         cout<<p.DeleteMin()<<"\n";
    }

//    cout<<p.GetSize()<<"\n";
//p.DeleteMin();
////
//p.DeleteMin();

//      p.TestRoutine();


}
