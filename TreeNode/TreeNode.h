// TreeNode.h

#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>


// Шаблонный класс TypereeNode для представления узла бинарного дерева

template <typename T>
class TreeNode {
public:
    T value;              // Значение узла
    TreeNode* left;       // Указатель на левый дочерний узел
    TreeNode* right;      // Указатель на правый дочерний узел

    // Конструктор для инициализации узла
    // val - значение, присваиваемое узлу
    // left и right инициализируются как nullptr
    // Рекомендуется добавить проверку или выброс исключения для недопустимых значений, если это применимо
    TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}

    // Деструктор
    ~TreeNode() {  }

    // Конструктор копирования
    // Создает глубокую копию другого узла
    // other - узел, из которого создается копия
    TreeNode(const TreeNode& other) : value(other.value), left(nullptr), right(nullptr) {
        // Если у другого узла есть левое поддерево, копируем его
        if (other.left) {
            left = new TreeNode(*other.left);  // Копируем левый узел
        }
        // Если у другого узла есть правое поддерево, копируем его
        if (other.right) {
            right = new TreeNode(*other.right);  // Копируем правый узел
        }
    }

    // Оператор присваивания копированием
    // other - узел, данные которого нужно скопировать в текущий узел
     TreeNode& operator=(const TreeNode& other) {
        if (this == &other) {
            return *this;  // Проверка на самоприсваивание
        }

        delete left;  // Удаляем левое поддерево
        delete right;  // Удаляем правое поддерево
        left = nullptr;
        right = nullptr;

        value = other.value;  // Копируем значение

        // Копируем левое поддерево, если оно есть
        if (other.left) {
            left = new TreeNode(*other.left);
        }
        // Копируем правое поддерево, если оно есть
        if (other.right) {
            right = new TreeNode(*other.right);
        }

        return *this;  // Возвращаем ссылку на текущий объект для цепочки присваиваний
    }

     // Конструктор перемещения
     // other - узел, из которого переносится управление
     TreeNode(TreeNode&& other) noexcept : value(other.value), left(other.left), right(other.right) {
         other.left = nullptr;  // Обнуляем указатель на левое поддерево у источника
         other.right = nullptr;  // Обнуляем указатель на правое поддерево у источника
     }

    // Очищает все дочерние узлы дерева
    void clear() {
        // Если есть левое поддерево, очищаем и удаляем его
        if (left) {
            left->clear();  // Рекурсивно очищаем левое поддерево
            delete left;  // Удаляем левый узел
            left = nullptr;  // Обнуляем указатель
        }
        // Если есть правое поддерево, очищаем и удаляем его
        if (right) {
            right->clear();  // Рекурсивно очищаем правое поддерево
            delete right;  // Удаляем правый узел
            right = nullptr;  // Обнуляем указатель
        }
    }
    // Функция копирования дерева
    // return копию
    TreeNode* copyTree() const {
        if (this == nullptr) return nullptr;
        TreeNode* newRoot = new TreeNode(value);
        if (left) newRoot->left = left->copyTree();
        if (right) newRoot->right = right->copyTree();
        return newRoot;
    }
};
// Функция сравнения двух деревьев (для тестирования)
template <typename T>
bool areTreesEqual(TreeNode<T>* a, TreeNode<T>* b) {
    if (!a && !b) return true;
    if (!a || !b || a->value != b->value) return false;
    return areTreesEqual(a->left, b->left) && areTreesEqual(a->right, b->right);
}
// Функция поиска узла в дереве
// Возвращает указатель на узел с заданным значением или nullptr, если узел не найден
// root - корень дерева, в котором производится поиск
// value - значение узла, которое нужно найти
TreeNode<int>* findNode(TreeNode<int>* root, int value) {
    if (root == nullptr || root->value == value) {
        return root;  // Если корень пустой или нашли узел с нужным значением
    }
    TreeNode<int>* leftResult = findNode(root->left, value);  // Рекурсивно ищем в левом поддереве
    if (leftResult) {
        return leftResult;  // Если нашли в левом поддереве, возвращаем результат
    }
    return findNode(root->right, value);  // Ищем в правом поддереве
}

