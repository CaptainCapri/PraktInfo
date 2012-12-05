#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

struct IRNode {
    typedef enum {PLUS, MINUS, MULT, NUMBER, POW, MAX} nodetype;

    IRNode(nodetype t, IRNode *l, IRNode *r) : type(t), value(-1), left(l), right(r) { }
    IRNode(unsigned v) : type(NUMBER), value(v), left(0), right(0) { }

    unsigned eval(unsigned x) const {
        switch (type) {
            case NUMBER: return value;
            case PLUS: return left->eval(x) + right->eval(x);
            case MINUS: return left->eval(x) - right->eval(x);
            case MULT: return left->eval(x) * right->eval(x);
            case POW: return pow(left->eval(x), right->eval(x));
            case MAX: return std::max(left->eval(x), right->eval(x));
            default:
                throw "eval failed";
        }
    }

    unsigned pow(unsigned a, unsigned b) const {
        unsigned result = a;

        if(b == 0)
            return 1;

        for(unsigned i = 1; i < b; ++i) {
            result *= a;
        }

        return result;
    }

    void gen_x86_64() const {
        switch (type) {
            case NUMBER:
                printf("\tmovl\t$%d, %%eax\n", value);
                break;
            case PLUS:
                left->gen_x86_64();
                printf("\tpushq\t%%rax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%rbx\n");
                printf("\taddl\t%%ebx, %%eax\n");
                break;
            case MINUS:
                left->gen_x86_64();
                printf("\tpushq\t%%rax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%rbx\n");
                printf("\tsubl\t%%eax, %%ebx\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                break;
            case MULT:
                left->gen_x86_64();
                printf("\tpushq\t%%rax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%rbx\n");
                printf("\tmull\t%%ebx\n");
                break;
            case POW:
                left->gen_x86_64();
                printf("\tpushq\t%%eax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%ebx\n");
                printf("\tmovl\t%%eax, %%ecx\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                printf("\tmovl\t$0, %%edx\n");
                printf("\tcmp\t%%ecx, %%edx\n");
                printf("\tje\tzero\n");
                printf("\tinc\t%%edx\n");
                printf("\tcmp\t%%ecx, %%edx\n");
                printf("\tje\tend\n");
                printf("\tdec\t%%ecx\n");
                printf("\tstart_loop:\n");
                printf("\tmull\t%%ebx\n");
                printf("\tloop\tstart_loop\n");
                printf("\tjmp\tend\n");
                printf("\tzero:\n");
                printf("\tmovl\t$1, %%eax\n");
                printf("\tend:\n");
                break;
            case MAX:
                left->gen_x86_64();
                printf("\tpushq\t%%eax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%ebx\n");
                printf("\tcmp\t%%eax, %%ebx\n");
                printf("\tjb end\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                printf("\tend:\n");
                break;
            default:
                throw "gen x86_64 failed";
        }
    }

    void gen_x86() const {
        switch (type) {
            case NUMBER:
                printf("\tmovl\t$%d, %%eax\n", value);
                break;
            case PLUS:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\taddl\t%%ebx, %%eax\n");
                break;
            case MINUS:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tsubl\t%%eax, %%ebx\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                break;
            case MULT:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tmull\t%%ebx\n");
                break;
            case POW:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tmovl\t%%eax, %%ecx\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                printf("\tmovl\t$0, %%edx\n");
                printf("\tcmp\t%%ecx, %%edx\n");
                printf("\tje\tzero\n");
                printf("\tinc\t%%edx\n");
                printf("\tcmp\t%%ecx, %%edx\n");
                printf("\tje\tend\n");
                printf("\tdec\t%%ecx\n");
                printf("\tstart_loop:\n");
                printf("\tmull\t%%ebx\n");
                printf("\tloop\tstart_loop\n");
                printf("\tjmp\tend\n");
                printf("\tzero:\n");
                printf("\tmovl\t$1, %%eax\n");
                printf("\tend:\n");
                break;
            case MAX:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tcmp\t%%eax, %%ebx\n");
                printf("\tjb end\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                printf("\tend:\n");
                break;
            default:
                throw "gen x86 failed";
        }
    }

    void gen_expr_x86_64() const {
        fprintf(stderr, "generating x86-64 code\n");

        printf("\t.text\n");
        printf("\t.globl calc_expr\n");
        printf("calc_expr:\n");

        gen_x86_64();

        printf("\tretq\n");
    }

    void gen_expr_x86() const {
        fprintf(stderr, "generating x86 code\n");

        printf("\t.text\n");
        printf("\t.globl calc_expr\n");
        printf("calc_expr:\n");
        // most first variable from stack to edi
        printf("\tmovl\t4(%%esp), %%edi\n");

        gen_x86();

        printf("\tretl\n");
    }

    nodetype type;
    unsigned value;
    IRNode *left, *right;
};

int main() {

#if 0
    // test 1
    IRNode *ir = new IRNode(IRNode::MINUS,
        new IRNode(IRNode::MULT, new IRNode(5), new IRNode(3)),
        new IRNode(4));
#endif

#if 0
    // test 2
    IRNode *ir = new IRNode(IRNode::MULT,
        new IRNode(IRNode::MINUS, 
            new IRNode(5), 
            new IRNode(IRNode::PLUS, new IRNode(1), new IRNode(2))),
        new IRNode(4));
#endif

#if 0
    // test pow
    IRNode *ir = new IRNode(IRNode::POW,
        new IRNode(7), new IRNode(12)); 

#endif

#if 1
    // test max
    IRNode *ir = new IRNode(IRNode::MAX,
        new IRNode(5), new IRNode(33)); 
#endif

    fprintf(stderr, "eval(interpreted) = %d\n", ir->eval(23));

    if (sizeof(void *) == 8)
    {
        ir->gen_expr_x86_64();
    }
    else if (sizeof(void *) == 4)
    {
        ir->gen_expr_x86();
    }
    else
        throw "unknown architecture";

    return EXIT_SUCCESS;
}