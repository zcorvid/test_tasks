#include <iostream>
#include <fstream>
#include <string>

template<class T>
struct node
{
    T value = 0;
    node *next = nullptr;
};

// adds to a list numbers from file, doesn't change root value
void fill_list(node<int> *root, const std::string &fname)
{
    std::ifstream fin(fname);
    int n;
    fin >> n;
    for (int i = 0; i < n; ++i)
    {
        int x;
        fin >> x;
        root->next = new node<int>;
        root = root->next;
        root->value = x;
    }
}

void print_list(node<int> *root)
{
    std::cout << "List: " << std::endl;
    while(root)
    {
        std::cout << " " << root->value << std::endl;
        root = root->next;
    }
}

void dealloc_list(node<int> *root)
{
    while(root)
    {
        node<int> *x = root;
        root = root->next;
        delete x;
    }
}

template<class T>
node<T>* revert_list(node<T> *root)
{
    node<T> *prev = nullptr;
    node<T> *next = nullptr;
    for(;;)
    {
        next = root->next;
        root->next = prev;
        prev = root;
        if (next) root = next;
        else
        {
            break;
        }
    }
    return root;
}

int main()
{
    node<int> *root = new node<int>;
    fill_list(root, "input1.txt");
    print_list(root);
    auto rev_root = revert_list(root);
    print_list(rev_root);
    dealloc_list(rev_root);
    return 0;
}
