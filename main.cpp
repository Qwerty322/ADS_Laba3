#include <iostream>
#include "Tree.h"
#include "RNDTree.h"
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
    Tree<INT_64, int> RandTree;
    //массив для ключей, которые присутствуют в дереве
    auto *m = new INT_64[n];
//установка первого случайного числа
    sRand();
//заполнение дерева и массива элементами со случайными ключами
    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        RandTree.addNode(m[i], 1);
    }
//вывод размера дерева до теста
    cout << "items count:" << RandTree.getSize() << endl;
//обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
//генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)        //10% промахов
        {
            RandTree.removeNode(LineRand());
            D += RandTree.getViewNode();
            RandTree.addNode(m[rand() % n], 1);
            I += RandTree.getViewNode();
            try {
                RandTree.getData(LineRand());
                S += RandTree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += RandTree.getViewNode(); }
        } else  //90% успешных операций
        {
            int ind = rand() % n;
            RandTree.removeNode(m[ind]);
            D += RandTree.getViewNode();
            INT_64 key = LineRand();
            RandTree.addNode(key, 1);
            I += RandTree.getViewNode();
            m[ind] = key;
            try {
                RandTree.getData(m[rand() % n]);
                S += RandTree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += RandTree.getViewNode(); }
        }    //конец теста

//вывод результатов:
//вывод размера дерева после теста
    cout << "items count:" << RandTree.getSize() << endl;
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
    Tree<INT_64, int> RandTree;
    //массив для ключей, которые присутствуют в дереве
    auto *m = new INT_64[n];

//заполнение дерева и массива элементами с возрастающими чётными //ключами на интервале [0, 10000, 20000, ... ,10000*n]
    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        RandTree.addNode(m[i], 1);
    }
//    RandTree.printTree();
//    cout << endl;
//вывод размера дерева до теста
    cout << "items count:" << RandTree.getSize() << endl;
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
            RandTree.removeNode(k);
//            cout << "Remove with 10% (" << i << endl;
            D += RandTree.getViewNode();
            RandTree.addNode(m[rand() % n], 1);
//            cout << "Add with 10% (" << i << endl;
            I += RandTree.getViewNode();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2);    // случайный нечётный ключ
            try {
                RandTree.getData(k);
//                cout << "Get with 10% (" << i << endl;
                S += RandTree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += RandTree.getViewNode(); }
        } else  //90% успешных операций
        {
            int ind = rand() % n;
            RandTree.removeNode(m[ind]);
//            cout << "Remove with 90% (" << i << endl;
            D += RandTree.getViewNode();;
            int k = LineRand() % (10000 * n);
            k = k + k % 2;        // случайный чётный ключ
            RandTree.addNode(k, 1);
//            cout << "Add with 90% (" << i << endl;
            I += RandTree.getViewNode();;
            m[ind] = k;
            try {
                RandTree.getData(m[rand() % n]);
//                cout << "Get with (90% (" << i << endl;
                S += RandTree.getViewNode();;
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error e) { S += RandTree.getViewNode(); }
        }
    }
//    RandTree.printTree();
//    cout << endl;
//вывод результатов:
// вывод размера дерева после теста
    cout << "items count:" << RandTree.getSize() << endl;
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

void test_randRND(int n) {
    //создание дерева для 64 – разрядных ключей типа INT_64
    RNDTree<INT_64, int> RandTree;
    //массив для ключей, которые присутствуют в дереве
    auto *m = new INT_64[n];
//установка первого случайного числа
    sRand();
//заполнение дерева и массива элементами со случайными ключами
    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        RandTree.addNode(m[i], 1);
    }
//вывод размера дерева до теста
    cout << "items count:" << RandTree.getSize() << endl;
//обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
//генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)        //10% промахов
        {
            RandTree.removeNode(LineRand());
            D += RandTree.getViewNode();
            RandTree.addNode(m[rand() % n], 1);
            I += RandTree.getViewNode();
            try {
                RandTree.getData(LineRand());
                S += RandTree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += RandTree.getViewNode(); }
        } else  //90% успешных операций
        {
            int ind = rand() % n;
            RandTree.removeNode(m[ind]);
            D += RandTree.getViewNode();
            INT_64 key = LineRand();
            RandTree.addNode(key, 1);
            I += RandTree.getViewNode();
            m[ind] = key;
            try {
                RandTree.getData(m[rand() % n]);
                S += RandTree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += RandTree.getViewNode(); }
        }    //конец теста

