#include<stack>
#include<string>
#include<iostream>
#include <fstream>
#include "StringLinkedList.h"
#include "TextEditor.h"

using namespace std;

void TextEditor::openFile(string filename){
	ifstream f;
	string line;
	
	page=0;
	
	
	while(!commands.empty())
		commands.pop();
	
	while(!lineNumbers.empty())
		lineNumbers.pop();
	
	while(!texts.empty())
		texts.pop();
	
	while(!lineList.isEmpty())
		lineList.deleteFromTail();
	
	
	f.open(filename.c_str());
	while(getline(f,line))
		lineList.addToTail(line);

    f.close();

	page=1;
	lineList.printPage(page);

}

void TextEditor::saveFile(string filename){
    ofstream myfile;
    StringLLNode *ptr=lineList.head;

    myfile.open(filename);
    if(myfile.is_open())
        while(ptr!=NULL){
            myfile<<ptr->info<<endl;
                ptr=ptr->next;
        }

	myfile.close();
    cout<<"Contents are saved on "<<filename<<endl;
}

void TextEditor::insertText(int n,string text){

    StringLLNode *tmp=lineList.head;
    StringLLNode *ptr;
    int i;
    if(n==1)
        lineList.addToHead(text);

    else if(n<=lineList.sizeOfList()){
        for(i=0;i<n-2;i++)
            tmp=tmp->next;
        ptr=new StringLLNode;
        ptr->next=tmp->next;
        tmp->next=ptr;
        ptr->info=text;
    }
    else{
        int x=n-lineList.sizeOfList()-1;
        for(i=0;i<x;i++)
            lineList.addToTail(" ");
        lineList.addToTail(text);
    }

    lineList.printPage(page);
}

string TextEditor::deleteLine(int lineNumber){

    StringLLNode *tmp=lineList.head;
    int i;
    string s;

    for(i=1;i<lineNumber;i++)
        tmp=tmp->next;

    s=tmp->info;
    lineList.deleteNode(lineNumber);

    i=1;
    tmp=lineList.head;
    while(tmp!=NULL){
        if(tmp->info==" "){
            tmp=tmp->next;
            lineList.deleteNode(i);
            continue;
        }
        tmp=tmp->next;
        i++;
    }

    lineList.printPage(page);

    return s;

}

void TextEditor::moveLine(int n,int m){
    StringLLNode *tmp1=lineList.head,*tmp2,*ptr;
    int i;
    string s;

    for(i=1;i<n;i++)
        tmp1=tmp1->next;
    s=tmp1->info;
    deleteLine(n);

    if(m>lineList.sizeOfList()){
        int size=lineList.sizeOfList();
        for(int x=0;x<m-size-1;x++)
            lineList.addToTail(" ");
        lineList.addToTail(s);
    }
    else if(m==1){
        lineList.addToHead(s);
    }
    else{
        tmp2=lineList.head;
        for(i=1;i<m-1;i++)
            tmp2=tmp2->next;

        ptr=new StringLLNode;
        ptr->info=s;
        ptr->next=tmp2->next;
        tmp2->next=ptr;
    }
    lineList.printPage(page);
}

string TextEditor::replaceLine(int lineNumber,string text){
    StringLLNode *tmp=lineList.head;
    string s;
    for(int i=0;i<lineNumber-1;i++)
        tmp=tmp->next;

    s=tmp->info;
    tmp->info=text;

    lineList.printPage(page);

    return s;
}

void TextEditor::nextPage(){
    page+=1;

    lineList.printPage(page);
}

void TextEditor::previousPage(){
    page-=1;

    lineList.printPage(page);
}

void TextEditor::undo(){
    string command,text;
    int n,m;

    if(commands.empty())
        cout<<"There is no tool to undo."<<endl;
    else{
        command=commands.top();
        commands.pop();

        if(command=="insert"){
            n=lineNumbers.top();
            lineNumbers.pop();

            texts.pop();

            deleteLine(n);
        }
        else if(command=="delete"){
            n=lineNumbers.top();
            lineNumbers.pop();

            text=texts.top();
            texts.pop();

            insertText(n,text);
        }

        else if(command=="move"){
            n=lineNumbers.top();
            lineNumbers.pop();

            m=lineNumbers.top();
            lineNumbers.pop();

            moveLine(n,m);
        }
        else if(command=="replace"){
            n=lineNumbers.top();
            lineNumbers.pop();

            text=texts.top();
            texts.pop();

            replaceLine(n,text);
        }

        else if(command=="next")
            previousPage();

        else if(command=="prev")
            nextPage();
    }
}
