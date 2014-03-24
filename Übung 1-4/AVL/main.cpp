#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class AvlTree {
public:
    AvlTree() : root(0) {
    }

    void insert(double d) {
        if (!root) root = new AvlNode(d);
        else insert(root, d);
    }

    void print() const {
        print(root);
    }
    int getTreeHeight(){
        return height(root);
    }
private:

    struct AvlNode {
        AvlNode(double d) : data(d), left(0), right(0) {
        }

        double data;
        AvlNode *left, *right;
    };

    void print(AvlNode *node) const {
        if (!node) return;

        print(node->left);
        printf("%.2f (%d)\n", node->data, height(node));
        print(node->right);
    }

    unsigned int height(AvlNode *node) const {
        if (!node) return 0;

        return 1 + std::max(height(node->left), height(node->right));
    }

    void rotate_right(AvlNode* &node) {
        AvlNode *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node = temp;
    }

    void rotate_right_left(AvlNode* &node) {
        rotate_right(node->right);
        rotate_left(node);
    }

    void rotate_left(AvlNode* &node) {
        AvlNode *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node = temp;
    }

    void rotate_left_right(AvlNode* &node) {
        rotate_left(node->left);
        rotate_right(node);
    }

    void insert(AvlNode* &node, double d) {
        if (!node) node = new AvlNode(d);

        if (d < node->data) {
            insert(node->left, d);

            if (height(node->left) - height(node->right) == 2) {
                if (d < node->left->data) rotate_right(node);
                else rotate_left_right(node);
            }
        }
        else if (d > node->data) {
            insert(node->right, d);

            if (height(node->right) - height(node->left) == 2) {
                if (d > node->right->data) rotate_left(node);
                else rotate_right_left(node);
            }
        }
    }

    AvlNode *root;
};

int main() {
#define BILLION 1E9

    // Calculate time taken by a request
    struct timespec requestStart, requestEnd;

    AvlTree Tree;
    time_t t;

    time(&t);
    srand((unsigned int)t);


    printf("nodes | height | time\n");
    for(int bsize = 10000; bsize<= 100000; bsize+=10000){

        //start
        clock_gettime(CLOCK_REALTIME, &requestStart);
        for (int i = 0; i < bsize; i++){
            Tree.insert(rand() % bsize*2);// + 1);
        }
        clock_gettime(CLOCK_REALTIME, &requestEnd);

        double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
                + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                / BILLION;

        printf("%d | ",bsize);
        printf(" %d | ",Tree.getTreeHeight());
        printf( "%lf\n", accum );

        //end
    }
    exit(0);
}
