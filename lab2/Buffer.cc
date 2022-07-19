#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    currentLineNum = 0;
}

Buffer::~Buffer() {}

linkList::linkList()
{
    head = new node;
    head->next = tail = new node;
    tail->pre = head;
}

linkList::~linkList()
{
    delete head;
    delete tail;
    clear();
}

void linkList::del(int pos1, int pos2){
    node *temp = move(pos1);
    int tempLen = pos2 - pos1 + 1;
    while (tempLen--) {
        node *temp2 = temp;
        temp2->pre->next = temp2->next;
        temp2->next->pre = temp2->pre;
        temp = temp->next;
        delete temp2;

    }
}



void linkList::clear()
{
    node *temp = head->next;
    while (temp != tail) {
        node *temtemp = temp;
        temp = temp->next;
        delete temtemp;
    }
    head->next = tail;
    tail->pre = head;

}

void linkList::print(int pos1, int pos2)const{
    node *temp = move(pos1);
    int temp1 = pos1;
    while (temp1 <= pos2) {
        std::cout << temp1 << "\t" << temp->data << std::endl;
        temp = temp->next;
        temp1 ++;
    }
//    std::cout << "End of Print!" << std::endl;
}

void linkList::insert(int currentLine, const string &str)
{

    if(currentLine == 0) {
        node *ptr = new node(str, head, tail);
        head->next = ptr;
        tail->pre = ptr;
        return;
    }
    node *cur = move(currentLine);
    node *temp = new node(str, cur->pre, cur);
    cur->pre->next = temp;
    cur->pre = temp;
//    std::cout << "insert" << currentLine <<std::endl;
//    append(currentLine, str);
//    if(currentLine>1)
//    swap(currentLine);
}

void linkList::swap(int loc) {
    node *temp = move(loc);
    node *temp1 = move(loc+1);
    temp->pre->next = temp1;
    temp1->next->pre = temp;
    temp->next = temp1->next;
    temp1->pre = temp->pre;
    temp->pre = temp1;
    temp1->next = temp;
}

void linkList::append(int currentLine, const string &str){
    if(currentLine == 0) {
        node *ptr = new node(str, head, tail);
        head->next = ptr;
        tail->pre = ptr;
        return;
    }
    node *cur = move(currentLine);
    node *temp = new node(str, cur, cur->next);

    cur->next->pre = temp;
    cur->next = temp;
}

linkList::node *linkList::move(int i)const {
    node *temp = head;
    while (i--) {
        if(temp == tail) return nullptr;
        temp = temp->next;
    }
    return temp;
}

int getSize(const string &filename) {
      int length;
//      char * buffer;

      std::ifstream is;
      is.open (filename, std::ios::binary );

      // get length of file:
      is.seekg (0, std::ios::end);
      length = is.tellg();
      is.seekg (0, std::ios::beg);

      // allocate memory:
//      buffer = new char [length];

      // read data as a block:
//      is.read (buffer,length);

      is.close();

//      std::cout.write (buffer,length);
      return length;
}

void Buffer::writeToFile(const string &filename) const {
    std::ofstream fout(filename);
    int length = 0;
    for (int i = 1; i <= this->totalLine; i++) {
        string str = moveToLine(i);
        length += str.length() + 1;
        fout << str << std::endl;
    }
    std::cout << length  << " byte(s) written" << std::endl;
}

void Buffer::showLines(int from, int to) const {
    ls.print(from, to);
}

void Buffer::deleteLines(int from, int to){
    ls.del(from, to);
}

void Buffer::insertLine(const string &text){
    ls.insert(this->currentLineNum, text);
}

void Buffer::appendLine(const string &text){
    ls.append(this->currentLineNum, text);

}

const string &Buffer::moveToLine(int idx) const{
    return ls.move(idx)->data;
}
