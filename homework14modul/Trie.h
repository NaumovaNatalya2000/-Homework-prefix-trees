#pragma once
#include<iostream>
#define ALPHABET_SIZE 26

class Trie
{
private:
	struct TrieNode {
		//массив указателей символов алфавита
		TrieNode* children[ALPHABET_SIZE];
		bool isEndOfWord; //true - если конец слова
	};
public:
	//конструктор по умолчанию
	Trie();

	//обертка добавление ноды
	void insert(std::string key);
	
	//обертка поиск ноды
	bool search(std::string key);

	//обертка удаление
	void remove(std::string key);

	//обертка количество слов
	int countWord();

	//обертка поиск слов по префиксу
	void searchPref(const std::string& key);

private:

	TrieNode* root;

	//создание ноды
	TrieNode* getNewNode();

	//основная добавление ноды
	void insert(TrieNode* root, std::string key);

	//основная поиск ноды
	bool search(TrieNode* root, std::string key);

	//подсчет слов
	int countWord(TrieNode* root);

	//проверка пусто ли дерево и является ли узел листом
	bool isEmpty(TrieNode* root);

	//основная удаление ноды
	TrieNode* remove(TrieNode* root, std::string key, int depth = 0);

	//основная поиск слов по префиксу
	void searchPref(TrieNode* currentNode, std::string buffer);
};

