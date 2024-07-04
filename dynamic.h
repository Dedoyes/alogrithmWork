#ifndef DYNAMIC_H
#define DYNAMIC_H
#include <bits/stdc++.h>

#include "turing.h"
int w[MAXN], v[MAXN];
int dp[MAXN];
int parent[MAXN]; // 记录每个重量对应的选择状态
using namespace std;

void loadInitialTape() {
    turing.cnt = 0;
    turing.pos = 0;

    for (int i = 1; i <= n; i++) {
        turing.arr[turing.cnt++] = tuElement(1, w[i], "");
        turing.arr[turing.cnt++] = tuElement(1, v[i], "");
    }
    turing.arr[turing.cnt++] = tuElement(0, 0, "$");
    turing.arr[turing.cnt++] = tuElement(1, n, "");
    turing.arr[turing.cnt++] = tuElement(1, bag, "");
    turing.arr[turing.cnt++] = tuElement(0, 0, "$");
    for (int i = 0; i <= bag; i++) {
        turing.arr[turing.cnt++] = tuElement(1, dp[i], "");
    }
    turing.arr[turing.cnt++] = tuElement(0, 0, "$");
    for (int i = 0; i <= bag; i++) {
        turing.arr[turing.cnt++] = tuElement(1, parent[i], ""); // 初始化 parent 数组
    }
    turing.arr[turing.cnt++] = tuElement(0, 0, "$");
}

void knapsack() {
    for (int i = 1; i <= n; i++) {
        turing.pos = (i - 1) * 2; // 指向当前物品的重量
        turing.printTape("Read Weight");
        turing.pos = (i - 1) * 2 + 1; // 指向当前物品的重量
        turing.printTape("Read Value");

        for (int j = bag; j >= w[i]; j--) {
            int newValue = dp[j - w[i]] + v[i];
            turing.pos = n * 2 + 4 + j; // 移动读写头到 dp 数组的位置
            turing.printTape("Compare");
            if (newValue > dp[j]) {
                dp[j] = newValue;
                parent[j] = i; // 记录选择了这个物品
                turing.arr[n * 2 + 4 + j] = tuElement(1, dp[j], ""); // 更新纸带上的 dp 数组
                turing.pos = n * 2 + 4 + j; // 移动读写头到 dp 数组的位置
                turing.printTape("Write data");

                turing.arr[n * 2 + 4 + bag + 2 + j] = tuElement(1, parent[j], ""); // 更新纸带上的 parent 数组
                turing.pos = n * 2 + 4 + bag + 2 + j; // 移动读写头到 parent 数组的位置
                turing.printTape("Write parent data");
            }
        }
    }
}

void printSelectedItems() {
    vector<int> items;
    for (int j = bag; j > 0; ) {
        int i = parent[j];
        if (i == 0) break; // 没有更多的物品选择
        items.push_back(i);
        cout<<"j = "<<j<<endl;
        j -= w[i];
    }
    cout << "\033[1mSelected items: \033[0m";
    for (int i = items.size() - 1; i >= 0; i--) {
        cout <<"\033[1m"<< items[i] <<"\033[0m"<< (i == 0 ? "" : ", ");
    }
    cout << endl;
}

int dp_all() {
    cout << "please input number of thing and weight of bag: ";
    cin >> n >> bag;
    for (int i = 1; i <= n; i++) {
        cout << "please input " << i << "th weight and value: " << endl;
        cin >> w[i] >> v[i];
    }
    cout << endl;
    for (int i = 0; i <= bag; i++) {
        dp[i] = 0;
        parent[i] = 0; // 初始化 parent 数组
    }
    turing.moveTot = 0;
    loadInitialTape();
    turing.printTape("Initial tape");
    knapsack();
    turing.arr[turing.cnt++] = tuElement(1, dp[bag], "");
    // Print the final maximum value
    turing.pos = n * 2 + 8 + bag*2;
    turing.printTape("Final tape");
    cout << "\033[1mMax of values: " << "\033[4m" << "<" << dp[bag] << ">" << "\033[0m" << endl << endl;

    // Print selected items
    printSelectedItems();
    cout << endl;
    cout << "\033[1mCompleted.\33[5mPress any key to continue..." << "\033[0m" << endl << endl;
    system("pause");
    //system("cls");
    return 0;
}

#endif //DYNAMIC_H
