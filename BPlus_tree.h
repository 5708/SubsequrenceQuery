#ifndef BPLUS_TREE_H  
#define BPLUS_TREE_H  
 
#include "BPlus_node.h"  
#include <vector>  
#include <Eigen/Dense>
#include "Data.h"

using Eigen::MatrixXd;
using namespace std; 
 
enum COMPARE_OPERATOR{LT, LE, EQ, BE, BT, BETWEEN}; // comparison operator：<、<=、=、>=、>、<>  
const int INVALID_INDEX = -1;
const int FRONT = 0;
const int BACK = 1;
 
struct SelectResult 
{ 
    int keyIndex; 
    CLeafNode* targetNode; 
}; 
 
class CBPlusTree{ 
public: 
    CBPlusTree(); 
    ~CBPlusTree(); 
    bool insert(KeyType key, const DataType& data); 
    bool remove(KeyType key); 
    //bool update(KeyType oldKey, KeyType newKey); 
    // fixed query，compareOperator could be LT(<)、LE(<=)、EQ(=)、BE(>=)、BT(>)  
    vector<DataType> select(KeyType compareKey, int compareOpeartor); 
    // range query，BETWEEN  
    vector<DataType> select(KeyType smallKey, KeyType largeKey); 
    bool search(KeyType key); // search wheter exist  
    void clear();             
    void print()const;        // print tree's key value 
    void printData()const;    // print data  
    void BPTbuild(MatrixXd *m);
	vector<int> rangeQuery(double up, double low);
private: 
    void recursive_insert(CNode* parentNode, KeyType key, const DataType& data); 
    void recursive_remove(CNode* parentNode, KeyType key); 
    void printInConcavo(CNode *pNode, int count)const; 
    bool recursive_search(CNode *pNode, KeyType key)const; 
    void changeKey(CNode *pNode, KeyType oldKey, KeyType newKey); 
    void search(KeyType key, SelectResult& result); 
    void recursive_search(CNode* pNode, KeyType key, SelectResult& result); 
	CNode* recursive_rangeQuery(CNode *pNode, KeyType key, int fb);
    //void remove(KeyType key, DataType& dataValue); 
    //void recursive_remove(CNode* parentNode, KeyType key, DataType& dataValue); 
private:
	int frontIndex, backIndex;
    CNode* m_Root; 
    CLeafNode* m_DataHead; 
    KeyType m_MaxKey;  // find the max key in the tree 
}; 
 
#endif 