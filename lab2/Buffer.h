#pragma once

#include <string>

using std::string;

class linkList{
private:
    struct node{
      string data;
      node *pre;
      node *next;


      node(const string &str = "",
           node *pre = nullptr,
           node *next = nullptr):
           data(str), pre(pre), next(next) {}
      ~node(){}
    };
public:
    node *head, *tail;


    linkList();
    ~linkList();

    void insert(int currentLine, const string &str);
    void append(int currentLine, const string &str);
    void del(int pos1, int pos2);
    void clear();
    void print(int pos1, int pos2)const;
    void swap(int loc);
    node *move(int i)const;
};

class Buffer {
private:
    // TODO: add a List here for storing the input lines
    linkList ls;
public:
    int currentLineNum;
    int totalLine;


    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;
    const string &moveToLine(int idx) const;
    void showLines(int from, int to) const;
    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
