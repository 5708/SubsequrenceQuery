#include "BPlus_tree.h"
#include "BPlus_node.h"
#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include "Data.h"

using Eigen::MatrixXd;
using namespace std;

int main(){
	CBPlusTree B;
	MatrixXd* matrix = new MatrixXd(3,3);
	(*matrix)<< 11,44,55,
				33,22,66,
				99,88,77;
	Data d;
	d.read("../Data/h20v9EVI1D1_1.txt",10000,285);
	B.BPTbuild(matrix);
	B.print();
	B.printData();
	vector<int> r = B.rangeQuery(33.0,88.0);
	for(int i = 0 ; i < r.size(); ++i)
		cout<<r[i]<<"--";
	cin.get();
}

CBPlusTree::CBPlusTree(){
	m_Root = NULL;
	m_DataHead = NULL;
}

CBPlusTree::~CBPlusTree(){
	clear();
}
void CBPlusTree::BPTbuild(MatrixXd *m){
	int x = m->cols();
	int y = m->rows();
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			//cout<<"i"<<m->data()<<endl;
			KeyType k = (*m)(j,i) ;
			DataType d =j*1000+i;
			insert(k, d);
		}
	}


}
bool CBPlusTree::insert(KeyType key, const DataType& data){
	//whether the key has already existed
	//if (search(key))
	//{
	// return false;
	//}

	// find the leaf node can be inserted or create a new leaf node 
	if(m_Root==NULL) 
	{
		m_Root = new CLeafNode();
		m_DataHead = (CLeafNode*)m_Root;
		m_MaxKey = key;
	}
	if (m_Root->getKeyNum()>=MAXNUM_KEY) // if the rood node is full, then split
	{
		CInternalNode* newNode = new CInternalNode();  //create new rood node
		newNode->setChild(0, m_Root);
		m_Root->split(newNode, 0);    // split leafnode
		m_Root = newNode;  //update root node
	}
	if (key>m_MaxKey)  //update the largest key
	{
		m_MaxKey = key;
	}
	recursive_insert(m_Root, key, data);
	return true;
}

void CBPlusTree::recursive_insert(CNode* parentNode, KeyType key, const DataType& data)
{
	if (parentNode->getType()==LEAF)  // if leaf node, then insert
	{
		((CLeafNode*)parentNode)->insert(key, data);
	}
	else
	{
		// find child node
		int keyIndex = parentNode->getKeyIndex(key);
		int childIndex= parentNode->getChildIndex(key, keyIndex); // get child node index
		CNode* childNode = ((CInternalNode*)parentNode)->getChild(childIndex);
		if (childNode->getKeyNum()>=MAXNUM_LEAF)  // if child node is full, then split
		{
			childNode->split(parentNode, childIndex);     
			if (parentNode->getKeyValue(childIndex)<=key)   // find the target child
			{
				childNode = ((CInternalNode*)parentNode)->getChild(childIndex+1);
			}
		}
		recursive_insert(childNode, key, data);
	}
}

void CBPlusTree::clear()
{
	if (m_Root!=NULL)
	{
		m_Root->clear();
		delete m_Root;
		m_Root = NULL;
		m_DataHead = NULL;
	}
}
vector<int> CBPlusTree::rangeQuery(double up, double low)
{
	vector<int> rangeResult;
	int endIndex;
	bool terminal = false;
	/*cout<<m_Root->getKeyIndex(34)<<endl;
	cout<<m_Root->getKeyValue(0)<<endl;
	cout<<m_Root->getKeyValue(1)<<endl;
	cout<<m_Root->getKeyValue(2)<<endl;
	cout<<m_Root->getChildIndex(33,3)<<endl;
	cout<<((CLeafNode*)m_Root)->getData(3);*/
	if (up < low)
	{
		CNode* fn = recursive_rangeQuery(m_Root, up, FRONT);
		CNode* bn = recursive_rangeQuery(m_Root, low, BACK);
		while(!terminal)
		{
			if(fn == bn)
			{
				while(frontIndex != backIndex)
				{
					rangeResult.push_back(((CLeafNode*)fn)->getData(frontIndex));
					frontIndex++;
				}
				terminal = true;
			}
			else
			{
				endIndex = fn->getKeyNum();
				while(frontIndex != endIndex)
				{
					rangeResult.push_back(((CLeafNode*)fn)->getData(frontIndex));
					frontIndex++;
				}
				fn = ((CLeafNode*)fn)->getRightSibling();
			}
		}
	}
	return rangeResult;
}
CNode* CBPlusTree::recursive_rangeQuery(CNode *pNode, KeyType key, int fb)
{
	if (pNode==NULL)  //check wheter the node's pointer is empty or the node is leaf node
	{    
		return NULL;
	}
	else
	{
		int keyIndex = pNode->getKeyIndex(key);
		int childIndex = pNode->getChildIndex(key, keyIndex); // the child node index pointer
		if (pNode->getType() == LEAF)
		{
			if (fb == FRONT)
			{
				frontIndex = keyIndex;
			}
			else
			{
				backIndex = keyIndex;
				if(pNode->getKeyValue(keyIndex) == key)
				{
					backIndex ++;
				}
			}
			return pNode;
		}
		else
		{
			return recursive_rangeQuery(((CInternalNode*)pNode)->getChild(childIndex),key,fb);
		}
	}
}
bool CBPlusTree::search(KeyType key)
{
	return recursive_search(m_Root, key);
}

