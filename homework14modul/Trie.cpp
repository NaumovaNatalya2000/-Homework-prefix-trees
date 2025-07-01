#include "Trie.h"

//конструктор по умолчанию - создаем корень дерева
Trie::Trie()
{
   root = getNewNode();
}

//создание ноды
Trie::TrieNode* Trie::getNewNode()
{
    //выделяем память под новый узел
   TrieNode* pNode = new TrieNode;

   //устанавливаем флаг конца слова в false
   pNode->isEndOfWord = false;

   //инициализируем детей nullptr
   for (int i{}; i < ALPHABET_SIZE; i++) {
      pNode->children[i] = nullptr;
   }
   return pNode;
}

//добавление ноды
void Trie::insert(std::string key)
{
   insert(root, key);
}
void Trie::insert(TrieNode* root, std::string key)
{
   TrieNode* currentNode = root;
   for (int i{}; i < key.size(); i++) {
      //если символ еще не был добавлен
      if (currentNode->children[key[i] - 'a'] == nullptr) {
         currentNode->children[key[i] - 'a'] = getNewNode();
         currentNode = currentNode->children[key[i] - 'a'];
      }
      //если символ уже был
      else {
         currentNode = currentNode->children[key[i] - 'a'];
      }
   }
   currentNode->isEndOfWord = true;
}

//поиск ноды
bool Trie::search(std::string key)
{
   return search(root, key);
}
bool Trie::search(TrieNode* root, std::string key)
{
   TrieNode* currentNode = root;
   for (int i{}; i < key.size(); i++) {
      int index = key[i] - 'a';
      if (!currentNode->children[index]) {
         return false;
      }
      currentNode = currentNode->children[index];
   }
   return (currentNode != nullptr && currentNode->isEndOfWord);
}

//проверка пусто ли дерево и является ли узел листом
bool Trie::isEmpty(TrieNode* root) {
   for (int i{}; i < ALPHABET_SIZE; i++) {
      if (root->children[i]) {
         return false;
      }
   }
   return true;
}

//удаление ноды
void Trie::remove(std::string key)
{
   root = remove(root, key);
}
Trie::TrieNode* Trie::remove(TrieNode* root, std::string key, int depth)
{
   //если дерево пустое
   if (!root) {
      return nullptr;
   }
   //если дошли до конца ключа
   if (depth == key.size()) {
      //этот узел уже больше не конец слова поэтому снимаем метку
      if (root->isEndOfWord) {
         root->isEndOfWord = false;
      }
      //если ключ не является префиксом удаляем его
      if (isEmpty(root)) {
         delete root;
         root = nullptr;
      }
      return root;
   }
   //Пока не дошли до конца ключа или определили,
   //что его нет в дереве, рекурсивно вызываем для ребенка
   //соответствующего символа
   int index = key[depth] - 'a';
   root->children[index] = remove(root->children[index], key, depth + 1);

   //если у корня нет дочернего слова
   //(удален только один его дочерний элемент),
   //и он не заканчивается другим словом
   if (isEmpty(root) && root->isEndOfWord == false) {
      delete root;
      root = nullptr;
   }
   //возвращаем новый корень
   return root;
}

//подсчет слов
int Trie::countWord()
{
   return countWord(root);
}
int Trie::countWord(TrieNode* root)
{
   TrieNode* node = root;
   if (node == nullptr) {
      return 0;
   }
   //счетчик слов
   int count = 0;
   if (node->isEndOfWord) {
      count = 1;
   }
   //рекурсивно добавляем к счетчику количество слов
   for (int i{}; i < ALPHABET_SIZE; i++) {
      if (node->children[i]) {
         count += countWord(node->children[i]);
      }
   }
   return count;
}

//поиск слов по префиксу
void Trie::searchPref(const std::string& key)
{
   TrieNode* currentNode = root; //переменная начальной точки поиска
   //присваиваем имеющееся значение в буфер сразу
   std::string buffer = key; //строка буфера

   //доходим сразу до последнего символа - узла
   for (int i{}; i < key.length(); i++) {
      //если один из символов последовательности не найден
      if (currentNode->children[key[i] - 'a'] == nullptr) {
         throw ("Слов с префиксом " + key + " не существует");
      }
      //перемещаем указатель на родитель - найденный символ
      currentNode = currentNode->children[key[i] - 'a'];
   }

   //вызываем функцию с уже заполненным буфером первой последовательностью символов
   //и перемещенным указателем
   searchPref(currentNode, buffer);
}
void Trie::searchPref(TrieNode* currentNode, std::string buffer)
{
   //если есть флаг конца слова
   if (currentNode->isEndOfWord) {
      //выводим найденное слово
      std::cout << buffer << std::endl;
   }

   //цикл рекурсии: если имеются дети у изначальной ноды - то переходим на них
   //в буфер добавляем символ
   for (int i{}; i < ALPHABET_SIZE; i++) {
      if (currentNode->children[i] != nullptr) {
         searchPref(currentNode->children[i], buffer + char(i + 'a'));
      }
   }
}