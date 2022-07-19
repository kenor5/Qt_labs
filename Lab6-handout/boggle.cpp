#include "lexicon.h"
#include "lexicon.cpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
char map[100][100];
bool visited[100][100];
int n;
int scoreP = 0, scoreC = 0;
Lexicon *list;
std::string tmp;
std::string tmp_cpy;
std::vector<std::string> playerInput;
std::vector<std::string> comList;
std::ifstream fin(".\\0.in");
std::ofstream fout(".\\0.out");

using namespace std;
void wordIniWith(int x, int y);
void recursion(string str, int x, int y) ;


void curMap()
{
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            fout << map[i][j];
        fout << endl;
    }
}

bool check(string &str) 
{
   for (auto &c: str) c = toupper(c);
  for (auto it = comList.begin(); it !=  comList.end(); it++) {
      if (str == *it) {
        scoreC -= str.length() - 3;
        comList.erase(it);
        return 1;
      }
  }
  
  return 0;
}

void autofind()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            recursion("", i, j);
        }
}


void recursion(string str, int x, int y) 
{
    if (!list->containsPrefix(str)) {return;}
    if (x == 0 || y == 0 || x >= n+1 || y >= n+1) {return;}
    if (visited[x][y]) {return;}


    visited[x][y] = 1;

    str += map[x][y];
    if (list->contains(str) && str.length() > 3 && find(comList.begin(), comList.end(), str) == comList.end()) {
        comList.push_back(str);
        scoreC += str.length() - 3;
        if (!list->containsPrefix(str)) {
        visited[x][y] = 0;
        return;
        }
    }

    recursion(str, x, y+1);

    recursion(str, x+1, y);

    recursion(str, x-1, y);

    recursion(str, x, y-1);

    recursion(str, x-1, y-1);

    recursion(str, x+1, y-1);

    recursion(str, x-1, y+1);

    recursion(str, x+1, y+1);

    visited[x][y] = 0;
}

int main() 
{
    list = new Lexicon(".\\EnglishWords.txt");
    fin >> n;
    memset(map, 0, sizeof(map));
    memset(visited, 0, sizeof(visited));
    if(n >98) n = 98;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            fin >> map[i][j];
    
    autofind();
    while (1) {
        curMap();
        fout << "Your Score: " << scoreP << endl;
        fout << "Your Words:";
        for (auto it = playerInput.begin(); it !=  playerInput.end(); it++)
            fout << " " << *it;
        fout << endl;
        fin >> tmp;
        tmp_cpy = tmp;
        for (auto &c: tmp_cpy) c = tolower(c);;
        if (tmp == "???") break;

        if (tmp.length() < 4){
            fout << tmp << " is too short." << endl;
            continue;
        }

        int flag = 0;
        for (auto it = playerInput.begin(); it !=  playerInput.end(); it++) {
            
            if (*it == tmp_cpy) {
                fout << tmp << " is already found." << endl;
                flag = 1;
                break;
            }
        }
        if (flag) continue;

        if (!list->contains(tmp)) {
            fout << tmp << " is not a word." << endl;
            continue;
        }

        if (check(tmp_cpy)) {
            for (auto &c: tmp) c= tolower(c);
            playerInput.push_back(tmp);
            scoreP += tmp.length() - 3;
        }
        else {
            fout << tmp << " is not on board." << endl;
            continue;
        }
    }

    sort(comList.begin(), comList.end());
    fout << "Computer Score: " << scoreC << endl;
    fout << "Computer Words:";
    for (auto it = comList.begin(); it !=  comList.end(); it++)
            fout  << " " << *it;
    
    delete list;

    return 0;
}
