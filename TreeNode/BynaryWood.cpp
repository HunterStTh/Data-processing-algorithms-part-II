// main.cpp 
// Гаврилов Д.А.
#include <iostream>
#include "TreeNode.h"
#include <cassert>
using namespace std;

// Тестовая функция для вставки узлов
void testInsertNode() {
    TreeNode<int>* root = new TreeNode<int>(10);
    insertNode(root, 5, true);
    insertNode(root, 15, false);
    insertNode(root->left, 3, true);
    insertNode(root->left, 7, false);
    insertNode(root->right, 12, true);
    insertNode(root->right, 18, false);

    // Проверяем структуру дерева
    assert(root->value == 10);
    assert(root->left->value == 5);
    assert(root->right->value == 15);
    assert(root->left->left->value == 3);
    assert(root->left->right->value == 7);
    assert(root->right->left->value == 12);
    assert(root->right->right->value == 18);

    deleteTree(root); // Очищаем дерево после теста
    cout << "Все тесты testInsertNode пройдены\n";
}

// Тестовая функция для вставки узлов
void testFindBST() {
    BinarySearchTree<int> bst;  // Создаем бинарное дерево поиска для типа int

    // Вставляем значения в дерево
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(24);
    bst.insert(34);

    
}

// Функция для тестирования метода clear
void testClear() {
    // Создаем дерево
    TreeNode<int>* root = new TreeNode<int>(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(15);
    root->left->left = new TreeNode<int>(3);
    root->left->right = new TreeNode<int>(7);
    root->right->left = new TreeNode<int>(12);
    root->right->right = new TreeNode<int>(18);

    // Вызываем метод clear на корневом узле
    root->clear();

    // Проверяем, что дерево полностью очищено
    assert(root->left == nullptr);  // Левое поддерево должно быть nullptr
    assert(root->right == nullptr); // Правое поддерево должно быть nullptr

    // Повторный clear не должен ничего делать 
    root->clear();
    assert(root->left == nullptr);
    assert(root->right == nullptr);

    // Удаляем сам корень, так как дерево уже очищено
    delete root;

    std::cout << "Тест clear пройден!" << std::endl;
}

// Тестовая функция для удаления дерева
void testDeleteTree() {
    TreeNode<int>* root = new TreeNode<int>(10);
    insertNode(root, 5, true);
    insertNode(root, 15, false);

    deleteTree(root); // Удаляем дерево
    assert(root == nullptr);  // После удаления корень должен быть nullptr
    cout << "Все тесты testDeleteTree пройдены\n";
}//добавить удаленние из пустого дерева

// Тестовая функция для вычисления глубины дерева
void testCalculateDepth() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);  // Корневой узел
    insertNode(root, 5, true);   // Влево
    insertNode(root, 3, true);   // Влево
    // Проверяем глубину дерева
    assert(calculateDepth(root) == 2);  // Глубина должна быть 3 (Уровни: корень -> 5 -> 3)

    deleteTree(root); // Очищаем дерево после теста
    std::cout << "Все тесты testCalculateDepth пройдены\n";
}

// Тест функции прямого обхода (NLR)
void testNLR() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);  // Корневой узел
    insertNode(root, 5, true);   // Влево
    insertNode(root, 15, false); // Вправо
    insertNode(root, 3, true);   // Влево
    insertNode(root, 7, false);  // Вправо
   
    std::vector<int> result;
    NLR(root, result);
    // Ожидаемый результат: 10 5 3 15 7
  
    std::vector<int> expected = { 10, 5, 3, 15, 7 };
    assert(result == expected);

    std::cout << "Тест NLR пройден!" << std::endl;
}
// Тест функции симметричного обхода (LNR)
void testLNR() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);  // Корень
    insertNode(root, 5, true);   // Левый узел
    insertNode(root, 15, false); // Правый узел
    insertNode(root, 3, true);   // Левый подузел
    insertNode(root, 7, false);  // Правый подузел
        /* 
                        7
                    /
                15
            /
        10
            \
                5
                    \
                        3
        */
 
    std::vector<int> result;
    LNR(root, result); 

    // Ожидаемый результат: 3 5 10 15 7
    std::vector<int> expected = { 3, 5, 10, 15, 7 };
    assert(result == expected);

    std::cout << "Тест LNR прошел успешно!" << std::endl;
}

