#include <cassert>
#include <algorithm>
#include <iostream>


template <typename T>
class Heap {
    public:
        Heap(unsigned n) : elements(0), size(n), data(new T[n]) { }
        virtual ~Heap() { delete [] data; }
    
        bool empty() const { return elements; }
        T top() const {
            assert(elements > 0);
            return data[0];
        }


        void push(T d)
        {
            assert(elements < size);
            
            data[elements++] = d;
            unsigned idx = elements-1;
            while (idx != 0)
            {
                unsigned pidx = parent_index(idx);
                
                if (data[pidx] < d) 
                    std::swap(data[idx], data[pidx]);
                else break;
                    idx = pidx;
            }
        }

        void pop()
        {
            assert(elements > 0);
            
            data[0] = data[--elements];
            unsigned idx = 0;
            
            do
            {
                unsigned childs = children(idx);
                if (childs == 0) break;
                unsigned max_idx = left_index(idx);
                if (childs == 2)
                {
                    if (data[max_idx] < data[max_idx + 1]) 
                        max_idx++;
                }
                if (data[idx] < data[max_idx])
                {
                    std::swap(data[idx], data[max_idx]);
                    idx = max_idx;
                }
                else break;
                
            } while (true);
            
        }

        void print() const
        {
            for (unsigned int i = 0; i < elements; i++)
            {
                std::cout << data[i] << std::endl;
            }


        }


    private:
        unsigned elements;
        unsigned size;
        T *data;

        unsigned left_index(unsigned idx) const { return 2 * idx + 1; }
        unsigned right_index(unsigned idx) const { return 2 * idx + 2; }
        unsigned parent_index(unsigned idx) const { return (idx - 1) / 2; }
        unsigned children(unsigned idx) const {
            if (elements <= left_index(idx)) return 0;
            else if (elements > right_index(idx)) return 2;
            else return 1;
        }
};