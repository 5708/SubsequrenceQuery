#ifndef BPLUS_NODE  
#define BPLUS_NODE 
#define NULL 0

enum NODE_TYPE{INTERNAL, LEAF};
enum SIBLING_DIRECTION{LEFT, RIGHT};
typedef double KeyType;
typedef int DataType;

const int ORDER = 4;  				//B+ tree's order
const int MINNUM_KEY = ORDER - 1; 	//the min amount of keys
const int MAXNUM_KEY = 2*ORDER - 1;	//the max amount of keys
const int MINNUM_CHILD = MINNUM_KEY + 1; //the min amount of children tree
const int MAXNUM_CHILD = MAXNUM_KEY + 1; //the max amount of children tree
const int MINNUM_LEAF = MINNUM_KEY;
const int MAXNUM_LEAF = MAXNUM_KEY;

class CNode{
public:
	CNode();
	virtual ~CNode();

	NODE_TYPE getType() const{return m_Type;}
	void setType(NODE_TYPE type){m_Type=type;}
	int getKeyNum()const{return m_KeyNum;}
	void setKeyNum(int n){m_KeyNum=n;}
	KeyType getKeyValue(int i)const{return m_KeyValues[i];}
	void setKeyValue(int i, KeyType key){m_KeyValues[i]=key;}
	int getKeyIndex(KeyType key)const; 	//find the key's index
	//interface definition
	virtual void removeKey(int keyIndex, int childIndex)=0; //remove key from the node
	virtual void split(CNode* parentNode, int childIndex)=0; //split node
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex)=0; //merge nodes
	virtual void clear()=0; //clear node and it's child tree
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d)=0; //borrow a key value from it's sibling node
	virtual int getChildIndex(KeyType key, int keyIndex)const=0; //get child index based on key value
protected: 
    NODE_TYPE m_Type; 
    int m_KeyNum; 
    KeyType m_KeyValues[MAXNUM_KEY]; 
};

//Internal Node
class CInternalNode : public CNode{ 
public: 
    CInternalNode(); 
    virtual ~CInternalNode(); 
 
    CNode* getChild(int i) const {return m_Childs[i];} 
    void setChild(int i, CNode* child){m_Childs[i] = child;} 
    void insert(int keyIndex, int childIndex, KeyType key, CNode* childNode); 
    virtual void split(CNode* parentNode, int childIndex); 
    virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex); 
    virtual void removeKey(int keyIndex, int childIndex); 
    virtual void clear(); 
    virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d); 
    virtual int getChildIndex(KeyType key, int keyIndex)const; 
private: 
    CNode* m_Childs[MAXNUM_CHILD]; 
}; 

//Leaf node
class CLeafNode : public CNode{ 
public: 
    CLeafNode(); 
    virtual ~CLeafNode(); 
 
    CLeafNode* getLeftSibling() const {return m_LeftSibling;} 
    void setLeftSibling(CLeafNode* node){m_LeftSibling = node;} 
    CLeafNode* getRightSibling() const {return m_RightSibling;} 
    void setRightSibling(CLeafNode* node){m_RightSibling = node;} 
    DataType getData(int i) const {return m_Datas[i];} 
    void setData(int i, const DataType& data){m_Datas[i] = data;} 
    void insert(KeyType key, const DataType& data); 
    virtual void split(CNode* parentNode, int childIndex); 
    virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex); 
    virtual void removeKey(int keyIndex, int childIndex); 
    virtual void clear(); 
    virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d); 
    virtual int getChildIndex(KeyType key, int keyIndex)const; 
private: 
    CLeafNode* m_LeftSibling; 
    CLeafNode* m_RightSibling; 
    DataType m_Datas[MAXNUM_LEAF]; 
}; 
#endif 