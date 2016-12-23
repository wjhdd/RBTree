#include<iostream>
using namespace std;


enum Color  
{  
    Red,  
    Black  
};  
  
template<class K,class V>  
struct RedBlackTreeNode  
{  
    K             _key;      //��  
    V             _val;      //ֵ  
    Color             _color;    //��ɫ  
    RedBlackTreeNode<K, V>*   _parent;   //���ڵ�   
    RedBlackTreeNode<K, V>*   _left;     //���ӽڵ�   
    RedBlackTreeNode<K, V>*   _right;    //���ӽڵ�  
      
    RedBlackTreeNode(const K& key, const V& val)  
        : _key(key)  
        , _val(val)  
        , _color(Red)  
        , _parent(NULL)  
        , _left(NULL)  
        , _right(NULL)  
    {}  
};  
  
template<class K,class V>  
class RedBlackTree  
{  
    typedef RedBlackTreeNode<K, V> Node;  
public:  
    RedBlackTree()  
        :_root(NULL)  
    {}  
  
    void InOrder()  
    {  
        _InOrder(_root);  
    }  
      
    Node* Find(const K &key)  
    {  
        Node *cur = _root;  
        while (cur)  
        {  
            if (cur->_key == key)  
            {  
                return cur;  
            }  
            else if(key < cur->_key)  
            {  
                cur = cur->_left  
            }  
            else  
            {  
                cur = cur->_right;  
            }  
        }  
        return cur;  
    }  
  
    bool Insert(const K &key, const V &val)  
    {  
        if (_root == NULL)  
        {  
            _root = new Node(key, val);  
            _root->_color = Black;  
            return true;  
        }  
  
        //�Ҳ����  
        Node *parent = NULL;  
        Node *cur = _root;  
        while (cur)  
        {  
            parent = cur;  
            if (cur->_key == key)  
                return false;  
            else if (cur->_key < key)  
                cur = cur->_right;  
            else  
                cur = cur->_left;  
        }  
  
        //���ӽڵ�  
        cur = new Node(key, val);  
        cur->_parent = parent;  
        if (parent->_key > key)  
        {  
            parent->_left = cur;  
        }  
        else  
        {  
            parent->_right = cur;  
        }  
  
        //���ݺ������������  
        while (parent != _root && parent->_color == Red) //�游�ڵ�����Ҹ��ڵ�Ϊ��ɫ  
        {  
            Node* grandfa = parent->_parent;  
            if (grandfa->_left == parent)  
            { //�²���ڵ�λ��grandfa��������  
                Node *uncle = grandfa->_right;  
                if (uncle && uncle->_color == Red)  
                {  
                    grandfa->_color = Red;  
                    parent->_color = Black;  
                    uncle->_color = Black;  
                      
                    cur = grandfa;  
                    if (cur == _root)  
                    {//����������  
                        break;  
                    }  
                    parent = cur->_parent;  
                    //continue;  
                }  
                else  
                {  
                    if (cur == parent->_right)  
                    {//����  
                        _RotateL(parent);  
                        cur = cur->_left;  
                        parent = cur->_parent;  
                    }  
                    //�ҵ���  
                    _RotateR(grandfa);  
                    parent->_color = Black;  
                    parent->_left->_color = Red;  
                    parent->_right->_color = Red;  
                    break;  
                }  
            }  
            else  
            { //�²���ڵ�λ��grandfa��������  
                Node *uncle = grandfa->_left;  
                if (uncle && uncle->_color == Red)  
                {  
                    grandfa->_color = Red;  
                    parent->_color = Black;  
                    uncle->_color = Black;  
  
                    cur = grandfa;  
                    if (cur == _root)  
                    {  
                        break;  
                    }  
                    parent = cur->_parent;  
                }  
                else  
                {  
                    if (cur == parent->_left)  
                    { //�ҵ���  
                        _RotateR(parent);  
                        cur = cur->_right;  
                        parent = cur->_parent;  
                    }  
                    //����  
                    _RotateL(grandfa);  
                    parent->_color = Black;  
                    parent->_left->_color = Red;  
                    parent->_right->_color = Red;  
                    break;  
                }  
            }  
        }  
        _root->_color = Black;  
        return true;  
    }  
  
  
    bool Remove(const K &key)  
    {  
        Node* pos = Find(key);  
        if (pos == NULL)  
        {  
            return false;  
        }  
        /* 
            δ��� 
        */  
        return true;  
    }  
  
    bool IsRight()  
    {     
        //ͳ��һ��·���ϵĺ�ɫ�ڵ�ĸ���  
        Node *cur = _root;  
        int blacknum = 0;  
        while (cur)  
        {  
            if (cur->_color == Black)  
                ++blacknum;  
            cur = cur->_left;  
        }  
  
        return _CheckRBTree(_root,blacknum,0);  
    }  
  
    ~RedBlackTree()  
    {}  
  
protected:  
    bool _CheckRBTree(Node *root,int blacknum,int curblacknum)  
    {  
        if (root == NULL)  
            return true;  
  
        if (root->_color == Black)  
        {//��ɫ�ڵ�  
            ++curblacknum;  
        }  
        else  
        {//��ɫ�ڵ�  
            if (root->_parent && root->_parent->_color == Red)  
            {//����Ҫ��  
                cout << "����������ɫ�ڵ�" << endl;  
                return false;  
            }  
        }  
  
        if (root->_left == NULL && root->_right == NULL)  
        {//Ҷ�ӽ��  
            if (curblacknum == blacknum)  
                return true;  
  
            return false;  
        }  
  
        return _CheckRBTree(root->_left,blacknum,curblacknum)   
            && _CheckRBTree(root->_right,blacknum,curblacknum);  
    }  
  
    void _InOrder(Node *root)  
    {  
        if (root)  
        {  
            _InOrder(root->_left);  
            cout << "[" << root->_key << "," << root->_val << "] ";  
            _InOrder(root->_right);  
        }  
    }  
  
    void _RotateL(Node *&parent)  
    { //����  
        Node *subR = parent->_right;
        Node *subRL = subR->_left;
  
        if (subRL)  
        {  
            subRL->_parent = parent;  
        }  
        subR->_parent = parent->_parent;        
        parent->_parent = subR;  
        subR->_left = parent;  
        parent->_right = subRL;  
        parent = subR;  
        if (parent->_parent)  
        {  
            Node* grandfa = parent->_parent;  
            if (grandfa->_key > parent->_key)            
                grandfa->_left = parent;           
            else              
                grandfa->_right = parent;  
        }  
        else  
        {  
            _root = parent;  
        }  
    }  
      
    void _RotateR(Node *&parent)  
    { //�ҵ���  
        Node* subL = parent->_left;  
        Node *subLR = subL->_right;  
  
        if (subLR)  
        {  
            subLR->_parent = parent;  
        }  
        subL->_parent = parent->_parent;  
        parent->_parent = subL;  
        subL->_right = parent;  
        parent->_left = subLR;  
        parent = subL;  
        if (parent->_parent)  
        {  
            Node *grandfa = parent->_parent;  
            if (grandfa->_key > parent->_key)  
                grandfa->_left = parent;  
            else  
                grandfa->_right = parent;  
        }  
        else  
        {  
            _root = parent;  
        }  
    }  
  
protected:  
    Node    *_root;  
};  