#ifndef MAP_HPP
#define MAP_HPP

#include "list.hpp"

template<typename K, typename D>
class MapBinaryTreeNode
{
public:
    MapBinaryTreeNode *left;
    MapBinaryTreeNode *right;
    K key;
    D data;
    MapBinaryTreeNode(K key, D data);
    void add(K key, D data);
};

template<typename K, typename D>
class Map
{
public:
    MapBinaryTreeNode<K, D> *root;
    Map();
    void add(K key, D data);
    MapBinaryTreeNode<K, D>* find(K key);
    List<D> *listData();
    virtual ~Map();
};

template<typename K, typename D>
MapBinaryTreeNode<K, D>::MapBinaryTreeNode(K key, D data)
{
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

template<typename K, typename D>
void MapBinaryTreeNode<K, D>::add(K key, D data)
{
    if(key == this->key)
    {
        this->data = data;
    }
    else if(key < this->key)
    {
        if(this->left == nullptr) this->left = new MapBinaryTreeNode<K, D>(key, data);
        else this->left->add(key, data);
    }
    else
    {
        if(this->right == nullptr) this->right = new MapBinaryTreeNode<K, D>(key, data);
        else this->right->add(key, data);
    }
}

template<typename K, typename D>
Map<K, D>::Map()
{
    this->root = nullptr;
}

template<typename K, typename D>
void Map<K, D>::add(K key, D data)
{
    if(this->root == nullptr)
    {
        this->root = new MapBinaryTreeNode<K,D>(key, data);
    }
    else
    {
        this->root->add(key, data);
    }
}

template<typename K, typename D>
MapBinaryTreeNode<K, D> *Map<K, D>::find(K key)
{
    MapBinaryTreeNode<K, D> *node = this->root;
    while(node != nullptr)
    {
        if(key == node->key)
        {
            return node;
        }
        else if(key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    return nullptr;
}

template<typename K, typename D>
void list_data_from_map_tree(MapBinaryTreeNode<K, D> *node, List<D> *list)
{
    if(node != nullptr)
    {
        list_data_from_map_tree(node->left, list);
        list->pushEnd(node->data);
        list_data_from_map_tree(node->right, list);
    }
}

template<typename K, typename D>
void delete_map_tree(MapBinaryTreeNode<K, D> *node)
{
    if(node != nullptr)
    {
        delete_map_tree(node->left);
        delete_map_tree(node->right);
        delete node;
    }
}

template<typename K, typename D>
List<D>* Map<K,D>::listData()
{
    List<D> *mylist = new List<D>();
    list_data_from_map_tree(this->root, mylist);
    return mylist;
}

template<typename K, typename D>
Map<K, D>::~Map()
{
    delete_map_tree(this->root);
}

#endif // MAP_HPP