bool CBPlusTree::recursive_search(CNode *pNode, KeyType key)const
{
	if (pNode==NULL)  //check wheter the node's pointer is empty or the node is leaf node
	{    
		return false;
	}
	else
	{
		int keyIndex = pNode->getKeyIndex(key);
		int childIndex = pNode->getChildIndex(key, keyIndex); // the child node index pointer
		if (keyIndex<pNode->getKeyNum() && key==pNode->getKeyValue(keyIndex))
		{
			return true;
		}
		else
		{
			if (pNode->getType()==LEAF)   //check whether the node is leaf node
			{
				return false;
			}
			else
			{
				return recursive_search(((CInternalNode*)pNode)->getChild(childIndex), key);
			}
		}
	}
}

void CBPlusTree::print()const
{
	printInConcavo(m_Root, 10);
}

void CBPlusTree::printInConcavo(CNode *pNode, int count) const{
	if (pNode!=NULL)
	{
		int i, j;
		for (i=0; i<pNode->getKeyNum(); ++i)
		{
			if (pNode->getType()!=LEAF)
			{
				printInConcavo(((CInternalNode*)pNode)->getChild(i), count-2);
			}
			for (j=count; j>=0; --j)
			{
				cout<<"-";
			}
			cout<<pNode->getKeyValue(i)<<endl;
		}
		if (pNode->getType()!=LEAF)
		{
			printInConcavo(((CInternalNode*)pNode)->getChild(i), count-2);
		}
	}
}

void CBPlusTree::printData()const
{
	CLeafNode* itr = m_DataHead;
	while(itr!=NULL)
	{
		for (int i=0; i<itr->getKeyNum(); ++i)
		{
			cout<<itr->getData(i)<<" ";
		}
		cout<<endl;
		itr = itr->getRightSibling();
	}
}

bool CBPlusTree::remove(KeyType key)
{
	if (!search(key))  //not exist
	{ 
		return false;
	}
	if (m_Root->getKeyNum()==1)//特殊情况处理
	{
		if (m_Root->getType()==LEAF)
		{
			clear();
			return true;
		}
		else
		{
			CNode *pChild1 = ((CInternalNode*)m_Root)->getChild(0);
			CNode *pChild2 = ((CInternalNode*)m_Root)->getChild(1);
			if (pChild1->getKeyNum()==MINNUM_KEY && pChild2->getKeyNum()==MINNUM_KEY)
			{
				pChild1->mergeChild(m_Root, pChild2, 0);
				delete m_Root;
				m_Root = pChild1;
			}
		}
	}
	recursive_remove(m_Root, key);
	return true;
}

// parentNode's num of keys>MINNUM_KEY
void CBPlusTree::recursive_remove(CNode* parentNode, KeyType key)
{
	int keyIndex = parentNode->getKeyIndex(key);
	int childIndex= parentNode->getChildIndex(key, keyIndex); // get child key index 
	if (parentNode->getType()==LEAF)// find target child node
	{
		if (key==m_MaxKey&&keyIndex>0)
		{
			m_MaxKey = parentNode->getKeyValue(keyIndex-1);
		}
		parentNode->removeKey(keyIndex, childIndex);  
		// if key value exist among the internal node, replace the internal node
		if (childIndex==0 && m_Root->getType()!=LEAF && parentNode!=m_DataHead)
		{
			changeKey(m_Root, key, parentNode->getKeyValue(0));
		}
	}
	else // internal node
	{
		CNode *pChildNode = ((CInternalNode*)parentNode)->getChild(childIndex); //get the root of the child tree which contatins the key
		if (pChildNode->getKeyNum()==MINNUM_KEY)                       // the number of keys reach the min number
		{
			CNode *pLeft = childIndex>0 ? ((CInternalNode*)parentNode)->getChild(childIndex-1) : NULL;                       //left sibling node
			CNode *pRight = childIndex<parentNode->getKeyNum() ? ((CInternalNode*)parentNode)->getChild(childIndex+1) : NULL;//right sibling node
			// consider borrow from sibling node
			if (pLeft && pLeft->getKeyNum()>MINNUM_KEY)// if left sibling node can be borrowed
			{    
				pChildNode->borrowFrom(pLeft, parentNode, childIndex-1, LEFT);
			}
			else if (pRight && pRight->getKeyNum()>MINNUM_KEY)//if right sibling node can be borrowed
			{
				pChildNode->borrowFrom(pRight, parentNode, childIndex, RIGHT);
			}
			//can not borrow from sibling node, merge
			else if (pLeft)                    //merge with left
			{
				pLeft->mergeChild(parentNode, pChildNode, childIndex-1);
				pChildNode = pLeft;
			}
			else if (pRight)                   //merge with right
			{
				pChildNode->mergeChild(parentNode, pRight, childIndex);
			}
		}         
		recursive_remove(pChildNode, key);
	}
}