// Функция вставки нового узла по указанному направлению
// parent - родительский узел, в который добавляется новый узел
// value - значение нового узла
// isLeft - флаг, указывающий, вставлять ли узел влево (true) или вправо (false)
void insertNode(TreeNode<int>*& parent, int value, bool isLeft) {
    if (parent == nullptr) {
        parent = new TreeNode<int>(value);  // Если родительский узел пустой, создаем новый узел
    }
    else {
        // Если нужно вставить влево
        if (isLeft) {
            if (parent->left == nullptr) {
                parent->left = new TreeNode<int>(value);  // Вставляем новый узел в левое поддерево
            }
            else {
                insertNode(parent->left, value, isLeft);  // Рекурсивно продолжаем в левом поддереве
            }
        }
        else {
            // Если нужно вставить вправо
            if (parent->right == nullptr) {
                parent->right = new TreeNode<int>(value);  // Вставляем новый узел в правое поддерево
            }
            else {
                insertNode(parent->right, value, isLeft);  // Рекурсивно продолжаем в правом поддереве
            }
        }
    }
}

// Остальные функции для работы с деревом

// Функция для удаления всех узлов дерева
// root - указатель на корень дерева, которое нужно удалить
template <typename T>
void deleteTree(TreeNode<T>*& root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

// Функция для отображения дерева в консоли
// root - корень дерева, которое нужно отобразить
// indent - отступ для текущего уровня (по умолчанию 0)
template <typename T>
void displayTree(TreeNode<T>* root, int indent = 0) {
    if (root != nullptr) {
        if (root->right) {
            displayTree(root->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (root->right) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << root->value << "\n ";
        if (root->left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            displayTree(root->left, indent + 4);
        }
    }
}
// Функция для вычисления глубины дерева
// node - указатель на текущий узел дерева, начиная с которого вычисляется глубина
template <typename T>
int calculateDepth(TreeNode<T>* node) {
    if (node == nullptr) {
        return -1;  // Если узел пустой, то дерево пустое, глубина -1
    }

    int leftDepth = calculateDepth(node->left);   // Глубина левого поддерева
    int rightDepth = calculateDepth(node->right); // Глубина правого поддерева

    return std::max(leftDepth, rightDepth) + 1; // Берем максимальную глубину и прибавляем 1 (текущий узел)
}
// Прямой обход дерева (NLR) - сначала текущий узел, потом левое и правое поддеревья
// node - указатель на текущий узел, с которого начинается обход
// result - вектор, в который будут добавляться значения узлов по мере обхода

template <typename T>
void NLR(TreeNode<T>* node, std::vector<T>& result) {
    if (node == nullptr) return;  // Если узел пустой, выходим
    result.push_back(node->value);  // Добавляем значение текущего узла в результат
    NLR(node->left, result);        // Рекурсивно идем в левое поддерево
    NLR(node->right, result);       // Рекурсивно идем в правое поддерево
}

// Симметричный обход дерева (LNR) - сначала левое поддерево, потом текущий узел, затем правое поддерево
// node - указатель на текущий узел, с которого начинается обход
// result - вектор, в который будут добавляться значения узлов по мере обхода
template <typename T>
void LNR(TreeNode<T>* node, std::vector<T>& result) {
    if (node == nullptr) return;  // Если узел пустой, выходим
    LNR(node->left, result);        // Рекурсивно идем в левое поддерево
    result.push_back(node->value);  // Добавляем значение текущего узла в результат
    LNR(node->right, result);       // Рекурсивно идем в правое поддерево
}

// Обратный обход дерева (LRN) - сначала левое поддерево, потом правое, потом текущий узел
// node - указатель на текущий узел, с которого начинается обход
// result - вектор, в который будут добавляться значения узлов по мере обхода
template <typename T>
void LRN(TreeNode<T>* node, std::vector<T>& result) {
    if (node == nullptr) return;  // Если узел пустой, выходим
    LRN(node->left, result);        // Рекурсивно идем в левое поддерево
    LRN(node->right, result);       // Рекурсивно идем в правое поддерево
    result.push_back(node->value);  // Добавляем значение текущего узла в результат
}

// Функция для применения произвольной функции к каждому узлу дерева
// node - текущий узел дерева, начиная с которого применяем функцию
// func - функция, которая применяется к каждому узлу
template <typename T, typename Func>
void applyFunction(TreeNode<T>* node, Func func) {
    if (node == nullptr) return;
    func(node);                      // Применяем функцию к текущему узлу
    applyFunction(node->left, func);  // Рекурсивно обходим левое поддерево
    applyFunction(node->right, func); // Рекурсивно обходим правое поддерево
}

// Функция для печати значений узлов дерева (обход NLR - прямой обход)
// node - текущий узел дерева, начиная с которого выполняется печать
template <typename T>
void printTree(TreeNode<T>* node) {
    if (node == nullptr) return;
    std::cout << node->value << " "; // Выводим значение текущего узла
    printTree(node->left);           // Рекурсивно обходим левое поддерево
    printTree(node->right);          // Рекурсивно обходим правое поддерево
}

// Функция для подсчёта количества узлов в дереве (обход NLR - прямой обход)
// node - текущий узел дерева, начиная с которого выполняется подсчёт
// Возвращает количество узлов в поддереве, включая сам узел
template <typename T>
int countNodes(TreeNode<T>* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right); // Подсчитываем текущий узел + левое + правое поддерево
}

// Класс для работы с бинарным деревом поиска
template <typename Type>
class BinarySearchTree {
private:
    TreeNode<Type>* root;  // Корень дерева

    // Рекурсивная вставка узла в дерево
    // node - текущий узел, в который происходит вставка
    // value - значение, которое нужно вставить
    // Возвращает указатель на текущий узел после вставки
    TreeNode<Type>* insertNode(TreeNode<Type>* node, const Type& value) {
        if (!node) return new TreeNode<Type>(value);  // Если узел пустой, создаем новый
        if (value < node->value)
            node->left = insertNode(node->left, value);  // Вставляем в левое поддерево
        else
            node->right = insertNode(node->right, value); // Вставляем в правое поддерево
        return node;  // Возвращаем текущий узел
    }
    // Рекурсивный поиск узла по значению
    // node - текущий узел, в котором происходит поиск
    // value - значение, которое нужно найти
    // Возвращает указатель на найденный узел или nullptr, если узел не найден
    TreeNode<Type>* findNode(TreeNode<Type>* node, const Type& value) const {
        if (!node || node->value == value) return node;  // Если узел найден или пустой
        return value < node->value ? findNode(node->left, value) : findNode(node->right, value);
    }

    // Рекурсивное удаление всех узлов дерева
    // node - текущий узел, который нужно удалить
    void deleteTree(TreeNode<Type>* node) {
        if (node) {
            deleteTree(node->left);   // Рекурсивно удаляем левое поддерево
            deleteTree(node->right);  // Рекурсивно удаляем правое поддерево
            delete node;  // Удаляем текущий узел
        }
    }
    //delete узла дерева remove*
    // todo: findNode
public:
    // Конструктор по умолчанию
    BinarySearchTree() : root(nullptr) {}

    // Конструктор с начальным значением корня
    // value - значение, которое будет присвоено корню
    BinarySearchTree(const Type& value) : root(new TreeNode<Type>(value)) {}

    // Деструктор: освобождает память
    ~BinarySearchTree() {
        deleteTree(root);  // Удаление всего дерева
    }

    // Возвращает указатель на корень дерева
    TreeNode<Type>* getRoot() const {
        return root;
    }

    // Вставляет узел с заданным значением в дерево
    // Сложность: O(log n) в среднем, O(n) в худшем случае (несбалансированное дерево)
    void insert(const Type& value) {
        root = insertNode(root, value);
    }
    // Рекурсивный поиск узла по значению
    // value - значение, которое нужно найти
    // Возвращает указатель на найденный узел или nullptr, если узел не найден
    TreeNode<Type>* findBST(const Type& value) const {
        if (!this || this->value == value) return this;  // Если узел найден или пустой
        return value < this->value ? findNode(this->left, value) : findNode(this->right, value);
    }

    // Находит узел с заданным значением, бросает исключение, если не найден
    // Сложность: O(n), т.к. выполняется полный симметричный обход
    TreeNode<Type>* getNodeByValue(const Type& key) const {
        std::vector<Type> result;
        LNR(root, result);  // Симметричный обход для поиска узла
        for (auto& value : result) {
            if (value == key) return root;
        }
        throw std::runtime_error("Узел с заданным значением не найден");
    }

    // Выводит дерево в консоль
    // Сложность: O(n) для полного обхода всех узлов
    void printTree() const {
        displayTree(root);
    }

    // todo: const 
    // Симметричный обход (LNR)
    // Сложность: O(n), посещаем каждый узел один раз
    std::vector<Type> inorder() const{
        std::vector<Type> result;
        LNR(root, result);
        return result;
    }

    // Прямой обход (NLR)
    // Сложность: O(n), посещаем каждый узел один раз
    std::vector<Type> preorder() const{
        std::vector<Type> result;
        NLR(root, result);
        return result;
    }

    // Обратный обход (LRN)
    // Сложность: O(n), посещаем каждый узел один раз
    std::vector<Type> postorder() const{
        std::vector<Type> result;
        LRN(root, result);
        return result;
    }

    // Печать узлов дерева в симметричном порядке (LNR)
    void printBypassInorderLNR() const{
        std::vector<Type> temp = inorder();
        std::cout << "<========== Симметричный обход LNR ==========>" << std::endl;
        for (const auto& val : temp) {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }

    // Печать узлов дерева в прямом порядке (NLR)
    void printBypassPreorderNRL() const{
        std::vector<Type> temp = preorder();
        std::cout << "<========== Прямой обход NLR ==========>" << std::endl;
        for (const auto& val : temp) {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }

    // Печать узлов дерева в обратном порядке (LRN)
    void printBypassPostorderRLN() const{
        std::vector<Type> temp = postorder();
        std::cout << "<========== Обратный обход RLN ==========>" << std::endl;
        for (const auto& val : temp) {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }

    // todo: size_t
    // Вычисление глубины дерева
    // Сложность: O(log n) в среднем, O(n) в худшем случае
    size_t getTreeDepth() const {
        return calculateDepth(root);
    }

    // Применяет функцию к каждому узлу дерева (симметрично)
    // Сложность: O(n), т.к. функция применяется ко всем узлам
    // Применяет функцию к каждому узлу дерева (симметрично)
    template <typename Type>
    void applyInorder(TreeNode<Type>* root, const std::function<void(Type&)>& func) {
        applyFunction(root, func);
    }

    // Копирование дерева
    // Сложность: O(n), так как происходит полный обход дерева
    BinarySearchTree copy() const{
        BinarySearchTree tree;
        std::vector<Type> result;
        LNR(root, result);  // Симметричный обход
        for (const auto& value : result) {
            tree.insert(value);
        }
        return tree;
    }

    // Подсчет количества узлов в дереве
    // Сложность: O(n), т.к. происходит полный обход всех узлов
    size_t getTreeNodesCount() const {
        return countNodes(root);
    }

    // Удаление всех узлов дерева
    // Сложность: O(n), посещаем каждый узел
    void deleteTreeNow() {
        deleteTree(root);
        root = nullptr;
    }
    //Ф-ция отображения дерева
    void displayBSTree(int indent = 0)
    {
        displayTree(root, indent);
    }
    //Ф-ция подсчета глубины
    size_t calculateDepthBST()
    {
        return calculateDepth(root);
    }
    // Рекурсивная функция для удаления узла с заданным значением
    // node - текущий узел, value - значение для удаления
    // Возвращает измененное поддерево после удаления
    TreeNode<Type>* removeNode(TreeNode<Type>* node, const Type& value) {
        if (!node) return nullptr;  // Базовый случай: узел не найден

        // Ищем узел для удаления
        if (value < node->value) {
            node->left = removeNode(node->left, value);  // Идем влево
        }
        else if (value > node->value) {
            node->right = removeNode(node->right, value);  // Идем вправо
        }
        else {
            // Узел найден. Обрабатываем три случая.

            // Случай 1: Узел без детей (лист)
            if (!node->left && !node->right) {
                delete node;
                return nullptr;  // Просто удаляем и возвращаем nullptr
            }

            // Случай 2: Узел с одним ребенком
            if (!node->left || !node->right) {
                TreeNode<Type>* child = node->left ? node->left : node->right;
                delete node;
                return child;  // Заменяем узел на его ребенка
            }

            // Случай 3: Узел с двумя детьми
            // Находим преемника (минимальный узел в правом поддереве)
            TreeNode<Type>* successor = node->right;
            while (successor->left) {
                successor = successor->left;
            }
            // Копируем значение преемника в текущий узел
            node->value = successor->value;
            // Рекурсивно удаляем дубликат преемника из правого поддерева
            node->right = removeNode(node->right, successor->value);
        }
        return node;  // Возвращаем измененный узел
    }
    // Удаляет узел с заданным значением.
    void remove(const Type& value) {
        root = removeNode(root, value);
    }
};
