#include "cdll.h"
#include <iostream>
#include <algorithm>


CDLLNode::CDLLNode(const char *ti, const char *tw)
{
    time = ti;
    tweet = tw;
    next = NULL;
    prev = NULL;
}

CDLLNode::~CDLLNode()
{
    // no dynamic memory allocation, nothing to destroy
}

CDLL::CDLL()
{
    head = NULL;
    current = NULL;
}

CDLL::~CDLL()
{
    CDLLNode *p1 = head;
    CDLLNode *p2 = p1->next;

    while (p1 != head)
    { 
        delete p1;
        p1 = p2;
        p2 = p2->next;
    }
    delete head;
}
 
unsigned int CDLL::num_elements(CDLLNode *node)
{
    // end marks the end of iteration thru CDLL
    CDLLNode *end = head->prev;
    CDLLNode *p = head;
    unsigned int i = 0;
    // while p is not end
    while(p != end)
    {
        p = p->next;
        i++;
    }
    // add 1 b/c p stop before the last node to be counted
    return i + 1; 
}

void CDLL::prepend(const char *time, const char *tweet)
{
    // create node to be inserted into the CDLL
    CDLLNode *n = new CDLLNode(time, tweet);
    // if CDLL is empty
    if (head == NULL)
    {
        n->next = n;
        n->prev = n;
        head = n;
    } // if CDLL has only 1 node
    else if (head->next == head)
    {
        n->next = head;
        n->prev = head;
        head->next = n;
        head->prev = n;
        head = n;
    } // to insert node into CDLL with more than 1 node
    else
    {
        n->next = head;
        n->prev = head->prev;
        head->prev->next = n;
        head->prev = n;
        head = n;
    }
}

void CDLL::append(const char *time, const char *tweet)
{
    CDLLNode *n = new CDLLNode(time, tweet);
    // if CDLL is empty
    if (head == NULL)
    {
        n->next = n;
        n->prev = n;
        head = n;
    } // if CDLL has only 1 node
    else if (head->next == head)
    {
        n->next = head;
        n->prev = head;
        head->next = n;
        head->prev = n;
    }
    else // to insert node into CDLL w/ more than 1 node
    {
        n->next = head;
        n->prev = head->prev;
        head->prev->next = n;
        head->prev = n;
    }
}

void CDLL::go_next()
{
    // don't iterate if current is NULL
    if (current != NULL)
    {
        current = current->next;
    }
}

void CDLL::go_prev()
{
    // don't iterate if current is NULL
    if (current != NULL)
    {
        current = current->prev;
    }
}

void CDLL::go_first()
{
    // first is the head of the CDLL
    current = head;
}

void CDLL::go_last()
{
    // don't iterate if current is NULL
    if (current != NULL)
    {
        current = head->prev;
    }
}

void CDLL::skip(unsigned int n)
{
    unsigned int num = CDLL::num_elements(current);
    // don't iterate passed the number of elements
    for (unsigned int i = 1; i <= n % num; i++)
    {
        current = current->next;
    }   
}

void CDLL::search(const char *word)
{
    CDLLNode *p = current->next;
    CDLLNode *end = current;

    
    while (p)
    {
        // break once the CDLL has been searched in entirety
        if(p == end) break;
        // set pLow to word
        std::string pLow = p->tweet;

        for (unsigned int i = 0; i < pLow.length(); ++i)
        {
            // convert pLow to lowercase
            pLow[i] = tolower(pLow[i]);
        }
        // if word is found, set current to p
        if((pLow).find(word) != std::string::npos)
        {
            current = p;
            break;
        }
        else
        { // other wise iterate p
            p = p->next;
        }
    }
}

void CDLL::print_current()
{
    if (current)
    {
        std::cout << current->time.substr(0, 19) << "    " << current->tweet << std::endl;
    }
}

void CDLL::print_all()
{
    if (head)
    {
        CDLLNode *p = head;
        while (1)
        {
            std::cout << p->time << " ";
            if (p->next == head)
            {
                break;
            }
            else
            {
                p = p->next;
            }
        }
    }
    std::cout << std::endl;
}
