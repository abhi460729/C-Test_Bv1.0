#include <iostream>
#include <string>
using namespace std;
template <typename KEY, typename T>
class Map{
private:
        struct Elem {
            Elem():left(0),right(0),height(-1),rightThread(false){}
            KEY key;
            T data;
            Elem *left;
            Elem *right;
            int height;
            bool rightThread;
        };
        Elem *_root;
        int _size;

public:

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

        int balanceFactor(Elem *cur)
        {
            if (cur == NULL)
                return 0;
            return height(cur->left) - height(cur->right);
        }

        int height(Elem * node)
        {
            if (node == NULL)
                return 0;
            return node->height;
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
        {
            return insert( root->left, key, data, root);
        }
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

    void updateHeight(Elem*& cur){
        cur->height = 1 + max(height(cur->left),
                        height(cur->right));
    }

    void balance(Elem*& cur, const KEY &key){


        updateHeight(cur);

        int bal=balanceFactor(cur);

        if (bal > 1 && key < cur->left->key) {
             rotateRight(cur);
             return;
        }

        if (bal < -1 && key > cur->right->key){
             rotateLeft(cur);
             return;
        }

        if (bal > 1 && key > cur->left->key)
        {
            doubleRotateLeft(cur);
            return;
        }

        if (bal < -1 && key < cur->right->key)
        {
            doubleRotateRight(cur);
            return;
        }


        }

    void rotateRight(Elem *& node){
        Elem *x = node->left;
        Elem *T2 = x->right;

        x->right = node;
        node->left = T2;

        node->height = max(height(node->left),
                        height(node->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;

        return;
    }

    void rotateLeft(Elem *& node){
        Elem *y = node->right;
        Elem *T2 = y->left;


        y->left = node;
        node->right = T2;

        node->height = max(height(node->left),
                        height(node->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        return;

    }

    void doubleRotateLeft(Elem *& node){
            rotateLeft(node->left);
            rotateRight(node);
            return;
    }

     void doubleRotateRight(Elem *& node){
            rotateRight(node->right);
            rotateLeft(node);
            return;
    }




};
int main(){
    return 0;
    }
