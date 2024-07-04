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

int lxylazydegree = 0;
int fsuma = 0;
TuringMachine lxy;

void olx() {
    cout << endl << endl << endl;
}

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
    cout << "计算当前上界" << endl;
    olx();
    lxy.pos = 1 + i * 2;
    lxy.print();
    lxylazydegree++;
    cout << "计算当前上界" << endl;
    lxy.insertNum(sumT);
    lxylazydegree++;
    int leftT = T - sumT;// 剩余
    cout << "计算剩余重量" << endl;
    olx();
    lxy.pos = 1;
    lxy.print();
    lxylazydegree++;
    cout << "计算剩余重量" << endl;
    olx();
    lxy.pos = lxy.cnt;
    lxy.print();
    lxylazydegree++;
    cout << "计算当前上界" << endl;
    lxy.insertNum(leftT);
    lxylazydegree++;
    while (i < M && hrbs[i].tim <= leftT) {
        leftT -= hrbs[i].tim;
        sumV += hrbs[i].val;
        i++;
        lxy.pos = 1 + i * 2;
        cout << "计算当前上界" << endl;
        olx();
        lxy.print();
        lxylazydegree++;
        cout << "计算当前上界" << endl;
        lxy.insertNum(leftT);
        lxylazydegree++;
    }
    if (i < M){
        cout << "计算所需上界" << endl;
        sumV = sumV + leftT * (hrbs[i].val * 1.0 / hrbs[i].tim);
        lxy.insertNum(sumV);
        lxylazydegree++;
    }
    return sumV;
}


int solve() {
    int res = 0;
    Node r = { 0, 0, 0, bound(0, 0, 0) };
    que.push(r); //根结点
    //cout << r.sumT << " " << r.sumV << " " << r.maxV << endl;
    cout << "添加节点数据" << endl;
    lxy.insertNum(r.sumT);
    lxylazydegree++;
    cout << "添加节点数据" << endl;
    lxy.insertNum(r.sumV);
    lxylazydegree++;
    cout << "生成节点" << endl;
    lxy.insertNum(r.maxV);
    lxylazydegree++;
    while (que.top().maxV > res) {  //堆顶结点的上界大于已知最优值
        Node nd = que.top();
        que.pop();
        if (nd.nxt == M) {
            res = max(res, nd.sumV); //实际最优值
        }
        else {
            Node n2 = nd;
            cout << "判断需要草药时是否剪枝" << endl;
            lxy.insertNum(nd.sumT);
            lxylazydegree++;
            cout << "数据相加" << endl;
            lxy.insertNum(hrbs[nd.nxt].tim);
            lxylazydegree++;
            cout << "数据比较" << endl;
            lxy.insertNum(T);
            lxylazydegree++;
            if (nd.sumT + hrbs[nd.nxt].tim <= T) {  //剪枝

                cout << "无需剪枝，清除节点无关信息" << endl;
                lxy.erase();
                fsuma++;
                lxylazydegree++;
                cout << "无需剪枝，清除节点无关信息" << endl;
                lxy.erase();
                fsuma++;
                lxylazydegree++;
                cout << "无需剪枝，清除节点无关信息" << endl;
                lxy.erase();
                fsuma++;
                lxylazydegree++;


                nd.maxV = bound(nd.nxt, nd.sumT, nd.sumV);
                if (nd.maxV > res) {
                    nd.sumT += hrbs[nd.nxt].tim;
                    nd.sumV += hrbs[nd.nxt].val;
                    nd.nxt++;
                    que.push(nd);
                    res = max(res, nd.sumV);
                    //cout << n.sumT << " " << n.sumV << " " << n.maxV << endl;
                    cout << "添加节点数据" << endl;
                    lxy.insertNum(nd.sumT);
                    lxylazydegree++;
                    cout << "添加节点数据" << endl;
                    lxy.insertNum(nd.sumV);
                    lxylazydegree++;
                    cout << "生成节点" << endl;
                    lxy.insertNum(nd.maxV);
                    lxylazydegree++;

                }
            }
            else {
                cout << "需要剪枝,删除数据" << endl;
                lxy.erase();
                lxylazydegree++;
                cout << "需要剪枝,删除数据" << endl;
                lxy.erase();
                lxylazydegree++;
                cout << "需要剪枝,删除数据" << endl;
                lxy.erase();
                lxylazydegree++;
                fsuma = fsuma + 3;
            }

            n2.maxV = bound(n2.nxt + 1, n2.sumT, n2.sumV);// 不放当前草药时的上界
            cout << "添加无需草药时上界" << endl;
            lxy.insertNum(n2.maxV);
            lxylazydegree++;
            cout << "添加已知最优值" << endl;
            lxy.insertNum(res);
            lxylazydegree++;


            if (n2.maxV >= res) { // 上界小于当前已知最优值剪枝

                cout << "上界大，不剪枝，清除无关数据" << endl;
                lxy.erase();
                lxylazydegree++;
                cout << "上界大，不剪枝，清除无关数据" << endl;
                lxy.erase();
                lxylazydegree++;
                fsuma = fsuma + 2;

                n2.nxt++;
                que.push(n2);
                //cout << n2.sumT << " " << n2.sumV << " " << n2.maxV << endl;
                cout << "添加节点数据" << endl;
                lxylazydegree++;
                lxy.insertNum(n2.sumT);
                cout << "添加节点数据" << endl;
                lxy.insertNum(n2.sumV);
                lxylazydegree++;
                cout << "生成节点" << endl;
                lxy.insertNum(n2.maxV);
                lxylazydegree++;
            }
            else {
                cout << "最优值大，剪枝，删除" << endl;
                lxy.erase();
                lxylazydegree++;
                cout << "最优值大，剪枝，删除" << endl;
                lxy.erase();
                lxylazydegree++;
                fsuma = fsuma + 2;
            }
        }
    }
    return res;
}

void initBranch() {
    cout << "please input capacity and number of goods" << endl;
    cin >> T >> M;
    cout << "Please give " << M << " examples:" << endl;
    Herb h;
    for (int i = 0; i < M; i++) {
        cin >> h.tim >> h.val;
        hrbs.push_back(h);
    }
    cout << "放入初始数据" << endl;
    lxylazydegree++;
    lxy.insertNum(T);
    cout << "放入初始数据" << endl;
    lxylazydegree++;
    lxy.insertNum(M);
    for (int i = 0; i < hrbs.size(); i++) {

        cout << "放入初始数据" << endl;
        lxylazydegree++;
        lxy.insertNum(hrbs[i].tim);
        cout << "放入初始数据" << endl;
        lxylazydegree++;
        lxy.insertNum(hrbs[i].val);
    }

    sort(hrbs.begin(), hrbs.end(), greater<Herb>());
    lxy.insertChar('$');

    for (int i = 0; i < hrbs.size(); i++) {
        cout << "将数据排序" << endl;
        lxy.insertNum(hrbs[i].tim);
        lxylazydegree++;
        cout << "将数据排序" << endl;
        lxy.insertNum(hrbs[i].val);
        lxylazydegree++;
    }

    int funals = solve();

    cout << "maxval = " << funals << endl;
    cout << "step = " << lxylazydegree << endl;
    cout << "length = " << lxylazydegree - fsuma << endl;

    lxy.insertChar('$');
    lxy.insertNum(funals);
}
#endif
