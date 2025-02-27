#include <iostream>
#include <vector>
#include <string>

struct PhoneRecord {
    std::string phoneNumber;
};

struct TreeNode {
    std::string name;
    std::vector<PhoneRecord> phones;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& name, const std::string& phone) 
        : name(name), left(nullptr), right(nullptr) {
        phones.push_back({phone});
    }
};

class PhoneBook {
private:
    TreeNode* root;

    // добавление записи через рекурсию
    TreeNode* addRecord(TreeNode* node, const std::string& name, const std::string& phone) {
        if (!node) {
            return new TreeNode(name, phone);
        }

        if (name < node->name) {
            node->left = addRecord(node->left, name, phone);
        } else if (name > node->name) {
            node->right = addRecord(node->right, name, phone);
        } else {
            // если имя совпадает, добавляем телефон к существующему узлу
            node->phones.push_back({phone});
        }

        return node;
    }

    // поиска записи через рекурсию
    TreeNode* findRecord(TreeNode* node, const std::string& name) {
        if (!node || node->name == name) {
            return node;
        }

        if (name < node->name) {
            return findRecord(node->left, name);
        } else {
            return findRecord(node->right, name);
        }
    }

    // удаление записи через рекурсию
    TreeNode* deleteRecord(TreeNode* node, const std::string& name) {
        if (!node) {
            return nullptr;
        }

        if (name < node->name) {
            node->left = deleteRecord(node->left, name);
        } else if (name > node->name) {
            node->right = deleteRecord(node->right, name);
        } else {
            // узел найден, удаляем его
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // узел с двумя дочерними узлами: находим минимальный узел в правом поддереве
            TreeNode* temp = node->right;
            while (temp && temp->left) {
                temp = temp->left;
            }

            // копируем данные минимального узла в текущий узел
            node->name = temp->name;
            node->phones = temp->phones;

            // удаляем минимальный узел в правом поддереве
            node->right = deleteRecord(node->right, temp->name);
        }

        return node;
    }

    // рекурсивно очищаем память
    void clearTree(TreeNode* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    PhoneBook() : root(nullptr) {}

    ~PhoneBook() {
        clearTree(root);
    }

    // добавление записи
    void add(const std::string& name, const std::string& phone) {
        root = addRecord(root, name, phone);
    }

    // поиск записи
    void find(const std::string& name) {
        TreeNode* node = findRecord(root, name);
        if (node) {
            std::cout << "phone for " << name << ":" << std::endl;
            for (const auto& phone : node->phones) {
                std::cout << phone.phoneNumber << std::endl;
            }
        } else {
            std::cout << "not found" << std::endl;
        }
    }

    // удаление записи
    void remove(const std::string& name) {
        root = deleteRecord(root, name);
    }
};

int main() {
    PhoneBook phoneBook;
    std::string command, name, phone;

    while (true) {
        std::cout << "enter command (add, find, remove, exit): ";
        std::cin >> command;
        std::cin.ignore();

        if (command == "add") {
            std::cout << "enter name: ";
            std::getline(std::cin, name);
            std::cout << "enter phone: ";
            std::getline(std::cin, phone);
            phoneBook.add(name, phone);
        } else if (command == "find") {
            std::cout << "enter name: ";
            std::getline(std::cin, name);
            phoneBook.find(name);
        } else if (command == "remove") {
            std::cout << "enter name: ";
            std::getline(std::cin, name);
            phoneBook.remove(name);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "unknown command" << std::endl;
        }
    }
}
