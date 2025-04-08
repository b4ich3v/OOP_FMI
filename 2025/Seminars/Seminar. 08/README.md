# Задача 1: 
Да се напише функция throwSomething(), която пита потребителя какъв тип изключение иска да бъде хвърлено. След това да се създаде caller() функция, която прихваща някои от тях, и main(), която прихваща останалите.
Изисквания:

В throwSomething() да се използва switch, като се хвърля:

* char
* int
* double
* std::runtime_error
* std::out_of_range
* друго → std::logic_error

В caller() прихващайте само int и double. В main() прихващайте std::out_of_range, std::exception, и останалото (...)
