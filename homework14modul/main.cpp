#include<iostream>
#include<string>
#include<functional>
#include "Trie.h"

using namespace std;

//функция для перехвата исключения
void safe_call(std::function <void()> func) {
	try {
		func();
	}
	catch (const string& exception) {
		cout << "Exception caught: " << exception << endl;
	}
}

//функция чистки экрана
void clearScreen() {
	cout << "\033[2J\033[H";
}

//функция паузы
void pause() {
	cout << "Нажмите Enter для продолжения...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
	setlocale(LC_ALL, "");
	Trie trie;
	trie.insert("cat");
	trie.insert("call");
	trie.insert("cult");
	trie.insert("run");
	trie.insert("rut");
	trie.insert("cal");

	char menuChoice = 'k';

	string word;
	string input; //переменная для перехвата первого символа из потока ввода

	while (menuChoice!='q' && menuChoice != 'Q') {
		cout << "Основное меню программы Словарь" << endl;
		cout << "----------------------------------" << endl;
		cout << "Введите префикс для поиска слова:" << endl;
		getline(cin, word);
		//вызов исключения если такого слова нет
		if (!word.empty()) {
			cout << "----------------------------------" << endl;
			cout << "Список слов с префиксом " << word << ":" << endl;
			safe_call([&]() {trie.searchPref(word); });
			pause();
		}
		else {
			cout << "Не был введен префикс. Просьба ввести повторно" << endl;
			pause();
			clearScreen();
			continue;
		}
		cout << "Для выхода из программы введите q.\nДля продолжения работы программы введите любой другой символ." << endl;
		getline(cin, input);
		//если символ введен то присваиваем переменной меню первый символ из потока ввода
		if (!input.empty()) {
			menuChoice = input[0];
		}
		clearScreen();
	}
}