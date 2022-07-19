#pragma once
/* some code from Libconio 1.0 (C) 2004 FSL A.C. */

#ifdef _WIN32
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static void clrscr()
{
    system("cls");
}
#else
#include <termios.h>
#include <stdio.h>
#define ESC 033 /* Escape char */

static int getch()
{
    struct termios t;
    int c;

    tcgetattr(0, &t);
    t.c_lflag &= ~ECHO + ~ICANON;
    tcsetattr(0, TCSANOW, &t);
    fflush(stdout);
    c = getchar();
    t.c_lflag |= ICANON + ECHO;
    tcsetattr(0, TCSANOW, &t);
    return c;
}

static void clrscr()
{
    printf("%c[2J", ESC);
    printf("%c[%d;%dH", ESC, 0, 0);
}
#endif

class Stack{
    int *data;
    int top;
public:
    Stack(int n = 7){
        data = new int[n];
        top = 0;
    }
    ~Stack(){delete []data;}
    int pop() {top--;return data[top+1];}
    void push(int n){top++; data[top] = n;}
    bool empty(){return top==0;}
    int size(){return top;}
    int elem(int n){return data[n];}
    void clear(){top = 0;}
    int topelem(){if(top) return data[top];
                 else return 6;}
};

//class Queue{
//    int *data;
//    int head, tail, size;
//    int length;
//public:
//    Queue(int n){
//        size = n;
//        data = new int[size];
//        head = tail = 0;
//        length = 0;
//    }
//    ~Queue(){delete []data;}
//    void push(int n){tail = (tail+1)%size; data[tail] = n; length++;}
//    void pop(){head = (head+1)%size; length--;}
//    bool empty(){return length==0;}
//};


#include <iostream>
#include <cstring>
using namespace std;

Stack disk1 = Stack(), disk2 = Stack(), disk3 = Stack();

class Termio
{
    //画饼子的封装函数
    static void renew(Stack &stack, int n){

        if(stack.empty()) return;
        int col = 5 + 15*(n-1);
        int height = initHeight(stack.size());
        int stackSize = stack.size();
        for(int i = height, j = 0; j < stack.size(); j++, i += 2) {

//            memset(buffer[i], ' ', CANVAS_WIDTH);
            buffer[i][col] = '*';
            for(int l = stack.elem(stackSize - j); l >=1 ; l--) {
                buffer[i][col+l] = '*';
                buffer[i][col-l] = '*';
            }
        }
    }
public:
    // donot change the width and height
    static const int CANVAS_WIDTH = 41;
    static const int CANVAS_HEIGHT = 11;
    static char buffer[CANVAS_HEIGHT][CANVAS_WIDTH + 1];



    static char GetChar() {
        return getch();
    }

    static void Clear() {
        clrscr();
    }

    static void Draw() {
        for (int i = 0; i < CANVAS_HEIGHT; i++)
        {
            buffer[i][CANVAS_WIDTH] = '\0';
            cout << buffer[i] << endl;
        }
    }

    //把柱子清空
    static void ResetBuffer() {
        for (int i = 0; i < CANVAS_HEIGHT; i++){
            memset(buffer[i], ' ', CANVAS_WIDTH);//为什么不加这一行就不行
            buffer[i][5] = '|';
            buffer[i][20] = '|';
            buffer[i][35] = '|';
        }
        for (int i = 0; i < CANVAS_WIDTH; i++) {
            if(i == 5 || i == 20 || i == 35) continue;
            buffer[CANVAS_HEIGHT-1][i] = '-';
        }
    }

    //最上面的饼子的高度
    static int initHeight(int n){return 11-2*n;}

    //往柱子上面加饼子
    static void renew() {
        ResetBuffer();
        renew(disk1, 1);
        renew(disk2, 2);
        renew(disk3, 3);
    }

    //移动饼子的函数，封装不到位
    static void move(int from, int to){
        switch(from){
            case 1:

            switch(to){
                case 2: disk2.push(disk1.pop());renew();return;
                case 3: disk3.push(disk1.pop());renew();return;
            }

            case 2:
            switch(to){
                case 1: disk1.push(disk2.pop());renew();return;
                case 3: disk3.push(disk2.pop());renew();return;
            }
            case 3:
            switch(to){
                case 2: disk2.push(disk3.pop());renew();return;
                case 1: disk1.push(disk3.pop());renew();return;
            }
        }
    }


};
