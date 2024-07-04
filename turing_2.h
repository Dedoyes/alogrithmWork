void printTape(const std::string& operation) {
        //Sleep(500);
        //system("pause");
        system("cls");

        std::cout << "\033[1;4;36mTuring DP for 0-1 bag"<<"\033[0m";//green
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\033[1;33mTape:"<<"\033[0m";//blue
        std::cout << std::endl;
        std::cout << std::endl;
        moveTot++;
        int l = 1, r = 1;
        for (int i = 0; i <= cnt; i++) {
            r += arr[i].size() + 3;
            if (pos == i) {
                int mid = (l + r) >> 1;

                for (int j = l; j <= mid - 1; j++)
                    std::cout << "\033[1m_\033[0m";

                std::cout << "\033[1;31m"<<"V"<<"\033[0m";
                for (int j = mid + 1; j <= r; j++)
                    std::cout << "\033[1m_\033[0m";
            } else {
                for (int j = l; j <= r; j++) {
                    std::cout << "\033[1m_\033[0m";
                }
            }
            l = r + 1;
        }
        std::cout << std::endl;
        for (int i = 0; i <= n*2+3; i++) {
            std::cout << "\033[1m| \033[0m";
            if (arr[i].type == 1) {
                std::cout << "\033[1;32m" << arr[i].num << "\033[0m"; // 绿色
            } else {
                std::cout << "\033[1;34m" << arr[i].s << "\033[0m"; // 蓝色
            }
            std::cout << " ";
        }
        for (int i = n*2+4; i <=n*2+4+bag ; i++) {
            std::cout << "\033[1m| \033[0m";
            if (arr[i].type == 1) {
                std::cout << "\033[1;33m" << arr[i].num << "\033[0m"; // 绿色
            } else {
                std::cout << "\033[1;34m" << arr[i].s << "\033[0m"; // 蓝色
            }
            std::cout << " ";
        }
        for (int i = n*2+4+bag+1; i <= cnt; i++) {
            std::cout << "\033[1m| \033[0m";
            if (arr[i].type == 1) {
                std::cout << "\033[1;36m" << arr[i].num << "\033[0m"; // 绿色
            } else {
                std::cout << "\033[1;34m" << arr[i].s << "\033[0m"; // 蓝色
            }
            std::cout << " ";
        }
        std::cout << "\033[1m|\033[0m" << std::endl;
        for (int i = 1; i <= r; i++) {
            std::cout << "\033[1m-\033[0m";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout <<"\033[1m"<<"Step: "<<"\033[4m"<<"<" << moveTot << ">"<<"\033[0m"<<"        "<<"\033[1m";
        std::cout<<std::endl<<std::endl;
        std::cout<<"Operation: "<<"\033[4m"<<"<" << operation << ">\033[0m";
        std::cout<<std::endl;
        std::cout << std::endl;
        std::cout <<"\033[1mLength of tape: "<<"\033[4m"<<"<" << cnt<< ">\033[0m" << std::endl;
        std::cout << std::endl;
    }