// Тест функции обратного обхода (LRN)
void testLRN() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);  // Корень
    insertNode(root, 5, true);   // Левый узел
    insertNode(root, 15, false); // Правый узел
    insertNode(root->right, 3, true);   // Левый подузел
    insertNode(root->right, 7, false);  // Правый подузел
    /*
        7
      /
    15
      \
        3
  /
 10
   \
    5
       */
    std::vector<int> result;
    LRN(root, result);
    

    // Ожидаемый результат: 5, 3, 7, 15, 10
    std::vector<int> expected = { 5, 3, 7, 15, 10 };
    assert(result == expected);

    std::cout << "Тест LRN прошел успешно!" << std::endl;
}

// Тест функции подсчета узлов
void testCountNodes() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);  // Корень
    insertNode(root, 5, true);   // Левый узел
    insertNode(root, 15, false); // Правый узел
    insertNode(root, 3, true);   // Левый подузел
    insertNode(root, 7, false);  // Правый подузел

    int count = countNodes(root);

    // Ожидаемый результат: 5 узлов
    assert(count == 5);

    std::cout << "Тест подсчета узлов прошел успешно!" << std::endl;
}

// Тест функции печати дерева
void testPrintTree() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);  // Корень
    insertNode(root, 5, true);   // Левый узел
    insertNode(root, 15, false); // Правый узел
    insertNode(root, 3, true);   // Левый подузел
    insertNode(root, 7, false);  // Правый подузел

    std::cout << "Дерево: ";
    printTree(root);  // Ожидаемый вывод: 10 5 3 7 15
    std::cout << "\nОжидаемый вывод: 10 5 3 7 15\n";
}

// Функция для печати значения узла
void printNode(TreeNode<int>* node) {
    std::cout << node->value << " ";
}

// Тест функции applyFunction: вывод значений дерева
void testApplyFunction_PrintTree() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);  // Корень
    insertNode(root, 5, true);   // Левый узел
    insertNode(root, 15, false); // Правый узел
    insertNode(root, 3, true);   // Левый подузел
    insertNode(root, 7, false);  // Правый подузел

    std::cout << "Вывод дерева: ";
    applyFunction(root, printNode);
    std::cout << "\nОжидаемый вывод: 10 5 3 7 15\n";

    deleteTree(root);
}

// Функция для увеличения значения узла на 1
void incrementNodeValue(TreeNode<int>* node) {
    node->value += 1;
}
// Тест функции applyFunction: увеличение значений
void testApplyFunction_IncrementValues() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);
    insertNode(root, 5, true);
    insertNode(root, 15, false);

    applyFunction(root, incrementNodeValue);

    std::cout << "После увеличения: ";
    applyFunction(root, printNode);
    std::cout << "\nОжидаемый вывод: 11 6 16\n";
    // Тест с пустым деревом
    root = nullptr;
    applyFunction(root, incrementNodeValue); // Не должно быть ошибок
    std::cout << "Тест с пустым дерева пройден.\n";

    // Тест с отрицательными значениями
    insertNode(root, -10, true);
    insertNode(root, -5, true);
    insertNode(root, -15, false);

    applyFunction(root, incrementNodeValue);
    deleteTree(root);
}

// Функция для суммирования значений узлов
void sumNodeValues(TreeNode<int>* node, int& sum) {
    sum += node->value;
}

