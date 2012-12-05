#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <ctime>
#include <cstdlib>
#include "SkipNode.h"

class DescribedException : public std::exception
{
public:
	DescribedException(char const *description) throw(): description(description)
	{
	}
	virtual ~DescribedException() throw() {}
	virtual char const *what() const throw()
	{
		return description.c_str();
	}
protected:
	std::string description;
};


class NotFoundException : public DescribedException
{
public:
    NotFoundException() :
	    DescribedException((std::string("key not found in SkipList").c_str())) {}
};




template <typename Key, typename Object>
class SkipList
{
public:
    
    SkipList(float p, unsigned int maxLevel) :
       m_head(0), m_tail(0), m_currentLevel(1), m_maxLevel(maxLevel), m_propability(p)
    {
        srand(time(0));

        m_head = new SkipNode<Key,Object>(maxLevel);
    
    }


    ~SkipList()
    {
        SkipNode<Key, Object> *currentNode = m_head;
        SkipNode<Key, Object> *toDelete;

        while(currentNode != 0)
        {
            toDelete = currentNode;
            currentNode = currentNode->fwdNodes[1];
            delete toDelete;
        }
    }

    bool insert(Key key, Object object)
    {
        SkipNode<Key, Object>** update = new SkipNode<Key, Object>* [m_maxLevel+1];

        SkipNode<Key, Object> *currentNode = m_head;

        for (unsigned int i = m_currentLevel; i > 0; --i)
        {
            while(currentNode->fwdNodes[i] != 0 && currentNode->fwdNodes[i]->key < key)
                currentNode = currentNode->fwdNodes[i];
            update[i] = currentNode;
        }

        currentNode = currentNode->fwdNodes[1];

        if (currentNode != 0 && currentNode->key == key)
        {
            //cout << "if (currentNode != 0 && currentNode->key == key)" << endl;
            currentNode->object = object;
        }
        else
        {
            
            //cout << "if (currentNode != 0 && currentNode->key == key) - ELSE" << endl;
            unsigned int randLevel = randomLevel();

            //cout << "randLevel:    " << randLevel << endl;
            //cout << "currentLevel: " << m_currentLevel << endl;


            if (randLevel > m_currentLevel)
            {
                
                for (unsigned int i = m_currentLevel + 1; i <= randLevel; i++)
                {
                    update[i] = m_head;
                }
                m_currentLevel = randLevel;
            }

            currentNode = new SkipNode<Key, Object>(key, object, randLevel);

            for (unsigned int i = 1; i <= randLevel; i ++)
            {
                currentNode->fwdNodes[i] = update[i]->fwdNodes[i];
                update[i]->fwdNodes[i] = currentNode;
            }

        }


        delete [] update;
        return true;
    }

    bool remove(Key key)
    {


        return false;
    }


    Object search(Key key)
    {
        if (m_head == 0)
            throw NotFoundException();

        SkipNode<Key, Object> *currentNode = m_head;

        for (unsigned int i = m_currentLevel; i > 0; i--)
        {
            while(currentNode->fwdNodes[i] != 0 && currentNode->fwdNodes[i]->key < key)
                currentNode = currentNode->fwdNodes[i];

        }

        currentNode = currentNode->fwdNodes[1];

        if (currentNode != 0 && currentNode->key == key) return currentNode->object;
        else throw NotFoundException();
    }


    


private:
    SkipNode<Key, Object> *m_head;
    SkipNode<Key, Object> *m_tail;
    
    unsigned int m_currentLevel;
    unsigned int m_maxLevel;
    float m_propability;

    unsigned int randomLevel()
    {
        unsigned int tempLevel = 1;

        while (rand()/float(RAND_MAX) < m_propability && tempLevel < m_maxLevel)
        {
            tempLevel++;
        }

        return tempLevel;
    }




};


#endif
  