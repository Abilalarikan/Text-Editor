#include "StringLinkedList.h"
#include<stack>
using namespace std;
class TextEditor{
private:
	stack<string> commands;
	stack<int> lineNumbers;
    stack<string> texts;
	StringLList lineList;
	int page;

	friend int main();

public:
	TextEditor(){
		page=0;
	}	
	void openFile(string);
	void saveFile(string);
	void insertText(int,string);
	string deleteLine(int);
	void moveLine(int,int);
	string replaceLine(int,string);
	void nextPage();
	void previousPage();
	void undo();
};