//вывод результатов:
//вывод размера дерева после теста
    cout << "items count:" << RandTree.getSize() << endl;
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

void test_ordRND(int n) {
    //создание дерева для 64 – разрядных ключей типа INT_64
    RNDTree<INT_64, int> RandTree;
    //массив для ключей, которые присутствуют в дереве
    auto *m = new INT_64[n];

//заполнение дерева и массива элементами с возрастающими чётными //ключами на интервале [0, 10000, 20000, ... ,10000*n]
    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        RandTree.addNode(m[i], 1);
    }
//вывод размера дерева до теста
    cout << "items count:" << RandTree.getSize() << endl;
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
            RandTree.removeNode(k);
            D += RandTree.getViewNode();
            RandTree.addNode(m[rand() % n], 1);
            I += RandTree.getViewNode();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2);    // случайный нечётный ключ
            try {
                RandTree.getData(k);
                S += RandTree.getViewNode();
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error) { S += RandTree.getViewNode(); }
        } else  //90% успешных операций
        {
            int ind = rand() % n;
            RandTree.removeNode(m[ind]);
            D += RandTree.getViewNode();;
            int k = LineRand() % (10000 * n);
            k = k + k % 2;        // случайный чётный ключ
            RandTree.addNode(k, 1);
            I += RandTree.getViewNode();;
            m[ind] = k;
            try {
                RandTree.getData(m[rand() % n]);
                S += RandTree.getViewNode();;
            }
                //обработка исключения при ошибке операции поиска
            catch (runtime_error e) { S += RandTree.getViewNode(); }
        }
    }
