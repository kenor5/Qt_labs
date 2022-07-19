#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TODO: Implement destructor
    delete buffer;
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TODO: finish cmdAppend.
    while (true) {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        buffer->appendLine(text);
        buffer->totalLine ++;
        buffer->currentLineNum ++;
    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;

    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if(firstLine) {
            buffer->insertLine(text);
            firstLine = false;
        }
        else {
            buffer->appendLine(text);
        }

        buffer->totalLine ++;
        buffer->currentLineNum ++;
    }
    buffer->currentLineNum --;
//    cout << "currentLine:" << buffer->currentLineNum << endl;
}

void Editor::cmdDelete(int start, int end)
{

    if(start > end) {
        cout << "? Delete range error" << endl;
        return;
    }
    if(start > buffer->totalLine || end > buffer->totalLine || start <= 0 || end <= 0) {
        cout << "? Line number out of range" << endl;
        return;
     }
    buffer->deleteLines(start, end);
    int tempInt = end - start + 1;
    buffer->totalLine -= tempInt;
    buffer->currentLineNum = start + 1;
    if (buffer->currentLineNum > buffer->totalLine)
        buffer->currentLineNum = buffer->totalLine;
}

void Editor::cmdNull(int line)
{
    if(line > buffer->totalLine || line <= 0) {
        cout << "? Line number out of range" << endl;
        return;
      }
    cout << buffer->moveToLine(line) << endl;
    buffer->currentLineNum = line;
}

void Editor::cmdNumber(int start, int end)
{
    if(start > end) {
        cout << "? Number range error" << endl;
        return;
    }
    if(start > buffer->totalLine || end > buffer->totalLine || start <= 0 || end <= 0) {
        cout << "? Line number out of range" << endl;
        return;
     }
    buffer->showLines(start, end);
    buffer->currentLineNum = end;
}

void Editor::cmdWrite(const string &filename)
{
    if(filename == ""){
        cout << "? Filename not specified" << endl;
        return;
    }
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if(cmd == "w" || cmd == "w ") {
        cout << "? Filename not specified" << endl;
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
        cmdWrite(cmd.substr(2));
        return;
    }
    // TODO: handle special case "1,$n".
    if(cmd == "1,$n") {
        cmdNumber(1, buffer->totalLine);
        return;
    }
    int start, end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;

    if (ss.eof()) {
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;
    if (ss.good()) {
        if (type == 'n') {
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            cmdDelete(start, end);
            return;
        }
    }
    throw "Bad/Unknown command";
}