void CBPlusTree::changeKey(CNode *pNode, KeyType oldKey, KeyType newKey) 
{ 
	if (pNode!=NULL && pNode->getType()!=LEAF) 
	{ 
		int keyIndex = pNode->getKeyIndex(oldKey); 
		if (keyIndex<pNode->getKeyNum() && oldKey==pNode->getKeyValue(keyIndex))  // find
		{ 
			pNode->setKeyValue(keyIndex, newKey); 
		} 
		else   // continue to find 
		{ 
			changeKey(((CInternalNode*)pNode)->getChild(keyIndex), oldKey, newKey); 
		} 
	} 
} 
/*
vector<DataType> CBPlusTree::select(KeyType compareKey, int compareOpeartor)
{
vector<DataType> results;
if (m_Root!=NULL)
{
if (compareKey>m_MaxKey)   // 比较键值大于B+树中最大的键值
{
if (compareOpeartor==LE || compareOpeartor==LT)
{
for(CLeafNode* itr = m_DataHead; itr!=NULL; itr= itr->getRightSibling())
{
for (int i=0; i<itr->getKeyNum(); ++i)
{
results.push_back(itr->getData(i));
}
}
}    
}
else if (compareKey<m_DataHead->getKeyValue(0))  // 比较键值小于B+树中最小的键值
{
if (compareOpeartor==BE || compareOpeartor==BT)
{
for(CLeafNode* itr = m_DataHead; itr!=NULL; itr= itr->getRightSibling())
{
for (int i=0; i<itr->getKeyNum(); ++i)
{
results.push_back(itr->getData(i));
}
}
}
}
else  // 比较键值在B+树中
{
SelectResult result;
search(compareKey, result);
switch(compareOpeartor)
{
case LT:
case LE:
{
CLeafNode* itr = m_DataHead;
int i;
while (itr!=result.targetNode)
{
for (i=0; i<itr->getKeyNum(); ++i)
{
results.push_back(itr->getData(i));
}
itr = itr->getRightSibling();
}
for (i=0; i<result.keyIndex; ++i)
{
results.push_back(itr->getData(i));
}
if (itr->getKeyValue(i)<compareKey ||(compareOpeartor==LE && compareKey==itr->getKeyValue(i)))
{
results.push_back(itr->getData(i));
}
}   
break;
case EQ:
{
if (result.targetNode->getKeyValue(result.keyIndex)==compareKey)
{
results.push_back(result.targetNode->getData(result.keyIndex));
}
}
break;
case BE:
case BT:
{
CLeafNode* itr = result.targetNode;
if (compareKey<itr->getKeyValue(result.keyIndex) ||(compareOpeartor==BE && compareKey==itr->getKeyValue(result.keyIndex)))
{
results.push_back(itr->getData(result.keyIndex));
}
int i;
for (i=result.keyIndex+1; i<itr->getKeyNum(); ++i)
{
results.push_back(itr->getData(i));
}
itr = itr->getRightSibling();
while (itr!=NULL)
{
for (i=0; i<itr->getKeyNum(); ++i)
{
results.push_back(itr->getData(i));
}
itr = itr->getRightSibling();
}
}
break;
default:  // 范围查询
break;
}
}
}
sort<vector<DataType>::iterator>(results.begin(), results.end());
return results;
}

vector<DataType> CBPlusTree::select(KeyType smallKey, KeyType largeKey)
{
vector<DataType> results;
if (smallKey<=largeKey)
{
SelectResult start, end;
search(smallKey, start);
search(largeKey, end);
CLeafNode* itr = start.targetNode;
int i = start.keyIndex;
if (itr->getKeyValue(i)<smallKey)
{
++i;
}
if (end.targetNode->getKeyValue(end.keyIndex)>largeKey)
{
--end.keyIndex;
}
while (itr!=end.targetNode)
{
for (; i<itr->getKeyNum(); ++i)
{
results.push_back(itr->getData(i));
}
itr = itr->getRightSibling();
i = 0;
}
for (; i<=end.keyIndex; ++i)
{
results.push_back(itr->getData(i));
}
}
sort<vector<DataType>::iterator>(results.begin(), results.end());
return results;
}

void CBPlusTree::search(KeyType key, SelectResult& result)
{
recursive_search(m_Root, key, result);
}

void CBPlusTree::recursive_search(CNode* pNode, KeyType key, SelectResult& result)
{
int keyIndex = pNode->getKeyIndex(key);
int childIndex = pNode->getChildIndex(key, keyIndex); // 孩子结点指针索引
if (pNode->getType()==LEAF)
{
result.keyIndex = keyIndex;
result.targetNode = (CLeafNode*)pNode;
return;
}
else
{
return recursive_search(((CInternalNode*)pNode)->getChild(childIndex), key, result);
}
}*/