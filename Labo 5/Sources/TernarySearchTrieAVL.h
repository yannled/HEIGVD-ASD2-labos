//
//  AVLTree.h
//  SearchTrees
//
//  Created by Olivier Cuisenaire on 25.11.14.
//  Copyright (c) 2014 Olivier Cuisenaire. All rights reserved.
//
//  MODIFIED BY Valentin MINDER, Toni DE SOUSA DIAS
//  ASD2 - LAB5 - DICTIONARY
//  ORIGINAL FILE: AVLTree.h (all changes are marqued "MODIFIED")
//  ONLY struct Node, destructor, and methods put, get and contains have been modified!
//  (and therefore other methods may not be consistent with the data structure changes, but we dont car for our goal)
//  A PROOF A CONCEPT OF AVL HAS BEEN ADDED to prove that the AVL works (visit/checkAVL methods)
//  This represent a TST Ternary Search Trie with an AVL structure
//
//  Structure explanation: 
//  each node has a ptr to the next row (nextRow) which is another sub-TST for the next row
//  the next key will be used (the ptr will be incremented)
//
//  A sequence of keys is contained in the Trie if the last key reaches a node 
//  where the value is not a nullptr but any stored value of ValueType (we don't care about the value)
// 
//  To insert or search, keys are passed as pointers, to be use like an array. 
//  The first element of key (*key) is the key for the first row, then the ptr is incremented (key++)
//  for the next row, until it reaches the end of keys or trie.
//  
//  In the application, we used char as key, therefore a string 
//  is transformed in char* and we use a key (a char) at each level of the trie.
//  The string is valid if it's last key (last char) reaches a node with a value not nullptr.
//  (and int as value, but doesn't really matter: only matter if there is value or not)
//

#ifndef SearchTrees_TST_TernarySearchTrie_AVL_h
#define SearchTrees_TST_TernarySearchTrie_AVL_h

#include <algorithm>

template < typename KeyType, typename ValueType >
class TernarySearchTrieAVL {
private:

    //
    // Noeux de l'arbre. contient une cle, une valeur, et les liens vers les
    // sous-arbres droit et gauche.
    //

    struct Node {
    public:
        KeyType key;
        ValueType* value; // MODIFIED: *
        TernarySearchTrieAVL<KeyType, ValueType> *nextRow; // MODIFIED: added
        Node* right; // sous arbre avec des cles plus grandes
        Node* left; // sous arbre avec des cles plus petites
        int nodeSize; // taille du sous-arbre dont ce noeud est la racine.
        int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
        // MODIFIED: *

        Node(KeyType key, ValueType* value) : key(key), value(value), right(nullptr), nextRow(nullptr), left(nullptr), nodeSize(1), nodeHeight(0) {
        }
    };

    //
    // Racine de l'arbre.
    //
    Node* root;

    // HELPER: Methode aide pour le methodes d'effacement. Efface del et retourne ret.

    Node* deleteAndReturn(Node* del, Node* ret) {
        delete del;
        return ret;
    }
    // HELPER: Mise à jour de la taille d'un sous-arbre à partir des taille de ses enfants

    void updateNodeSize(Node* x) {
        x->nodeSize = size(x->right) + size(x->left) + 1;
    }
    // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants

    void updateNodeHeight(Node* x) {
        x->nodeHeight = std::max(height(x->right), height(x->left)) + 1;
    }

private:
    //
    // AVL: rotation droite avec mise à jour des tailles et hauteurs
    //

    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;

        y->nodeSize = x->nodeSize;
        updateNodeSize(x);

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    //
    // AVL: rotation gauche avec mise à jour des tailles et hauteurs
    //

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        y->nodeSize = x->nodeSize;
        updateNodeSize(x);

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }


    //
    // Constructeur. La racine est vide
    //
public:

    TernarySearchTrieAVL() : root(nullptr) {
    }


    //
    // Destructeur.
    //
public:

    ~TernarySearchTrieAVL() {
        deleteSubTree(root);
    }
private:

    void deleteSubTree(Node* x) {
        if (x == nullptr) return;
        // MODIFIED: ADDED
        if (x->nextRow != nullptr) {
            deleteSubTree(x->nextRow->root);
        }
        deleteSubTree(x->right);
        deleteSubTree(x->left);
        delete x;
    }

    //
    // Nombre d'elements
    //
public:

    int size() {
        return size(root);
    }