//вывод результатов:
// вывод размера дерева после теста
    cout << "items count:" << RandTree.getSize() << endl;
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
    RNDTree<TYPE, TYPE> RandTree;
    Tree<>::Iterator iterator(&RandTree);
    Tree<>::Iterator iterator1(&RandTree);
    Tree<>::Reverse_Iterator reverseIterator(&RandTree);
    Tree<>::Reverse_Iterator reverseIterator1(&RandTree);
    bool Flag = true;
    while (Flag) {
        cout << "______________ Menu ________________\n"
                "1.  Output the size of RandTree      |\n"
                "2.  Cleaning a RandTree              |\n"
                "3.  Is RandTree empty?               |\n"
                "4.  Get element by key               |\n"
                "5.  Set element by key               |\n"
                "6.  Push element by key              |\n"
                "7.  Remove element by key            |\n"
                "8.  Request begin for iterator       |\n"
                "9.  Request rbegin for iterator      |\n"
                "10. Request end for iterator         |\n"
                "11. Request rend for iterator        |\n"
                "12. Functions of iterator            |\n"
                "13. Print a RandTree                 |\n"
                "14. Print a keys of RandTree         |\n"
                "15. Poryadkoviy number by key        |\n"
                "16. Test rand                        |\n"
                "17. Test ord                         |\n"
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
                cout << RandTree.getSize() << endl;
                break;
            }
            case 2: {
                ClearConsole();
                RandTree.clear();
                break;
            }
            case 3: {
                ClearConsole();
                cout << "####### ACTION #######\n";
                cout << boolalpha << RandTree.isEmpty() << endl;
                break;
            }
            case 4: {
                ClearConsole();
                cout << "Input the key: ";
                int key;
                cin >> key;
                cout << "####### ACTION #######\n";
                try {
                    cout << RandTree.getData(key) << endl;
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
                cout << boolalpha << RandTree.setNode(key, value) << endl;
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
                cout << boolalpha << RandTree.addNode(key, value) << endl;
                break;
            }
            case 7: {
                ClearConsole();
                cout << "Input the key: ";
                TYPE key;
                cin >> key;
                cout << "####### ACTION #######\n";
                cout << boolalpha << RandTree.removeNode(key) << endl;
                break;
            }
            case 8: {
                ClearConsole();
                try {
                    iterator = RandTree.begin();
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }

                break;
            }
            case 10: {
                ClearConsole();
                try {
                    iterator = RandTree.end();
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            }

            case 9: {
                ClearConsole();
                try {
                    reverseIterator = RandTree.rbegin();
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }

                break;
            }
            case 11: {
                ClearConsole();
                try {
                    reverseIterator = RandTree.rend();
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
                            "1. Init a second iterator   |\n"
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
                                cout << "Choose iterator: direct(1) or reverse(2)? (1/2)\n";
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
                                                iterator1 = RandTree.begin();
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                iterator1 = RandTree.end();
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
                                                reverseIterator1 = RandTree.rbegin();
                                            } catch (runtime_error error) {
                                                cout << error.what() << endl;
                                            }
                                            flag = false;
                                            f = false;
                                        } else if (in == 2) {
                                            try {
                                                reverseIterator1 = RandTree.rend();
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
                                cout << "Choose iterator: direct(1) or reverse(2)? (1/2)\n";
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
                                cout << "Choose iterator: direct(1) or reverse(2)? (1/2)\n";
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
                                cout << "Choose iterator: direct(1) or reverse(2)? (1/2)\n";
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
                                cout << "Choose iterator: direct(1) or reverse(2)? (1/2)\n";
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
                                cout << "Choose iterator: direct(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    cout << "####### ACTION #######\n";
                                    try {
                                        cout << boolalpha << (iterator == iterator1) << endl;
                                    } catch (runtime_error error) {
                                        cout << error.what() << endl;
                                    }
                                    f = false;
                                } else if (in == 2) {
                                    cout << "####### ACTION #######\n";
                                    try {
                                        cout << boolalpha << (reverseIterator == reverseIterator1) << endl;
                                    } catch (runtime_error error) {
                                        cout << error.what() << endl;
                                    }
                                    f = false;
                                } else cout << "Incorrect input! Please repeat...\n";
                            }
                            break;
                        }
                        case 7: {
                            ClearConsole();
                            bool f = true;
                            while (f) {
                                cout << "Choose iterator: direct(1) or reverse(2)? (1/2)\n";
                                int in;
                                cin >> in;
                                if (in == 1) {
                                    cout << "####### ACTION #######\n";
                                    try {
                                        cout << boolalpha << (iterator != iterator1) << endl;
                                    } catch (runtime_error error) {
                                        cout << error.what() << endl;
                                    }
                                    f = false;
                                } else if (in == 2) {
                                    cout << "####### ACTION #######\n";
                                    try {
                                        cout << boolalpha << (reverseIterator != reverseIterator1) << endl;
                                    } catch (runtime_error error) {
                                        cout << error.what() << endl;
                                    }
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
            case 13: {
                ClearConsole();
                RandTree.printTree();
                cout << endl;
                break;
            }
            case 14: {
                ClearConsole();
                RandTree.printKeys();
                cout << endl;
                break;
            }
            case 15: {
                ClearConsole();
                cout << "Input the key: ";
                int key;
                cin >> key;
                cout << "####### ACTION #######\n";
                try {
                    cout << RandTree.getIndexByKey(key) << endl;
                } catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            }
            case 16: {
                ClearConsole();
                cout << "Input the count of elements: ";
                int count;
                cin >> count;
                try {
                    cout << "Test rand for BST:\n";
                    test_rand(count);
                    cout << "\nTest rand for RND_Tree:\n";
                    test_randRND(count);
                } catch (exception e) {}
                break;
            }
            case 17: {
                ClearConsole();
                cout << "Input the count of elements: ";
                int count;
                cin >> count;
                try {
                    cout << "Test ord for BST:\n";
                    test_ord(count);
                    cout << "\nTest ord for RND_Tree:\n";
                    test_ordRND(count);
                } catch (exception e) {}
                break;
            }
            case 777: {
                srand(time(0));
                for (int i = 0; i < 10; ++i) {
                    RandTree.addNode(rand() % 101 + 1, rand() % 101 + 1);
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
