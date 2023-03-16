#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <iostream>
template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            m_valid = false;
            count = 0;
        }
        
        Iterator(std::vector<ValueType>& values)
        {
            vals = values;
            it = vals.begin();
            m_valid = true;
            count = 0;
        }

        ValueType& get_value() const
        {
            return *it; //return value at iterator
        }

        bool is_valid() const
        {
            return m_valid; //check validity of iterator
        }

        void advance()
        {
            if(count < vals.size()) //advance iterator if allowed
            {
                it++;
                count++;
                if(count >= vals.size()){
                    m_valid = false;
                }
            }else{
                m_valid = false;
            }
        }

      private:
        bool m_valid;
        int count;
        std::vector<ValueType> vals;
        typename std::vector<ValueType>::iterator it;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        TreeMultimapHelper(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if(m_root == nullptr) //if empty tree then insert node at root
        {
            m_root = new Node(key, value);
            return;
        }
        Node *curr = m_root;
        if(curr != nullptr)
        {
            if(curr->m_key == key) //if key exists then add value to list of values
            {
                curr->m_values.push_back(value);
                return;
            }
        }
        curr = m_root;
        for(;;)
        {
            if(curr->m_key == key) //if key exists then add value to list of values
            {
                curr->m_values.push_back(value);
                return;
            }else if(key < curr->m_key)
            {
                if(curr->left != nullptr)
                {
                    curr = curr->left; //traverse to left child if present
                }
                else{
                    curr->left = new Node(key, value); //create new node if left child not present
                    return;
                }
            }else if(key > curr->m_key){
                if(curr->right != nullptr)
                {
                    curr = curr->right; //traverse to right child if present
                }else{
                    curr->right = new Node(key, value);//create new node if right child not present
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* curr = m_root;
        while(curr != nullptr)
        {
            if(curr->m_key == key){ //checking if current node has same key value trying to find
                Iterator *it = new Iterator(curr->m_values); // found the key;
                return *it;
            }else if(key < curr->m_key){
                curr = curr->left; //traversing to left child
            }else if(key > curr->m_key){
                curr = curr->right; //traversing through right child
            }
        }
        Iterator *i = new Iterator;
        return *i;
    }

  private:
    struct Node{
        Node(KeyType key, ValueType value)
        {
            m_key = key;
            m_values.push_back(value);
            left = nullptr;
            right = nullptr;
        }
        Node* left;
        Node* right;
        KeyType m_key;
        std::vector<ValueType> m_values;
    };
    Node* m_root;
    
    void TreeMultimapHelper(Node* curr) //clearing all the nodes in the tree
    {
        if(curr == nullptr){
            return;
        }
        TreeMultimapHelper(curr->left);
        TreeMultimapHelper(curr->right);
        delete curr;
    }
    
};

#endif // TREEMULTIMAP_INCLUDED
