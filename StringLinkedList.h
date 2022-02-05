
#ifndef STRING_LINKED_LIST
#define STRING_LINKED_LIST
#include<string>
using namespace std;
class StringLLNode {
public:
    StringLLNode() {
        next = 0;
    }
    StringLLNode(string el, StringLLNode *ptr = 0) {
        info = el; next = ptr;
    }
    string info;
    StringLLNode *next;
};

class StringLList {
public:
    StringLList() {
        head = tail = 0;
    }
    ~StringLList();
    int isEmpty() {
        return head == 0;
    }
    void addToHead(string);
    void addToTail(string);
    string  deleteFromHead();
    string  deleteFromTail();
    void deleteNode(int);
    bool isInList(string) const;
    void printPage(int) const;
	string& firstEl();
    string& lastEl();
    int sizeOfList();
private:
    StringLLNode *head, *tail;


    friend class  TextEditor;
};

#endif





