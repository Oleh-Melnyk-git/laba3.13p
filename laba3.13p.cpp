#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// Структура Zodiac
struct Zodiac {
  string surname;
  string name;
  string sign;
  int birthday[3]; // день, місяць, рік
};

// Вузол префіксного дерева
struct TrieNode {
  map<char, TrieNode *> children;
  bool isEndOfWord;
  vector<Zodiac> people; // список людей, що відповідають цьому ключу

  TrieNode() { isEndOfWord = false; }
};

// Клас Trie
class Trie {
private:
  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }

  // Додавання елемента
  void insert(const string &key, const Zodiac &person) {
    TrieNode *node = root;
    for (char c : key) {
      if (node->children.find(c) == node->children.end()) {
        node->children[c] = new TrieNode();
      }
      node = node->children[c];
    }
    node->isEndOfWord = true;
    node->people.push_back(person);
  }

  // Пошук за ключем (прізвище)
  vector<Zodiac> search(const string &key) {
    TrieNode *node = root;
    for (char c : key) {
      if (node->children.find(c) == node->children.end()) {
        return {}; // не знайдено
      }
      node = node->children[c];
    }
    if (node->isEndOfWord) {
      return node->people;
    }
    return {};
  }

  // Вивід усіх елементів (рекурсивно)
  void displayAll(TrieNode *node, string prefix) {
    if (node->isEndOfWord) {
      for (const auto &person : node->people) {
        cout << "Прізвище: " << person.surname << ", Ім'я: " << person.name
             << ", Знак: " << person.sign
             << ", Дата нар.: " << person.birthday[0] << "."
             << person.birthday[1] << "." << person.birthday[2] << endl;
      }
    }
    for (auto &child : node->children) {
      displayAll(child.second, prefix + child.first);
    }
  }

  void displayAll() { displayAll(root, ""); }
};

// Тестування
int main() {
  Trie trie;

  Zodiac p1 = {"Іваненко", "Іван", "Овен", {12, 4, 2000}};
  Zodiac p2 = {"Петренко", "Петро", "Телець", {5, 5, 1999}};
  Zodiac p3 = {"Іваненко", "Марія", "Рак", {20, 7, 2001}};

  trie.insert(p1.surname, p1);
  trie.insert(p2.surname, p2);
  trie.insert(p3.surname, p3);

  cout << "=== Всі записи ===" << endl;
  trie.displayAll();

  cout << "\n=== Пошук за прізвищем 'Іваненко' ===" << endl;
  auto results = trie.search("Іваненко");
  if (!results.empty()) {
    for (const auto &person : results) {
      cout << person.surname << " " << person.name << " - " << person.sign
           << endl;
    }
  } else {
    cout << "Не знайдено!" << endl;
  }

  return 0;
}
