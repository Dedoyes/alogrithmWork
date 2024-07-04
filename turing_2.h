#ifndef TEAM_ALGORITHM_TURING_H
#define TEAM_ALGORITHM_TURING_H

struct tuElement {
    int type;
    int num;
    std::string s;
    tuElement () {}
    tuElement (int _type, int _num, std::string _s) {
        type = _type; num = _num; s = _s;
    }
    inline void print () {
        if (type == 1) {
            std::cout << num;
        } else {
            std::cout << s;
        }
    }
    inline int size () {
        if (type == 2) {
            return s.size ();
        } else {
            int temp = num;
            int ret = 0;
            if (num == 0)
                ret = 1;
            while (num) {
                num /= 10;
                ret++;
            }
            num = temp;
            return ret;
        }
    }
};

struct TuringMachine {
    int pos;
    int cnt;
    int moveTot;
    tuElement arr[MAXN];

    void printTape(const std::string& operation) {
        Sleep(500);
        system("cls");
        std::cout << "Turing DP for 0-1 bag            \n";
        std::cout<<std::endl;
        moveTot++;
        int l = 1, r = 1;
        for (int i = 0; i <= cnt; i++) {
            r += arr[i].size() + 3;
            if (pos == i) {
                int mid = (l + r) >> 1;
                for (int j = l; j <= mid - 1; j++)
                    std::cout << "_";

                std::cout << "v";
                for (int j = mid + 1; j <= r; j++)
                    std::cout << "_";
            } else {
                for (int j = l; j <= r; j++) {
                    std::cout << "_";
                }
            }
            l = r + 1;
        }

        std::cout << std::endl;
        for (int i = 0; i <= cnt; i++) {
            std::cout << "| ";
            if (arr[i].type == 1) {
                std::cout << arr[i].num;
            } else {

                std::cout << arr[i].s;
            }
            std::cout << " ";
        }
        //Sleep(100);
        std::cout << "|" << std::endl;
        for (int i = 1; i <= r; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        std::cout << "Now is the "<<moveTot<<" step"<<"  "<<"Operation: " << operation << std::endl;
        std::cout << "Length of tape is "<<cnt<< std::endl;

    }

    void insertNum (int x) {
        this->cnt++;
        this->pos = this->cnt;
        moveTot++;
        this->arr[cnt] = tuElement (1, x, "");
        std::cout << "插入数字" << x << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        this->print ();
    }
    void insertChar (char x) {
        this->cnt++;
        this->pos = this->cnt;
        moveTot++;
        std::string tempS;
        tempS += x;
        this->arr[cnt] = tuElement (0, 0, tempS);
        std::cout << "写入字符" << x << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        this->print ();
    }
    void erase () {
        this->cnt--;
        std::cout << "删除" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        this->print ();
    }
    void print () {
        int l = 1, r = 1;
        for (int i = 1; i <= cnt; i++) {
            r += arr[i].size () + 3;
            if (pos == i) {
                int mid = (l + r) >> 1;
                for (int j = l; j <= mid - 1; j++)
                    std::cout << "_";
                std::cout << "v";
                for (int j = mid + 1; j <= r; j++)
                    std::cout << "_";
            } else {
                for (int j = l; j <= r; j++) {
                    std::cout << "_";
                }
            }
            l = r + 1;
        }
        std::cout << std::endl;
        for (int i = 1; i <= cnt; i++) {
            std::cout << "| ";
            if (this->arr[i].type == 1) {
                std::cout << this->arr[i].num;
            } else {
                std::cout << this->arr[i].s;
            }
            std::cout << " ";
        }
        std::cout << "|";
        std::cout << std::endl;
        for (int i = 1; i <= r; i++)
            std::cout << "-";
        std::cout << std::endl;
        Sleep(1000);
        system ("cls");
    }
    int binSearch (int x) {
        int L, R;
        this->pos = n + 2;
        moveTot++;
        L = arr[this->pos].num;
        std::cout << "读取L" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        this->print ();
        this->pos = n + 3;
        moveTot++;
        std::cout << "读取R" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        this->print ();
        R = arr[this->pos].num;
        this->insertChar ('$');
        this->insertNum ((L + R) >> 1);
        while (L <= R) {
            this->pos = n + 2;
            moveTot++;
            std::cout << "读取L" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            this->print ();
            L = arr[this->pos].num;
            this->pos = n + 3;
            moveTot++;
            std::cout << "读取R" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            this->print ();
            R = arr[this->pos].num;
            int mid = (L + R) >> 1;
            this->erase ();
            this->insertNum (mid);
            this->pos = mid;
            moveTot++;
            std::cout << "指针转移到数组下标为" << mid << "的位置" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            this->print ();
            if (arr[this->pos].num == x) {
                std::cout << "当前元素 = " << x << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                this->print ();
                return this->pos;
            } else if (arr[this->pos].num < x) {
                std::cout << "当前元素 < " << x << std::endl;
                std::cout << "更改L值" << std::endl;
                std::cout << std::endl;
                this->pos = n + 2;
                moveTot++;
                arr[this->pos].num = mid + 1;
                this->print ();
            } else {
                std::cout << "当前元素 > " << x << std::endl;
                std::cout << "更改R值" << std::endl;
                std::cout << std::endl;
                this->pos = n + 3;
                moveTot++;
                arr[this->pos].num = mid - 1;
                this->print ();
            }
        }
        return -1;
    }
} turing;

#endif //TEAM_ALGORITHM_TURING_H
