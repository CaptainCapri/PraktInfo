#ifndef SKIP_LIST_NODE
#define SKIP_LIST_NODE


template <class Key, class Object>
    class SkipNode
    {
    public:
        SkipNode(Key key , Object object, unsigned int level) :
          key(key), object(object), level(level)
        {
            fwdNodes = new SkipNode<Key, Object>* [level+1];
            for (unsigned int i = 0; i <= level; i++)
                fwdNodes[i] = 0;
        }

        SkipNode(unsigned int level) : level(level)
        {
            fwdNodes = new SkipNode<Key, Object>* [level+1];
            for (unsigned int i = 0; i <= level; i++)
                fwdNodes[i] = 0;

        }
        

        ~SkipNode()
        {
            delete [] fwdNodes;
        }


        Key key;
        Object object;
        unsigned int level;
        SkipNode** fwdNodes;
        
    };


#endif
