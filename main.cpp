#include <iostream>
#include "Tree.h"
#include <time.h>
#include <cmath>
#include <stdlib.h>

using namespace std;
typedef unsigned long long INT_64;

typedef int TYPE;

static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

unsigned long long LineRand() {
    unsigned long long a = rand();
    unsigned long long b = rand();
    a = ((a << 16) | b);
    return a;
}

void sRand() {
    srand(time(0));
    RRand = (INT_64) rand();
}

void test_rand(int n) {
    //создание дерева для 64 – разрядных ключей типа INT_64
    Tree<INT_64, int> tree;
    //массив для ключей, которые присутствуют в дереве
    auto *m = new INT_64[n];
//установка первого случайного числа
    sRand();
//заполнение дерева и массива элементами со случайными ключами
    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        tree.addNode(m[i], 1);
    }
//    tree.printTree();
//    cout << endl;
//вывод размера дерева до теста
    cout << "items count:" << tree.getSize() << endl;
//обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
//генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)        //10% промахов
        {
            tree.removeNode(LineRand());
            D += tree.getViewNode();
            tree.addNode(m[rand() % n], 1);
            I += tree.getViewNode();
            try {
                tree.getData(LineRand());
                S += tree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += tree.getViewNode(); }
//            cout << "Size1 = " << tree.getSize() << endl;
        } else  //90% успешных операций
        {
            int ind = rand() % n;
//            tree.printTree();
//            cout << "Index = " << ind << " , " << m[ind] << endl;
            tree.removeNode(m[ind]);
            D += tree.getViewNode();
            INT_64 key = LineRand();
            tree.addNode(key, 1);
            I += tree.getViewNode();
            m[ind] = key;
            try {
                tree.getData(m[rand() % n]);
                S += tree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += tree.getViewNode(); }
//            cout << i << "Size2 = " << tree.getSize() << endl;
        }    //конец теста

//вывод результатов:
//вывод размера дерева после теста
    cout << "items count:" << tree.getSize() << endl;
//теоретической оценки трудоёмкости операций BST
    cout << "1.39*log2(n)=" << 1.39 * (log((double) n) / log(2.0)) << endl;
//экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
//экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
//экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
//освобождение памяти массива m[]
    delete[] m;
}

void test_ord(int n) {
    //создание дерева для 64 – разрядных ключей типа INT_64
    Tree<INT_64, int> tree;
    //массив для ключей, которые присутствуют в дереве
    auto *m = new INT_64[n];

//заполнение дерева и массива элементами с возрастающими чётными //ключами на интервале [0, 10000, 20000, ... ,10000*n]
    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.addNode(m[i], 1);
    }
//вывод размера дерева до теста
    cout << "items count:" << tree.getSize() << endl;
//обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
//установка первого случайного числа
    sRand();
//генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0)        //10% промахов
        {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2);    //случайный нечётный ключ
            tree.removeNode(k);
            D += tree.getViewNode();
            tree.addNode(m[rand() % n], 1);
            I += tree.getViewNode();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2);    // случайный нечётный ключ
            try {
                tree.getData(k);
                S += tree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += tree.getViewNode(); }
        } else  //90% успешных операций
        {
            int ind = rand() % n;
            tree.removeNode(m[ind]);
            D += tree.getViewNode();;
            int k = LineRand() % (10000 * n);
            k = k + k % 2;        // случайный чётный ключ
            tree.addNode(k, 1);
            I += tree.getViewNode();;
            m[ind] = k;
            try {
                tree.getData(m[rand() % n]);
                S += tree.getViewNode();;
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error e) { S += tree.getViewNode(); }
        }
    }
//вывод результатов:
// вывод размера дерева после теста
    cout << "items count:" << tree.getSize() << endl;
//теоретической оценки трудоёмкости операций BST
    cout << "n/2 =" << n / 2 << endl;
//экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
//экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
//экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
//освобождение памяти массива m[]
    delete[] m;
}

void ClearConsole() {
    for (int i = 0; i < 5; ++i) {
        cout << endl;
    }
}