private:

    int size(Node* x) {
        return ( x == nullptr) ? 0 : x->nodeSize;
    }

    //
    // Insertion d'une paire cle / valeur.
    //
public:
    // MODIFIED: *

    void put(const KeyType* key, ValueType value) {
        root = put(root, key, value);
    }

private:
    // MODIFIED: *

    Node* put(Node* x, const KeyType* key, ValueType value) {
        //MODIFIED: ADDED
        if (key == nullptr || *key == '\0') {
            return nullptr;
        }
        if (x == nullptr) {
            // MODIFIED
            x = new Node(*key, nullptr);
        }


        if (*key < x->key)
            x->left = put(x->left, key, value);
        else if (*key > x->key)
            x->right = put(x->right, key, value);
        else {// x->key == key
            // MODIFIED: ADDED:
            key++; // ptr incremented (next key)
            if (key == nullptr || *(key) == '\0') {
                // reached the end of keys: insertion.
                x->value = &value;
            } else {
                // keys remaining: going for next row
                if (x->nextRow == nullptr) {
                    x->nextRow = new TernarySearchTrieAVL();
                }
                x->nextRow->put(key, value);
            }
        }


        updateNodeSize(x);

        return restoreBalance(x); // AVL. sinon on aurait return x; 
    }

    //
    // AVL: calcul et restoration de l'équilibre d'un noeud.
    //

    int balance(Node* x) {
        if (x == nullptr) return 0;
        return height(x->left) - height(x->right);
    }

    Node* restoreBalance(Node* x) {

        if (balance(x) < -1) // left < right-1
        {
            if (balance(x->right) > 0)
                x->right = rotateRight(x->right);
            x = rotateLeft(x);
        } else if (balance(x) > 1) // left > right+1
        {
            if (balance(x->left) < 0)
                x->left = rotateLeft(x->left);
            x = rotateRight(x);
        } else updateNodeHeight(x);
        return x;
    }

    //
    // Recherche d'une cle. Renvoie true et modifie
    // value si la cle est trouvee. Renvoie false et
    // ne modifie pas value sinon.
    //
public:
    // MODIFIED: *

    bool get(const KeyType* key, ValueType& value) {
        Node* x = root;
        while (x != nullptr) {
            if (*key < x->key)
                x = x->left;
            else if (*key > x->key)
                x = x->right;
            else // x->key == key.
            {
                // MODIFIED: ADDED
                key++; // ptr incremented (next key)
                if (key == nullptr || *(key) == '\0') {
                    // reached the end of keys: 
                    // check if value is nullptr (false) or contains data.
                    if (x->value != nullptr) {
                        value = *(x->value);
                        return true;
                    }
                    return false;
                } else if (x->nextRow == nullptr) {
                    // keys remaining but no next row: false
                    return false; // 
                } else {
                    // keys remaining: searching in next row
                    return x->nextRow->get(key, value);
                }
            }
        }
        return false;
    }

    //
    // idem précédent, mais sans retour de la valeur
    // MODIFIED: *

    bool contains(const KeyType* key) {
        Node* x = root;
        while (x != nullptr) {
            if (*key < x->key)
                x = x->left;
            else if (*key > x->key)
                x = x->right;
            else { // x->key == key.
                // MODIFIED: ADDED
                key++; // ptr incremented (next key)
                if (key == nullptr || *(key) == '\0') {
                    // reached the end of keys: 
                    // check if value is nullptr (false) or contains data.
                    return (x->value != nullptr);
                } else if (x->nextRow == nullptr) {
                    // keys remaining but no next row: false
                    return false; // 
                } else {
                    // keys remaining: searching in next row
                    return x->nextRow->contains(key);
                }
            }
        }
        return false;
    }

    //
    // Profondeur de l'arbre.
    //
public:

    int height() {
        return height(root);
    }
private:

    int height(Node* x) {
        if (x == nullptr)
            return -1;
        return x->nodeHeight;
    }


    //
    // Efface le plus petit element de l'arbre.
    //
public:

    void deleteMin() {
        if (root != nullptr) {
            root = deleteMin(root);
        }
    }
private:

    Node* deleteMin(Node* x) {
        if (x->left == nullptr)
            return deleteAndReturn(x, x->right);
        x->left = deleteMin(x->left);
        x->nodeSize--;
        return restoreBalance(x);
    }


    //
    // Efface le plus grand element de l'arbre.
    //
