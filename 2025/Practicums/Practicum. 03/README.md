# Задача 1. 
Да се напише програма, която чете матрица от текстов файл от вида : 3,3,3|1,1,3|3,3,1, чете друга матрица в същия формат от втория файл и записва произведението им в нов файл (броят на колоните винаги е 3).

# Задача 2.  
Да се напише структура, която съхранява информация за доставка на пица. Да се създаде масив от доставки - списък с поръчки. Една поръчка съдържа име на клиента (до 50 символа), телефонен номер (до 20 символа), адрес на потребителя(до 100 символа), общата стойност на доставката и броят пици. Структурата на пицата трябва да съдъжа типа на пицата { Маргарита, калцоне, бурата и каквато още пожелаете}, размер на пицата {S,M,L}, цена на пицата. Да се имплементират функции, които позволяват съхраняването и изчитането на информацията за поръчките от двоичен файл. Да се сортират поръчките в масива по адрес на доставка и да се запише в нов двоичен файл.

# Задача 3. 
Да се създаде структура Jedi със следните характеристики:

* Име (максимална дължина 50 символа)
* Възраст
* Сила
* LightSaber
Всеки лазер да се опише със следните полета:

* Цвят - RED, YELLOW, GREEN, BLUE, PURPLE
* Тип - SINGLEBLADED, DOUBLE_BLADED, CROSSGUARD

Да се напише структура JediCollection, която да може да пази в себе си най-много 100 джедая и техния брой. Да се реализира следния набор от функции:

* Jedi createJedi(const char* name, unsigned age, unsigned power, const LightSaber& saber) – създава нов джедай с подадените параметри. Да се реализира overload, приемащ създаден цвят и тип на лазер
* void addJedi(JediCollection& collection, const Jedi& jedi) – добавя джедай в подадената колекция
* void removeJedi(JediCollection& collection, const char* name) – премахва джедая с подаденото име от колекцията
* void printJediCollection(const JediCollection& collection) – принтира подадената колекция
* void saveCollectionToBinary(const char* fileName, const JediCollection& collection) – запазва колекцията в подадения двоичен файл
* JediCollection readCollectionFromBinary(const char* fileName) – прочита и създава колекция, записана в двоичен файл
* void saveCollectionToTxt(const char* fileName, const JediCollection& collection) – запазва колекцията в подадения текстов файл
* JediCollection readCollectionFromTxt(const char* fileName) – прочита и създава колекция, записана в текстов файл
* void sortByAge(JediCollection& collection) – сортира колекция във възходящ ред по възраст
* void sortByPower(JediCollection& collection) – сортира колекция във възходящ ред по сила
* Color mostPopularSaberColor(const JediCollection& collection) – връща най-използвания цвят на лазер от джедаите в колекцията
* Type mostPopularSaberType(const JediCollection& collection) – връща най-използвания тип на лазер от джедаите в колекцията
