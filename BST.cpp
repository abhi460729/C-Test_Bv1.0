#include <iostream>
#include <string>
using namespace std;
template <typename KEY, typename T>
class Map{
private:
    struct Elem {
        KEY key;
        T data;
        Elem *left;
        Elem *right;
        bool rightThread;
    };
    Elem *_root;
    int _size;

public:
    Map()
        {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        _root->rightThread = false;
        _size = 0;
        }

    bool insert( KEY key, T data)
        {
            if ( insert( _root->left, key, data, _root ) )
            {
                _size++;
                return true;
            }
            return false;
        }

		
    bool insert(Elem *&root, const KEY &key, const T &data, Elem *lastLeft) {
        if (root == _root || root == 0 )
        {
            root = new Elem;
            root->key = key;
            root->data = data;
            root->left = 0;
            root->right = lastLeft;
            root->rightThread = true;
            return true;
        }
        if (key == root->key)
        {
            return false;
        }
        if (key < root->key)
            return insert( root->left, key, data, root);
        if (! root->rightThread )
        {
            return insert(root->right, key, data, lastLeft);
        }
        else
        {
            root->rightThread = false;
            root->right = new Elem;
            root->right->key = key;
            root->right->data = data;
            root->right->left = 0;
            root->right->right = lastLeft;
            root->right->rightThread = true;
            return true;
        }
    }

    void destructCode(Elem *&p)
        {
            if( p->left != NULL )
            {
                destructCode( p->left );
            }
            if( p->right != NULL && ( !p->rightThread ) )
            {
                destructCode( p->right );
            }
            delete p;
        }

    void printTree(ostream& out, int level, Elem *p) const
        {
            int i;
            if (p)
            {
                if (p->right && !p->rightThread)
                    printTree(out, level+1,p->right);
                for(i=0;i<level;i++)
                {
                    out << "\t";
                }
                out << p->key << " " << p->data << '\n';
                printTree(out, level+1,p->left);
            }
        }
};

int main(){
    Map<int,int> m;
    m.insert(2,5);
    return 0;
}
