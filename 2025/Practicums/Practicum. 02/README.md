# Задача 1: 
Да се напише функция, която проверява колко пъти се среща даден символ във файл.

# Задача 2: 
От стандартния вход се прочитат три числа. Запишете във файл "result.txt" сумата и произведението им. Направете функция, която извежда на стандартния изход разликата на сумата и произведението, прочетени от файла "result.txt".

# Задача 3: 
Напишете програма, която чете масив от файл, като заделя точно толкова памет, колкото е нужна. След това да се сортира възходящо и низходящо, като двата резултата да се запишат в два отделни резултатни файла. ВНИМАНИЕ! Файлът може да е празен.

# Задача 4: 
Напишете структура FMIStudent, която в себе си има име с големина най-много 50, години, масив от оценки с големина най-много 100 и специалност. Специалностите могат да са SE, CS, IS, I. Вашата задача е да напишете функциите saveStudentToFile(const Student& s, std::ofstream& ofs), readStudentFromFile(Student& s, std::ifstream& ifs). Също така напишете и функциите writeStudentArrayToFile(const char* filename, const Student* students, size_t size) и readStudentArrayFromFile(const char* filename, size_t& size).

# Задача 5: 
За тази задача използвайте структурите, които написахме предния път - Point, Triangle. Напишете програма, която чете масив от точки от стандартния вход, след което го записва във файл. След като точките са записани във файла, трябва да прочетете същия файл, интерпретиран като масив от триъгълници. Ако броят точки не се дели точно на 3, прочетете толкова триъгълници за колкото стигат точките.

# Задача 6: 
Да се напише структура Vector, която да представлява вектор в тримерното евклидово пространство. Да се напише структура VectorSpace, която да съдържа в себе си най-много 50 вектора и техния брой. Да се реализират следните функции (помислете за подходящи типове на връщане и аргументи):

* makeVector()
* addToVectorSpace()
* serializeVector()
* deserializeVector()
* serializeVectorSpace()
* deserializeVectorSpace()

Бонус функционалности: сортиране по дължина, сортиране лексикографски, проверка за ЛЗ и ЛНЗ на вектори на позиция i и j, извеждане на всички възможни комбинации за база, скаларно, векторно, смесено произведение.

# Задача 7:
Да се напише функция, която приема като аргументи имената на два текстови файла. В първия файл са записани две цели числа. Да се запишат сбора и произведението им във втория файл.

# Задача 8:
Да се напише функция, която приема име на текстов файл. Във файла има записани най-много 20 цели числа. В два файла ("even.txt", "odd.txt") да се запишат четните и нечетните числа.

# Задача 9:
Да се създаде структура Device, която се описва със следните характеристики:

* име на устройството (до 32 символа);
* количество в наличност (цяло число);
* цена на устройството (дробно число);
* вид на устройството - TV, SMARTPHONE, LAPTOP, PC, CAMERA;
* доставчик на устройството (до 32 символа).
  
Да се създаде структура Warehouse, в която да могат да се съхраняват най-много 100 устройства. В структурата да се съхранява и името на собственика на склада (до 32 символа).

Да се реализират следните функции:

* Създаване на устройство
* Създаване на склад
* Добавяне на устройство в склад
* Сериализация на склад
* Десериализация на склад
* Записване на всички продукти от даден вид в текстов файл
* Извеждане на информация за склад на стандартния изход
* Сортиране на устройствата в склад във възходящ/низходящ ред по цена
* Сортиране на устройствата в склад във възходящ/низходящ ред по наличност
* Намиране на най-скъпото/най-евтиното устройство в склад

# Задача 10
Да се напише програма, която сравнява два текстови файла и връща номера на първия ред, в който имат разлика.

# Задача 11
Да се напише програма, която по зададени две имена на файлове, конкатенира съдържанието им в трети файл.След това всички интервали да бъдат заменени с ,.

# Задача 12
Напишете програма, която прочита текстов файл, заменя всяко срещане на дадена дума с нова дума и записва резултата в нов файл.

# Задача 13
Създайте структура City, която описва град и има име (до 63 символа) и брой жители. Създайте и структура District, която съдържа в себе си до 20 града и пази текущия си размер.

* Напишете функция, която записва във файл една област.
* Напишете друга функция, която прочита област от файл, след което сортира градовете в областта според броя на жителите им във възходящ ред и записва резултата в друг файл.

# Задача 14
В практиката често се налага да се направи копие на текстов файл, като определени шаблони в текста са заменени с конкретни стойности.
Да се напише програма за работа с шаблони (placeholders) в текстов файл.
Програмата трябва да прочете даден файл и да направи копие, в което шаблоните са заменени с конкретни стойности.

# Задача 15
Реализирайте структура User, която да съдържа име, имейл и парола на даден потребител. Всяко поле е с максимална дължина 128 символа. Създайте възможност за записване и четене на потребител в текстов файл. Реализирайте структура System, която има масив от User-и. Системата поддържа максимално 100 потребители. Създайте методи за запазване и прочитане на обект от тип System от файл. (Помислете за подходящ формат за записването на данните). Имплементирайте проста login система, която поддържа възможност за регистриране на нов потребител и вход в системата. След спиране на програмата и повторно пускане, трябва да се запази възможността вече регистрирани потребители да влизат в системата с имейла и паролата си.

# Задача 16
Всички сме чували за информационната система на IMF - ZUZI. Имплементирайте модул от ZUZI, който трябва да се грижи за обработката и съхраняването на информация за избираемите дисциплини. Една избираема дисциплина трябва да съдържа следната информация:

* ID
* Име
* Категория - {OKN, M, PM, PR, Other}
* Брой кредити, които носи.
* Вид на изпита - { Exam, Course Project, Test }

Обърнете внимание, че изпитът на една дисциплина може да бъде и съчетание от горните три.
От конзолата да се приема път към файл, в който ще се записват данните. Важно условие е форматът на файла да бъде CSV. Първият ред трябва да съдържа заглавните полета (атрибути). За CSV (comma-separated values) формата може да прочетете повече тук: https://en.wikipedia.org/wiki/Comma-separated_values.Модулът трябва да покрива минимално следните изисквания:

* Данните да могат да се съхраняват в подходящ файл.
* Данните да могат да се зареждат от подходящ файл.
* Да може да се добавя избираема дисциплина.
* Ако подаденото ID на дисциплина вече е заето, то да се презаписва информацията за старата дисциплина.
* Да може да се премахва избираема дисциплина по ID.
* Възможност за извършване на следните справки:
* Търсене на избираема дисциплина по ID и отпечатване.
* Да се извеждат всички избираеми дисциплини по селектирана категория.
* Да се извеждат всички избираеми дисциплини по даден затворен интервал [minC, maxC], където minC e минимален брой кредити, а maxC е максимален брой кредити, които избираемата носи.
* Да се направи потребиталски интерфейс за работа през конзолата. Създаденият "CLI" да се зарежда от файл.
