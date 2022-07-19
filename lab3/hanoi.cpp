#include "termio.h"

// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];

Stack From = Stack(200), To = Stack(200);

bool checkFromEmpty(int n) {
    switch (n){
        case 1:return !disk1.empty();
        case 2:return !disk2.empty();
        case 3:return !disk3.empty();
        default:return false;
    }
}

bool checkOrder(int from, int to) {

    switch(from){
        case 1:
        switch(to){
            case 1: return 0;
            case 2: return disk2.topelem()>disk1.topelem();
            case 3:  return disk3.topelem()>disk1.topelem();
        }

        case 2:
        switch(to){
            case 1: return disk1.topelem()>disk2.topelem();
             case 2: return 0;
            case 3: return disk3.topelem()>disk2.topelem();
        }
        case 3:
        switch(to){
            case 2: return disk2.topelem()>disk3.topelem();
            case 1: return disk1.topelem()>disk3.topelem();
             case 3: return 0;
        }
    }
    return 0;
}

bool checkNow() {
    return disk1.empty()&&disk3.empty();
}

void withdraw() {
    while(!From.empty()) {

    int from = From.pop();
    int to = To.pop();
    Termio::move(to, from);
    Termio::renew();
    cout << "Auto moving:"<< to <<"->" << from << "\n";
    Termio::Draw();
    }
}

void hanio(int n, int from, int to, int buff){
    if(n==0)return;
    if(n == 1) {
        Termio::move(from, to);
        cout << "Auto moving:"<< from <<"->" << to << "\n";
        Termio::Draw();
        return;
    }
    hanio(n-1, from, buff, to);
    Termio::move(from, to);
    cout << "Auto moving:"<< from <<"->" << to << "\n";
    Termio::Draw();
    hanio(n-1, buff, to, from);
}

void auto1(int n) {
    hanio(n, 1, 2, 3);
}

void auto2(int num2, int num3) {
    hanio(num2+num3, 1, 2, 3);
    hanio(num3, 2, 3, 1);
}


int main() {

    begin:
    disk1.clear();
    disk2.clear();
    disk3.clear();

    std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;

    int numOfDisk;
    string command;

    cin >> command;
    if(command == "Q") return 0;

    Termio termio;
    numOfDisk = stoi(command);
    if(numOfDisk >5 || numOfDisk < 1 ) goto begin;

    Termio::ResetBuffer();
    //往第一个柱子上添加n个饼子
    for (int i = numOfDisk; i >=1; i--) {
        disk1.push(i);
    }
    termio.renew();

    int from, to;
    while (true){
        termio.Draw();
        std::cout << "Move a disk. Format: x y" << std::endl;
        cin >> from >> to;
        if(from >3||to>3)continue;

//      自动一档
        if(from == 0 && to == 0){
            withdraw();
            auto1(numOfDisk);
            std::cout << "Congratulations! You win!" << std::endl;
            goto begin;
        }

//      自动2挡
        if(from <= 0 && to <= 0) {
            int temp;
            cin >> temp;
            withdraw();
            auto2((-1)*to, (-1)*temp);
            std::cout << "Congratulations! You win!" << std::endl;
            goto begin;
        }
//      检查是否移动空柱子或者大盘叠小盘
        if(checkFromEmpty(from)&&checkOrder(from, to)) {

            From.push(from);
            To.push(to);
            termio.move(from, to);
        }

//      检查赢了没有
        if(checkNow()) {
            termio.Draw();
            std::cout << "Congratulations! You win!" << std::endl;
            goto begin;
        }

    }

    return 0;
}
