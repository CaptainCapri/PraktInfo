#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
class Tree {
public:
    Tree() : root(0) {
    }

    void insert(double d) {
        if (!root) root = new Node(d);
        else insert(root, d);
    }

    void print() const {
        print(root);
    }
    int getTreeHeight(){
        return height(root);
    }

private:

    struct Node {
        Node(double d) : data(d), left(0), right(0) {
        }
        double data;
        Node *left, *right;
    };

    void print(Node *node) const {
        if (!node) return;

        print(node->left);
        printf("%.2f (%d)\n", node->data, height(node));
        print(node->right);
    }

    unsigned int height(Node *node) const {
        if (!node) return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }


    void insert(Node* &node, double d) {
        if (!node) node = new Node(d);

        if (d < node->data) {
            insert(node->left, d);
        }
        else if (d > node->data) {
            insert(node->right, d);
        }
    }

    Node *root;
};

int main() {
#define BILLION 1E9

    // Calculate time taken by a request
    struct timespec requestStart, requestEnd;

    Tree Tree;
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
