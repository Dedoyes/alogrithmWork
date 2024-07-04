#ifndef BACKTRACK_H
#define BACKTRACK_H
#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<vector>
#include<Windows.h>
using namespace std;
int cost[105];
int value[105];
int Time;
int n;  //记录物品种类
int ans;
struct Elements {
    int pos;
    int timeLeft;
    int tans;
    Elements(int _pos, int _timeLeft, int _tans) {
        pos = _pos;
        timeLeft = _timeLeft;
        tans = _tans;
    }
    void print() {
       // cout << pos << " " << timeLeft << " " << tans;
        printf("  dfs(%4d, %4d, %4d)  ", pos, timeLeft, tans);
    }
};
struct RecursiveSystem {
    int maxDeep;
    int curDeep;
    int step;
    int maxlen = 0;
    vector<Elements> dfs_stack;
    void push(Elements x) {
        dfs_stack.push_back(x);       
        //cout << "push :" << endl;
        //x.print();
        curDeep++;
        step++;
        maxDeep = max(maxDeep, curDeep);
        stackPrint();
        //cout << "curDeep = " << curDeep << endl;
        //maxDeep = max(maxDeep, curDeep);
    }
    void pop() {
        auto temp = dfs_stack[dfs_stack.size() - 1];
        dfs_stack.pop_back();
        curDeep--;
        step++;
        stackPrint();
        //cout << "pop :" << endl;
        //temp.print();
        ////cout << x.pos << " " << x.timeLeft << " " << x.tans << endl;
        //cout << "curDeep = " << curDeep << endl;
    }
    void stackPrint() {
        system("cls");
        cout << "|            top           |" << endl;
        cout << "|--------------------------|" << endl;
        for(auto x = dfs_stack.rbegin(); x != dfs_stack.rend(); x++) {
            cout << "|";
            x->print();
            cout << " |" << endl;
            cout << "|--------------------------|" << endl;
        }
        //cout << "top" << endl;
        //system("pause");  //手动版本
        _sleep(500);        //动画版本
    }

        
    void dfs(int pos, int timeLeft, int tans) {
        if(timeLeft < 0) {
            pop();
            return;
        }
        if(pos == n + 1) {
            ans = max(ans, tans);
            pop();
            return;
        }
        //cout << "dfs(" << pos << " + 1," << timeLeft << ")" << endl;
        push(Elements(pos + 1, timeLeft, tans));
        dfs(pos + 1, timeLeft, tans);   
        if(timeLeft >= cost[pos]) {
            //cout << "dfs(" << pos << " + 1," << timeLeft << " - " << "cost[" << pos <<"]" << " + " << "value[" << pos << "]" << endl;
            push(Elements(pos + 1, timeLeft - cost[pos], tans + value[pos]));
            dfs(pos + 1, timeLeft - cost[pos], tans + value[pos]);
            if(!dfs_stack.empty()) {
                pop();
            }
        }
        
    }

}sysBackTrack;
void BackTrack() {
    cin >> Time >> n;
    for(int i = 1; i <= n; i++) {
         cin >> cost[i] >> value[i];
    }
    sysBackTrack.dfs(1, Time, 0);
    cout << "answer = " << ans << endl;
    cout << "maxDeep = " << sysBackTrack.maxDeep << endl;
    cout << "最大空间  = " << sysBackTrack.maxDeep * sizeof(int) * 3 << " byte" << endl;
    cout << "step = " << sysBackTrack.step << endl;
}

#endif
