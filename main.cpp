#include<stack>
#include<string>
#include<iostream>
#include <sstream>
#include "StringLinkedList.h"
#include "TextEditor.h"

using namespace std;

//Most of the exceptions of the functions were taken into account in main function (exceeding size, invalid commands etc.).

int main(){
    TextEditor myTextEditor;
    string a,command,text,n_str,m_str;
    int n=0,m=0;
    cout<<"          TEXT EDITOR"<<endl;
    cout<<"commands:\n    -open filename\n    -save filename\n    -insert n text";
    cout<<"\n    -delete n\n    -move n m\n    -replace n text\n    -next\n    -prev\n    -undo\n";
    cout<<"What would you like to do?(Enter 0 to exit)\n";
    getline(cin,a);
    while(a!="0"){

        command = a.substr (0,a.find(" "));

        if(myTextEditor.page==0 && command!="open"){
            cout<<"You need to open a file first."<<endl;
        }

        else if(command=="open"){
            text=a.substr(5,a.length()-5);
            myTextEditor.openFile(text);
        }

        else if(command=="save"){
            text=a.substr(5,a.length()-5);
            myTextEditor.saveFile(text);
        }

        else if(command=="insert"){
            int i=7,count=0;

            n=a[i];
            while(n>=48 && n<=57){
                count++;
                i++;
                n=a[i];
            }

            n_str=a.substr(7,count);

            stringstream convert(n_str);
            convert>>n;

            myTextEditor.commands.push("insert");
            myTextEditor.lineNumbers.push(n);

            text=a.substr(8+count,a.length()-8-count);
            myTextEditor.texts.push(text);

            myTextEditor.insertText(n,text);
        }

        else if(command=="delete"){
            int i=7,count=0;

            n=a[i];
            while(n>=48 && n<=57){
                count++;
                i++;
                n=a[i];
            }

            n_str=a.substr(7,count);

            stringstream convert(n_str);
            convert>>n;
            if(n>myTextEditor.lineList.sizeOfList())
                cout<<"There is no line "<<n<<endl;
            else{
                myTextEditor.commands.push("delete");
                myTextEditor.lineNumbers.push(n);

                string s;
                s=myTextEditor.deleteLine(n);

                myTextEditor.texts.push(s);
            }
        }

        else if(command=="move"){
            int i=5,count=0;

            n=a[i];
            while(n>=48 && n<=57){
                count++;
                i++;
                n=a[i];
            }

            n_str=a.substr(5,count);

            stringstream convert(n_str);
            convert>>n;
            if(n>myTextEditor.lineList.sizeOfList())
                cout<<"There is no line "<<n<<endl;
            else{
                myTextEditor.commands.push("move");
                i=6+count;
                int x=i;
                count=0;
                m=a[i];
                while(m>=48 && m<=57){
                    count++;
                    i++;
                    m=a[i];
                }
                m_str=a.substr(x,count);

                stringstream convert(m_str);
                convert>>m;
                myTextEditor.lineNumbers.push(n);
                myTextEditor.lineNumbers.push(m);

                myTextEditor.moveLine(n,m);

            }

        }

        else if(command=="replace"){
            int i=8,count=0;

            n=a[i];
            while(n>=48 && n<=57){
                count++;
                i++;
                n=a[i];
            }

            n_str=a.substr(8,count);

            stringstream convert(n_str);
            convert>>n;
            if(n>myTextEditor.lineList.sizeOfList())
                cout<<"There is no line "<<n<<endl;
            else{
                myTextEditor.commands.push("replace");
                myTextEditor.lineNumbers.push(n);

                text=a.substr(9+count,a.length()-9-count);

                string s;
                s=myTextEditor.replaceLine(n,text);
                myTextEditor.texts.push(s);
            }
        }

        else if(command=="next"){

            if(myTextEditor.lineList.sizeOfList()<myTextEditor.page*10+1)
                cout<<"There is no next page"<<endl;
            else{
                myTextEditor.nextPage();
                myTextEditor.commands.push("next");
            }
        }

        else if(command=="prev"){
            if(myTextEditor.page==1)
                cout<<"There is no previous page"<<endl;
            else{
                myTextEditor.previousPage();
                myTextEditor.commands.push("prev");
            }
        }

        else if(command=="undo"){
            myTextEditor.undo();
        }

        else
            cout<<"Please enter valid command"<<endl;

        cout<<"What would you like to do?(Enter 0 to exit)\n";
        getline(cin,a);

    }
}

