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
            return *it;
        }

        bool is_valid() const
        {
            return m_valid;
        }

        void advance()
        {
            if(count < vals.size())
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
        if(m_root == nullptr)
        {
            m_root = new Node(key, value);
            return;
        }
        Node *curr = m_root;
        if(curr != nullptr)
        {
            if(curr->m_key == key)
            {
                curr->m_values.push_back(value);
                return;
            }
        }
        curr = m_root;
        for(;;)
        {
            if(curr->m_key == key)
            {
                curr->m_values.push_back(value);
                return;
            }else if(key < curr->m_key)
            {
                if(curr->left != nullptr)
                {
                    curr = curr->left;
                }
                else{
                    curr->left = new Node(key, value);
                    return;
                }
            }else if(key > curr->m_key){
                if(curr->right != nullptr)
                {
                    curr = curr->right;
                }else{
                    curr->right = new Node(key, value);
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
            if(curr->m_key == key){
                Iterator *it = new Iterator(curr->m_values); // found the key;
                return *it;
            }else if(key < curr->m_key){
                curr = curr->left;
            }else if(key > curr->m_key){
                curr = curr->right;
            }
        }
        Iterator *i = new Iterator;
        return *i;  // Replace this line with correct code.
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
    
    void TreeMultimapHelper(Node* curr)
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