// Тест функции applyFunction: подсчёт суммы узлов
void testApplyFunction_SumValues() {
    TreeNode<int>* root = nullptr;
    insertNode(root, 10, true);
    insertNode(root, 5, true);
    insertNode(root, 15, false);

    int sum = 0;
    applyFunction(root, [&](TreeNode<int>* node) { sumNodeValues(node, sum); });

    std::cout << "Сумма значений: " << sum << "\n";
    std::cout << "Ожидаемый вывод: 30\n";

    deleteTree(root);
}
// Тестирование копирования дерева
void testCopyTree() {
    // Тест 1: Копирование пустого дерева
    TreeNode<int>* emptyTree = nullptr;
    TreeNode<int>* copiedEmptyTree = (emptyTree ? emptyTree->copyTree() : nullptr);
    assert(copiedEmptyTree == nullptr);
    std::cout << "Пустое дерево работает.\n";

    // Тест 2: Копирование дерева с одним узлом
    TreeNode<int>* singleNodeTree = new TreeNode<int>(42);
    TreeNode<int>* copiedSingleNodeTree = singleNodeTree->copyTree();
    assert(copiedSingleNodeTree != nullptr && copiedSingleNodeTree->value == 42);
    delete singleNodeTree;
    delete copiedSingleNodeTree;
    std::cout << "одиночное дерево работает.\n";

    // Тест 3: Копирование дерева с несколькими уровнями
    TreeNode<int>* root = new TreeNode<int>(10);
    insertNode(root, 5, true);
    insertNode(root, 15, false);
    insertNode(root, 2, true);
    insertNode(root, 7, false);
    insertNode(root, 12, true);
    insertNode(root, 18, false);


    TreeNode<int>* copiedTree = root->copyTree();
    assert(areTreesEqual(root, copiedTree)); // Деревья должны быть равны

    std::cout << "большое дерево работает пройден.\n";

    // Тест 4: Проверка независимости копии (изменение оригинала не влияет на копию)
    root->left->value = 100; // Меняем оригинал
    assert(copiedTree->left->value == 5); // Копия не должна измениться

    std::cout << "тест на глубокость копии пройден.\n";

    delete root;
    delete copiedTree;
}
void testRemove() {
    //  Удаление листа.
    {
        BinarySearchTree<int> bst;
        bst.insert(5);
        bst.insert(3);
        bst.insert(7);
        bst.remove(3); // Удаляем лист 3.

        std::vector<int> inorder = bst.inorder();
        assert((inorder == std::vector<int>{5, 7}));
    }

    // Удаление узла с одним ребенком.
    {
        BinarySearchTree<int> bst;
        bst.insert(5);
        bst.insert(3);
        bst.insert(4); // Узел 3 имеет правого ребенка 4.
        bst.remove(3); // Заменяем 3 на 4.

        std::vector<int> inorder = bst.inorder();
        assert((inorder == std::vector<int>{4, 5}));
    }

    //Удаление узла с двумя детьми.
    {
        BinarySearchTree<int> bst;
        bst.insert(5);
        bst.insert(3);
        bst.insert(2);
        bst.insert(4);
        bst.insert(7);
        bst.insert(6);
        bst.insert(8);
        bst.remove(5); // Заменяем корень на преемника (6).

        std::vector<int> inorder = bst.inorder();
        assert((inorder == std::vector<int>{2, 3, 4, 6, 7, 8}));
    }

    //  Удаление корня (дерево из одного узла).
    {
        BinarySearchTree<int> bst;
        bst.insert(10);
        bst.remove(10);
        assert(bst.getRoot() == nullptr);
    }

    //  Попытка удалить несуществующий узел.
    {
        BinarySearchTree<int> bst;
        bst.insert(5);
        bst.remove(100); // Ничего не происходит.
        std::vector<int> inorder = bst.inorder();
        assert((inorder == std::vector<int>{5}));
    }

    std::cout << "Все тесты remove пройдены!" << std::endl;
}

int main() {setlocale(LC_ALL, "Rus");
    testRemove();
    testCopyTree();
    testFindBST();
    testCalculateDepth();
    testClear();
    testCountNodes();
    testDeleteTree();
    testInsertNode();
    testLNR();
    testNLR();
    testLRN();
    testApplyFunction_PrintTree();
    testApplyFunction_IncrementValues();
    testApplyFunction_SumValues();
    // Создаем бинарное дерево из  узлов не строгое не совершенное
    TreeNode<int>* root = nullptr;
    BinarySearchTree<int> bst;  // Создаем бинарное дерево поиска для типа int

    insertNode(root, 15, false); // Правый узел от корня
    insertNode(root, 5, true);    // Левый узел от корня
    insertNode(root->left, 7, false);  // Правый узел от узла 5
    insertNode(root->left, 9, true);    // Левый узел от узла 5
    insertNode(root->right, 17, false);// Правый узел от узла 15
    insertNode(root->right, 25, true); // Левый узел от узла 15
    insertNode(root->right->left, 25, true); // Левый узел от узла 15
    insertNode(root->right->left->left, 25, true); // Левый узел от узла 15

    // Вставляем значения в дерево
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(24);
    bst.insert(34);
    // Отображаем дерево
    cout << " Не бинарное дерево:\n";
    displayTree(root);
    cout << " Глубина: "<<calculateDepth(root)<<endl<<endl;

    cout << " Бинарное дерево:\n";
    bst.displayBSTree();
    cout << " Глубина: " << bst.calculateDepthBST();
    
    
    // Удаляем дерево
    deleteTree(root);

    return 0;
}
