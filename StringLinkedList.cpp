#include <iostream>
#include "StringLinkedList.h"
#include<string>
using namespace std;

StringLList::~StringLList() {
    for (StringLLNode *p; !isEmpty(); ) {
        p = head->next;
        delete head;
        head = p;
    }
}

void StringLList::addToHead(string el) {
    head = new StringLLNode(el,head);
    if (tail == 0)
       tail = head;
}

void StringLList::addToTail(string el) {
    if (tail != 0) {      // if list not empty;
         tail->next = new 	StringLLNode(el);
         tail = tail->next;
    }
    else head = tail = new StringLLNode(el);
}

string StringLList::deleteFromHead() {
    string el = head->info;
    StringLLNode *tmp = head;
    if (head == tail)
         head = tail = 0;
    else head = head->next;
    delete tmp;
    return el;
}

string StringLList::deleteFromTail() {
    string el = tail->info;
    if (head == tail) {
         delete head;
         head = tail = 0;
    }
    else {
         StringLLNode *tmp;
         for (tmp = head; tmp->next != tail; tmp = tmp->next);
         delete tail;
         tail = tmp;
         tail->next = 0;
    }
    return el;
}

void StringLList::deleteNode(int el) {
    int x=2;
    if (head != 0)
         if (head == tail && el == 1) {
              delete head;
              head = tail = 0;
         }
         else if (el == 1) {
              StringLLNode *tmp = head;
              head = head->next;
              delete tmp;
         }
         else {
              StringLLNode *pred, *tmp;
              for (pred = head, tmp = head->next;
                   tmp != 0 && !(x == el);
                   pred = pred->next, tmp = tmp->next)x++;
              if (tmp != 0) {
                   pred->next = tmp->next;
                   if (tmp == tail)
                      tail = pred;
                   delete tmp;
              }
         }
}

bool StringLList::isInList(string el) const {
		StringLLNode *tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}

void StringLList::printPage(int page) const {
    StringLLNode *tmp = head;
    int i=(page-1)*10+1,x;
    for(x=0;x<i-1;x++)
        tmp=tmp->next;

    for (;i<=page*10 && tmp!=NULL;i++ ){
        cout <<i<<")"<< tmp->info << "\n";
        tmp = tmp->next;
    }
    cout<<"\n";
	cout<<"---page "<<page<<"---"<<endl;
}

string& StringLList::firstEl() {
    return head->info;
}
string& StringLList::lastEl() {
    return tail->info;
}

int StringLList::sizeOfList(){
    StringLLNode *tmp=head;
    int count=0;
    while(tmp!=NULL){
        count++;
        tmp=tmp->next;
    }
    return count;
}