public:

    void deleteMax() {
        if (root != nullptr) {
            root = deleteMin(root);
        }
    }
private:

    Node* deleteMax(Node* x) {
        if (x->right == nullptr)
            return deleteAndReturn(x, x->left);
        x->left = deleteMin(x->right);
        x->nodeSize--;
        return restoreBalance(x);
    }


    //
    // Efface l'element de cle key
    //
public:

    void deleteElement(const KeyType& key) {
        root = deleteElement(root, key);
    }
private:

    Node* deleteElement(Node* x, const KeyType& key) {
        if (x == nullptr)
            return nullptr; // element pas trouve.

        if (key < x->key)
            x->left = deleteElement(x->left, key);
        else if (key > x->key)
            x->right = deleteElement(x->right, key);
        else { // x->key == key
            if (x->right == nullptr)
                return deleteAndReturn(x, x->left);
            if (x->left == nullptr)
                return deleteAndReturn(x, x->right);

            Node* y = min(x->right);
            x->key = y->key;
            x->value = y->value;
            x->right = deleteMin(x->right);
        }
        updateNodeSize(x);
        return restoreBalance(x);
    }

    //
    // Visite de l'arbre par ordre croissant de cle
    //
public:

    template < typename Fn >
    void visitInOrder(Fn f) {
        if (root != nullptr)
            visitInOrder(root, f);
    }

private:

    template < typename Fn >
    void visitInOrder(Node* x, Fn f) {
        if (x->left != nullptr)
            visitInOrder(x->left, f);

        f(x->key, x->value);

        if (x->right != nullptr)
            visitInOrder(x->right, f);
    }

public:

    /**
     * Proof of concept of AVL tree (we can see the graph)
     * MODIFIED: added
     */
    void visit() {
        if (root != nullptr)
            visit(root, 0);
    }

    /**
     * MODIFIED: added
     * Dans un arbre AVL, les hauteurs des deux sous-arbres d'un même nœud diffèrent au plus de un.
     * 
     * Hauteur = nombre de liens de la racine à la plus éloignée des feuilles. Un arbre null a une hauteur -1, une feuille une hauteur 0
     * On vérifie l'AVL au niveau 0 uniquement (équilibrage pour la première lettre.
     * @return 
     */
    bool checkAVL() {
        if (root != nullptr)
            return checkAVL(root);
        return true;
    }

private:
    // MODIFIED: added

    void visit(Node* x, int h) {

        for (int i = 0; i < h; i++) {
            std::cout << "|";
        }
        std::cout << x->key << "\t\t height: " << x->nodeHeight << ", size: " << x->nodeSize << std::endl;

        if (x->left != nullptr) {
            visit(x->left, h + 1);
        }


        if (x->right != nullptr) {
            visit(x->right, h + 1);
        }


    }

    // MODIFIED: added

    bool checkAVL(Node* x) {
        int left = -1;
        int right = -1;
        bool value = true;
        if (x->left != nullptr) {
            left = x->left->nodeHeight;
            value = value && checkAVL(x->left);
        }


        if (x->right != nullptr) {
            right = x->right->nodeHeight;
            value = value && checkAVL(x->right);
        }
        // difference de max 1 entre la hauteur droite et gauche
        return value && (-1 <= (left - right)) && ((left - right) <= 1);
    }


    //
    // Renvoie la cle la plus petite de l'arbre
    //
public:

    KeyType min() {
        return min(root)->key;
    }
private:

    Node* min(Node* x) {
        if (x->left == nullptr)
            return x;
        return min(x->left);
    }

    //
    // Renvoie la cle la plus grande de l'arbre
    //
public:

    KeyType max() {
        return max(root)->key;
    }
private:

    Node* max(Node* x) {
        if (x->right == nullptr)
            return x;
        return max(x->right);
    }


    //
    // Renvoie le rang (nombre de cles plus petites) d'une cle
    //
public:

    int rank(const KeyType& key) {
        return rank(root, key);
    }
private:

    int rank(Node* x, const KeyType& key) {
        if (x == nullptr) return 0;

        if (key < x->key)
            return rank(x->left, key);
        else if (key > x->key)
            return 1 + size(x->left) + rank(x->right, key);
        else return size(x->left);
    }
};


#endif // de SearchTrees_TST_TernarySearchTrie_AVL_h
