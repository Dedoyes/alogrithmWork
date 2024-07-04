#ifndef BRANCHBOUND_H
#define BRANCHBOUND_H
#include<iostream>
#include<string>
#include<functional>
#include<queue>
#include<algorithm>
#include<vector>
#include "turing.h"
using namespace std;

TuringMachine lxy;

struct Herb {
    int tim, val;
    bool operator > (const Herb& x) const {
        return (val * 1.0 / tim) > (x.val * 1.0 / x.tim);
    }
};

struct Node {
    int nxt, sumT, sumV;// 下一药草的序号 当前总时间 当前总价值
    double maxV;// 上界
    bool operator < (const Node& x) const {
        return maxV < x.maxV;
    }
};

int T, M;
vector<Herb> hrbs;
priority_queue<Node> que;

double bound(int i, int sumT, int sumV) {
    double res = sumV;
    int leftT = T - sumT;// 剩余
    while (i < M && hrbs[i].tim <= leftT) {
        leftT -= hrbs[i].tim;
        sumV += hrbs[i].val;
        i++;
    }
    if (i < M) {
        sumV = sumV + leftT * (hrbs[i].val * 1.0 / hrbs[i].tim);
    }
    return sumV;
}

int lxylazydegree = 0;

int solve() {
    int res = 0;
    Node r = { 0, 0, 0, bound(0, 0, 0) };
    que.push(r); //根结点
    //cout << r.sumT << " " << r.sumV << " " << r.maxV << endl;
    lxy.insertNum(r.sumT);
    lxy.insertNum(r.sumV);
    lxy.insertNum(r.maxV);
    while (que.top().maxV > res) {  //堆顶结点的上界大于已知最优值
        lxylazydegree++;
        Node nd = que.top();
        que.pop();
        if (nd.nxt == M) {
            res = max(res, nd.sumV); //实际最优值
        }
        else {
            Node n2 = nd;
            if (nd.sumT + hrbs[nd.nxt].tim <= T) {  //剪枝
                nd.maxV = bound(nd.nxt, nd.sumT, nd.sumV);
                if (nd.maxV > res) {
                    nd.sumT += hrbs[nd.nxt].tim;
                    nd.sumV += hrbs[nd.nxt].val;
                    nd.nxt++;
                    que.push(nd);
                    res = max(res, nd.sumV);
                    //cout << n.sumT << " " << n.sumV << " " << n.maxV << endl;
                    lxy.insertNum(nd.sumT);
                    lxy.insertNum(nd.sumV);
                    lxy.insertNum(nd.maxV);

                }
            }
            n2.maxV = bound(n2.nxt + 1, n2.sumT, n2.sumV);// 不放当前草药时的上界


            if (n2.maxV >= res) { // 上界小于当前已知最优值剪枝
                n2.nxt++;
                que.push(n2);
                //cout << n2.sumT << " " << n2.sumV << " " << n2.maxV << endl;
                lxy.insertNum(n2.sumT);
                lxy.insertNum(n2.sumV);
                lxy.insertNum(n2.maxV);
            }
        }
    }
    return res;
}

void initBranch() {
    cout << "please input capacity and number of goods" << endl;
    cin >> T >> M;
    cout << "Please give "<< M << " examples:" << endl;
    Herb h;
    for (int i = 0; i < M; i++) {
        cin >> h.tim >> h.val;
        hrbs.push_back(h);
    }
    sort(hrbs.begin(), hrbs.end(), greater<Herb>());
    cout << "maxval = " << solve() << endl;
    cout << "step = " << lxylazydegree << endl;
}
#endif