int main() {
    Tree<TYPE, TYPE> tree;
    Tree<>::Iterator iterator(&tree);
    Tree<>::Iterator iterator1(&tree);
    Tree<>::Reverse_Iterator reverseIterator(&tree);
    Tree<>::Reverse_Iterator reverseIterator1(&tree);
    bool Flag = true;
    while (Flag) {
        cout << "______________ Menu ________________\n"
                "1.  Output the size of list          |\n"
                "2.  Cleaning a list                  |\n"
                "3.  Is list empty?                   |\n"
                "4.  Get element by key               |\n"
                "5.  Set element by key               |\n"
                "6.  Push element by key              |\n"
                "7.  Remove element by key            |\n"
                "8.  Request begin for iterator       |\n"
                "9.  Request rbegin for iterator      |\n"
                "10. Request end for iterator         |\n"
                "11. Request rend for iterator        |\n"
                "12. Functions of iterator            |\n"
                "13. Request test_count last operation|\n"
                "14. Print a tree                     |\n"
                "15. Print a keys of tree             |\n"
                "16. Poryadkoviy number by key        |\n"
                "17. Test 1                           |\n"
                "18. Test 2                           |\n"
                "0.  Exit                             |\n"
                "-------------------------------------\n"
                "\n"
                "Input: ";
        int in;
        cin >> in;
        cout << endl;
        switch (in) {
            case 1: {
                ClearConsole();
                cout << "####### ACTION #######\n";
                cout << tree.getSize() << endl;
                break;
            }
            case 2: {
                ClearConsole();
                tree.clear();
                break;
            }
            case 3: {
                ClearConsole();
                cout << "####### ACTION #######\n";
                cout << boolalpha << tree.isEmpty() << endl;
                break;
            }
            case 4: {
                ClearConsole();
                cout << "Input the key: ";
                int key;
                cin >> key;
                cout << "####### ACTION #######\n";
                try {
                    cout << tree.getData(key) << endl;
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            }
            case 5: {
                ClearConsole();
                cout << "Input the key: ";
                TYPE key;
                cin >> key;
                cout << "Input the value: ";
                TYPE value;
                cin >> value;
                cout << boolalpha << tree.setNode(key, value) << endl;
                break;
            }
            case 6: {
                ClearConsole();
                cout << "Input the key: ";
                TYPE key;
                cin >> key;
                cout << "Input the value: ";
                TYPE value;
                cin >> value;
                cout << boolalpha << tree.addNode(key, value) << endl;
                break;
            }
            case 7: {
                ClearConsole();
                cout << "Input the key: ";
                TYPE key;
                cin >> key;
                cout << "####### ACTION #######\n";
                cout << boolalpha << tree.removeNode(key) << endl;
                break;
            }
            case 8: {
                ClearConsole();
                try {
                    iterator = tree.begin();
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }

                break;
            }
            case 10: {
                ClearConsole();
                try {
                    iterator = tree.end();
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            }

            case 9: {
                ClearConsole();
                try {
                    reverseIterator = tree.rbegin();
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }

                break;
            }
            case 11: {
                ClearConsole();
                try {
                    reverseIterator = tree.rend();
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            }
            case 12: {
                ClearConsole();
                bool iter = true;
                while (iter) {
                    cout << "_______Iterator menu________\n"
                            "1. Create a second iterator |\n"
                            "2. Read access (*)          |\n"
                            "3. Write access (*)         |\n"
                            "4. Go to next (++)          |\n"
                            "5. Go to previous (--)      |\n"
                            "6. Check equality           |\n"
                            "7. Check inequality         |\n"
                            "0. Exit                     |\n"
                            "----------------------------\n"
                            "\n"
                            "Input: ";
                    int in;
                    cin >> in;
                    switch (in) {
                        case 1: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: usual(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are set iterator on begin(1) or end(2)? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                iterator1 = tree.begin();
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                iterator1 = tree.end();
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else if (in == 2) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are set iterator on rbegin(1) or rend(2)? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                reverseIterator1 = tree.rbegin();
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                reverseIterator1 = tree.rend();
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }
                        case 2: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: usual(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                cout << *iterator << endl;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                cout << *iterator1 << endl;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else if (in == 2) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                cout << *reverseIterator << endl;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                cout << *reverseIterator1 << endl;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }
                        case 3: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: usual(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        cout << "Input the value: ";
                                        TYPE tmp;
                                        cin >> tmp;
                                        if (in == 1) {
                                            try {
                                                *iterator = tmp;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                *iterator = tmp;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else if (in == 2) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        cout << "Input the value: ";
                                        TYPE tmp;
                                        cin >> tmp;
                                        if (in == 1) {
                                            try {
                                                *reverseIterator = tmp;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                *reverseIterator1 = tmp;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }
                        case 4: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: usual(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                iterator++;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                iterator1++;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else if (in == 2) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                reverseIterator++;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                reverseIterator1++;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }
                        case 5: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: usual(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                iterator--;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                iterator1--;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else if (in == 2) {
                                    bool flag = true;
                                    while (flag) {
                                        cout << "Are use this operation for first or second iterator? (1/2)\n";
                                        int in;
                                        cin >> in;
                                        if (in == 1) {
                                            try {
                                                reverseIterator--;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                reverseIterator1--;
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else cout << "Incorrect input! Please repeat...\n";
                                    }
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }

                        case 6: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: usual(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    cout << "####### ACTION #######\n";
                                    cout << boolalpha << (iterator == iterator1) << endl;
                                    f = false;
                                } else if (in == 2) {
                                    cout << "####### ACTION #######\n";
                                    cout << boolalpha << (reverseIterator == reverseIterator1) << endl;
                                    f = false;
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }
                        case 7: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: usual(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    cout << "####### ACTION #######\n";
                                    cout << boolalpha << (iterator != iterator1) << endl;
                                    f = false;
                                } else if (in == 2) {
                                    cout << "####### ACTION #######\n";
                                    cout << boolalpha << (reverseIterator != reverseIterator1) << endl;
                                    f = false;
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }
                        default:
                            iter = false;
                    }
                }
                break;
            }
            case 15: {
                ClearConsole();
                tree.printKeys();
                cout << endl;
                break;
            }
            case 14: {
                ClearConsole();
                tree.printTree();
                cout << endl;
                break;
            }
            case 16: {
                ClearConsole();
                cout << "Input the key: ";
                int key;
                cin >> key;
                cout << "####### ACTION #######\n";
                try {
                    cout << tree.getIndexByKey(key) << endl;
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            }
            case 17: {
                ClearConsole();
                cout << "Input the count of elements: ";
                int count;
                cin >> count;
                test_rand(count);
                break;
            }
            case 18: {
                ClearConsole();
                cout << "Input the count of elements: ";
                int count;
                cin >> count;
                test_rand(count);
                break;
            }
            case 777: {
                srand(time(0));
                for (int i = 0; i < 10; ++i) {
                    tree.addNode(rand() % 101 + 1,rand() % 101 + 1);
                }
                break;
            }
            case 0: {
                Flag = false;
                break;
            }
            default:
                cout << "ERROR: Incorrect index of menu!\n";
        }
    }
    return 0;
}
