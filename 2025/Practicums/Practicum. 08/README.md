# Задача 1: 
Да се напише клас ComplexNumber. Класът ви трябва да има следните функционалности:

* Събиране, изваждане, умножение и деление на две комплексни числа. (+=, +, ….)
* Прочитане и записване на комплексно число.
* Напишете оператор ~, който ще използваме, за да намерим комплексно спрегнатото на дадено число.
* Сравняване на две комплексни числа. (Ще сравняваме две комплексни числа, като първият критерии ще ни е реалната част. Ако те са равни гледаме имагинерната.)

# Задача 2: 
Да се реализира клас дроб. Той трябва да поддържа следните функционалности:

* Събиране, изваждане, умножение и деление на дроби.
* Записване и прочитане на дроб.
* Оператор ~, който връща реципрочната дроб.
* Функция, която опростява дробта.
* Оператори за сравняване на дроби.
* Унарен минус, който връща отрицателната дроб, съответстваща на нашата.
* Оператори ++ и -- , които ще прибавят/вадят единица към дробта.

# Задача 3: 
Да се реализира клас Matrix. Той трябва да поддържа следните функционалности:

* Събиране, изваждане, умножение. Ако операциите не са възможни да се върне копие на обекта, от който е извикан оператора.
* Прочитане и запазване на матрица.
* Предефинирайте префиксен оператор +, който намира сумата на всички елементи в матрицата.
* Оператор bool, който връща дали дадена матрица е особена (нулева). Ако се извика от матрица, чиято детерминанта не може да се пресметне, да се върне false.

# Задача 4: 
Да се реализира клас Polynom от неизвестна степен. Той трябва да поддържа следните функционалности:

* Оператори за събиране, изваждане и умножение на два полинома.
* Оператор ~, който връща нов полином - производната на полинома, от който е извикан оператора.
* Оператори за четене и записване.
* Оператор (), който пресмята стойността на полинома с даден аргумент.
* Оператор [], който връща коефициента на полинома пред някоя степен. (Трябва да се предефинира за константен и за неконстантен достъп.)
* Оператори за сравнение на два полинома. Сравняваме ги лексикографски.
* Оператор унарен минус, който връща обратния вариант на полинома.

# Задача 5: 
Създайте клас Accommodation, който описва място за престой. Класът да съдържа следните полета:

* уникален номер (id) за всяко място
* име с произволна дължина
* тип: Apartment, Hotel, Villa,
* локация: точка с координати (x;y)
* цена за нощувка
* булев флаг, показващ дали мястото е запазено
* дни престой

Създайте следните функции:

* Подходящи гетъри и сетъри
* Функции за запазване и премахване на резервация
* Функция, която връща общата сума за дните престой. Функцията да връща нула при липса на резервация
* Създайте клас AirBnb, който съдържа самооразмеряващ се масив с места за престой.

Да се напишат следните член функции:

* Функция за добавяне на ново място за престой
* Функция, която приема id и дни и резервира мястото с подаденото id за дадения период от дни. При невалидно id да се хвърля подходящо изключение
* Функция, която приема id и отменя текущата резервация за съответното място, ако има такава. При невалидно id да се хвърля подходящо изключение
* Функция, която връща приходите от текущите резервации
* Функция, която връща приходите от всички направени до момента резервации
* Функция, която приема локация, и връща най-близкото място до дадените координати
* Функция, която премахва място за престой по подадено id. Да се хвърля подходящо изключение при невалидно id или при наличние на резервация
Реализрайте програма, с която да се изпробват всички функционалности на AirBnb класа. Да се извършва коректна обработка на изключенията.

# Задача 6:
Създайте клас Computer, съдържащ следните полета:

* serial number - полето се генерира автоматично с последователни числа за всеки нов обект от класа.
* brand (символен низ с произволна дължина)
* processor (символен низ с произволна дължина)
* video (цяло число)
* hard drive (цяло число)
* weight (цяло число)
* battery life (цяло число)
* price (дробно число)
* quantity (цяло число)
С изключение на количеството, не искаме да променяме член-данните след създаването на обект.

Създайте клас ComputerStore, съдържащ следните полета:

* name (символен низ с произволна дължина)
* списък с компютри
* Създайте конструктор, който приема име на магазина.

Създайте следните методи:

* Добавяне на компютър - ако вече има компютър от съответната марка, увеличава количеството, ако няма, го добавя в списъка
* Принтиране на списъка с компютри
* Покупка на компютър - приема brand и пари на купувача. Ако купувачът има достатъчно пари спрямо цената и има достатъчно количество от съответния компютър, осъществява успешна покупка и намалява количеството. В противен случай хвърля подходящо изключение.
метод, който принтира всички компютри с наличност, по-голяма от 0 - с опция да филтрира компютри, подходящи за пътуване или такива за игри (за определянето използвайте методите от следващия абзац).
* Създайте utility class (клас, съдържащ само статични методи) ConsultantUtils с два метода:

* isGoodForGaming - приема обект от клас Computer и връща true, ако процесорът е i5 или i7, видеото е 3060, 3070, 3080, 3090 и хард дискът е поне 512
* isGoodForTravel - приема обект от клас Computer и връща true, ако теглото е не повече от 2.5 кг и животът на батерията е над 6 часа

# Задача 7:
Реализирайте клас StringPool
Изисквания към класа StringPool

* Отговаря за съхраняване, споделяне и освобождаване на текстови низове;
* При поискване на низ (getString(const char*)):
* Ако вече съществува такъв низ, връща същия указател и увеличава броя препратки;
* Ако не съществува – създава го, съхранява го и връща нов указател;
* При освобождаване на низ (removeString(const char*)):
* Намалява броя препратки;
* Ако броят стане 0 – освобождава паметта;

# Задача 8:
Реализирайте клас ImmutableString, който:
Представлява текстов низ (const char*), който не може да се променя след създаване;
При създаването си не заделя нова памет, ако вече съществува низ със същото съдържание;
Използва централизиран мениджър на паметта – клас StringPool – за да гарантира, че еднакви низове сочат към една и съща локация в паметта;
Следи и управлява използването на стринговете чрез брой препратки (reference count).

Изисквания към класа ImmutableString

* Конструктор: приема const char* и използва StringPool, за да получи указател към съществуваща или нова памет;
* Копи-конструктор: копира указателя от друг ImmutableString, като увеличава броя препратки в пула;
* Деструктор: освобождава препратката към стринга чрез StringPool;
* Оператор []: достъп до символ по индекс (четене);

Функции:

* size_t length() const – връща дължината на низа;
* const char* c_str() const – връща C-style низ;
* Забрана: няма operator=, за да се запази иммутабилността;
* Оператор за събиране: +, връща нов ImmutableString от сбора на подадените 2
* Оператори за сравнение: ==, !=, <, <=, >, >=, базирани на strcmp;
* Оператор за изход: operator<<, който отпечатва текста.
