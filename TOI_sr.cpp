#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

#define ARR_LEN 2 //инструкция предпроцессору заменить при компеляции ARR_LEN на 3

#pragma region PrintLine & SkipString

void PrintLine()
{
    std::cout << "----------------------------------------------------------------" << std::endl;
}

void SkipString()
{
    std::cout << std::endl;
}

#pragma endregion

#pragma region Описание и создание изначального массива

struct Musician
{
    std::string nickname; //псевдоним музыканта
    std::string realName; //настоящее имя музыканта
    std::string label; //лейбл
    uint64_t listenersCount; // количество слушателей
    Musician(): listenersCount(0) {}
    Musician(std::string nickname, std::string realName, std::string label, uint64_t listenersCount) : nickname(nickname), realName(realName), label(label), listenersCount(listenersCount) {}
};

Musician musicians[ARR_LEN];

//функция для создания элемента структуры Musician
void GetMusicianInformation(int serNumber)
{
    std::string count; //переменная для считывания и проверки кол-ва слушателей
    bool isConverted = false;

    std::cout << "Начинаем ввод информации об артисте " << serNumber + 1 << std::endl;
    std::cout << "Введите псевдоним артиста: ";
    std::cin >> musicians[serNumber].nickname;

    std::cout << "Введите настоящее имя артиста: ";
    std::cin >> musicians[serNumber].realName;

    std::cout << "Введите лейбл артиста: ";
    std::cin >> musicians[serNumber].label;

    while (!isConverted)
    {
        std::cout << "Введите количество слушателей в месяц у артиста: ";
        std::cin >> count;

        try
        {
            size_t pos;
            musicians[serNumber].listenersCount = stoul(count, &pos);
            if (pos == count.length())
                isConverted = true;
            else
                std::cout << "Количество слушателей за месяц должно быть целым беззнаковым числом" << std::endl;
        }

        catch (std::invalid_argument)
        {
            std::cout << "Количество слушателей за месяц должно быть числом" << std::endl;
        }

        catch (std::out_of_range)
        {
            std::cout << "Количество слушателей за месяц должно быть неотрицательным и не превышающим 140697553867517" << std::endl; // 140697553867517 - граница типа uint64_t
        }
    }
}

//заполнение массива
void FillMusicians()
{
    for (int i = 0; i < ARR_LEN; i++)
    {
        SkipString();
        GetMusicianInformation(i);
    }
    PrintLine();
}

#pragma endregion

#pragma region Задание 1

#pragma region Описание структур индекс-массивов

struct NicknameIndex
{
    std::string nickname;
    int position; //идекс в массиве musicians
};

struct ListenersCountIndex
{
    int listenersCount;
    int position; //идекс в массиве musicians
};

#pragma endregion

#pragma region Создание массивов

NicknameIndex nicknameIndexes[ARR_LEN];
ListenersCountIndex listenersIndexes[ARR_LEN];

#pragma endregion

#pragma region Выводы

//вывод массива
void PrintMusicians()
{
    std::cout << std::endl;
    PrintLine();
    std::cout << "Изначальный массив";
    for (int i = 0; i < ARR_LEN; i++)
    {
        std::cout << std::endl;
        std::cout << "Элемент " << i + 1 << std::endl;
        std::cout << "Псевдоним исполнителя: " << musicians[i].nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << musicians[i].realName << std::endl;
        std::cout << "Лейбл исполнителя: " << musicians[i].label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[i].listenersCount << std::endl;
    }
    PrintLine();
}

//вывод массива после удаления элементов
void PrintRedactedMusicians() 
{
    bool isAllDeleted = true;

    //проверка на непустоту массива
    for (int i = 0; i < ARR_LEN; i++) 
    {
        if ((musicians[i].nickname != "nothing") && (musicians[i].listenersCount != -1))
        {
            isAllDeleted = false;
            break;
        }
    }

    if (!isAllDeleted) 
    {
        SkipString();
        PrintLine();
        std::cout << "Полученный массив";
        SkipString();

        for (int i = 0; i < ARR_LEN; i++)
        {
            if ((musicians[i].nickname != "nothing") && (musicians[i].listenersCount != -1))
            {
                std::cout << std::endl;
                std::cout << "Элемент " << i + 1 << std::endl;
                std::cout << "Псевдоним исполнителя: " << musicians[i].nickname << std::endl;
                std::cout << "Настоящее имя исполнителя: " << musicians[i].realName << std::endl;
                std::cout << "Лейбл исполнителя: " << musicians[i].label << std::endl;
                std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[i].listenersCount << std::endl;
            }
        }
    }
    
    else 
    { 
        SkipString();
        PrintLine();
        std::cout << "В массиве не осталось элементов";
        SkipString();
    }
}

//вывод индекс-массива 1
void PrintNicknameIndexes()
{
    std::cout << "Массив, отсортированный по псевдониму исполнителя: " << std::endl;
    for (int i = 0; i < ARR_LEN; i++)
    {
        if ((musicians[nicknameIndexes[i].position].nickname != "nothing") && (musicians[nicknameIndexes[i].position].listenersCount != -1))
        {
            SkipString();
            std::cout << "Псевдоним исполнителя: " << musicians[nicknameIndexes[i].position].nickname << std::endl;
            std::cout << "Настоящее имя исполнителя: " << musicians[nicknameIndexes[i].position].realName << std::endl;
            std::cout << "Лейбл исполнителя: " << musicians[nicknameIndexes[i].position].label << std::endl;
            std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[nicknameIndexes[i].position].listenersCount << std::endl;
        }

    }
    PrintLine();
}

//вывод индекс-массива 2
void PrintListenersCountIndexes()
{
    std::cout << "Массив, отсортированный по количеству слушателей у исполнителя: " << std::endl;
    for (int i = 0; i < ARR_LEN; i++)
    {
        if ((musicians[listenersIndexes[i].position].nickname != "nothing") && (musicians[listenersIndexes[i].position].listenersCount != -1))
        {
            std::cout << std::endl;
            std::cout << "Псевдоним исполнителя: " << musicians[listenersIndexes[i].position].nickname << std::endl;
            std::cout << "Настоящее имя исполнителя: " << musicians[listenersIndexes[i].position].realName << std::endl;
            std::cout << "Лейбл исполнителя: " << musicians[listenersIndexes[i].position].label << std::endl;
            std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[listenersIndexes[i].position].listenersCount << std::endl;
        }

    }
    PrintLine();
}
#pragma endregion

#pragma region Nickname

#pragma region создание

//создание индекс-массива для nickname
void CreateNicknameIndex()
{
    //заполнение индекс-массива на основе изначального массива
    for (int i = 0; i < ARR_LEN; i++)
    {
        if ((musicians[i].nickname != "nothing") && (musicians[i].listenersCount != -1))
        {
            nicknameIndexes[i].nickname = musicians[i].nickname;
            nicknameIndexes[i].position = i;
        }
    }
}

#pragma endregion

#pragma region сортировки

//сортровка индекс-массива по ключу nickname
void NickNameIndexSort()
{
    NicknameIndex swap; //переменная, через которую будет запоминаться значение при замене

    for (int i = 0; i < ARR_LEN / 2; i++)
    {
        for (int j = 0; j < ARR_LEN - i - 1; j++)
        {
            if (nicknameIndexes[j].nickname > nicknameIndexes[j + 1].nickname)
            {
                swap = nicknameIndexes[j];
                nicknameIndexes[j] = nicknameIndexes[j + 1];
                nicknameIndexes[j + 1] = swap;
            }
        }

        for (int j = ARR_LEN - i - 1; j > i; j--)
        {
            if (nicknameIndexes[j].nickname < nicknameIndexes[j - 1].nickname)
            {
                swap = nicknameIndexes[j];
                nicknameIndexes[j] = nicknameIndexes[j - 1];
                nicknameIndexes[j - 1] = swap;
            }
        }
    }
}

void NickNameIndexReversedSort()
{
    NicknameIndex swap; //переменная, через которую будет запоминаться значение при замене
    NickNameIndexSort(); // Сначала сортируем массив

    for (int i = 0; i < ARR_LEN / 2; i++)
    {
        swap = nicknameIndexes[i];
        nicknameIndexes[i] = nicknameIndexes[ARR_LEN - i - 1];
        nicknameIndexes[ARR_LEN - i - 1] = swap;
    }
}

#pragma endregion

#pragma region итерационный бинарный поиск

void NickNameBinSearch() 
{
    std::string nickName; //nick для поиска
    int leftBorder = 0, rightBorder = ARR_LEN - 1;
    bool found = false;

    NickNameIndexSort();

    std::cout << "Введите псевдоним исполнителя для поиска: ";
    std::cin >> nickName;
    std::cout << std::endl;

    while (leftBorder <= rightBorder) 
    {
        int middle = (rightBorder - leftBorder) / 2 + leftBorder; // индекс обрабатываемого элемента

        if (nicknameIndexes[middle].nickname == nickName) 
        {
            std::cout << "Псевдоним исполнителя: " << musicians[nicknameIndexes[middle].position].nickname << std::endl;
            std::cout << "Настоящее имя исполнителя: " << musicians[nicknameIndexes[middle].position].realName << std::endl;
            std::cout << "Лейбл исполнителя: " << musicians[nicknameIndexes[middle].position].label << std::endl;
            std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[nicknameIndexes[middle].position].listenersCount << std::endl;
            found = true;
            break;
        }

        else 
        {
            if (nicknameIndexes[middle].nickname > nickName) 
            {
                rightBorder = middle - 1;
            }

            else
            {
                leftBorder = middle + 1;
            }
        }
    }

    if (!found) { std::cout << "Элемент не найден" << std::endl; }
    PrintLine();
    SkipString();
}

#pragma endregion

#pragma region редактирование элементов

//будем ли менять?
char NicknameEditAsk() 
{
    char answer;
    bool isCorrect = false;
    std::cout << std::endl;
    std::cout << "Хотите ли вы изменить псевдоним какого-либо исполнителя? ";
    
    do 
    {
        std::cin >> answer;
        std::cout << std::endl;

        if ((answer == '+') || (answer == '-'))
        {
            isCorrect = true;
        }
        else 
        { 
            std::cout << "Ответ может быть + или -(тип char), повторите ввод: "; 
        }

    } while (!isCorrect);

    return answer;
}

//получаем номер изменяемого элемента
int AskNicknamePosition() 
{
    std::string inputData;
    bool isConverted = false;
    int number;

    std::cout << "Введите номер изменяемого элемента: ";
    
    while ((!isConverted) || (number <= 0) || (number > ARR_LEN))
    {
        std::cin >> inputData;

        try
        {
            size_t pos;
            number = stoul(inputData, &pos);

            if (pos == inputData.length())
            {
                isConverted = true;
            }
  
            if ((number > ARR_LEN) || (number <= 0))
            {
                isConverted = false;
                std::cout << "Номер элемента может быть в диапазоне от 1 до " << ARR_LEN << std::endl;
                std::cout << "Повторите ввод: ";
            }   
        }

        catch (std::invalid_argument)
        {
            std::cout << "Номер элемента должен быть числом, повторите ввод: ";
        }
    }

    return number - 1;
}

//само редактирование
void NicknameEdit() 
{
    char answer = NicknameEditAsk();
    std::string newNickname;

    if (answer == '+') 
    {
        while (answer == '+') 
        {
            int number = AskNicknamePosition();
            std::cout << std::endl;

            std::cout << "Введите новый псевдоним исполнителя: ";
            std::cin >> newNickname;
            std::cout << std::endl;

            musicians[number].nickname = newNickname;
            CreateNicknameIndex();
            NickNameIndexSort();

            PrintNicknameIndexes();

            answer = NicknameEditAsk();
        }
    }
    else 
    {
        std::cout << "Вы не внесли никаких изменений" << std::endl;
    }

    PrintLine();
}

#pragma endregion

#pragma region удаление элементов

//будем ли удалять?
char DelNicknameAsk()
{
    char answer;
    bool isCorrect = false;
    std::cout << std::endl;
    std::cout << "Хотите ли вы удалить какой-либо элемент по псевдониму исполнителя? ";

    do
    {
        std::cin >> answer;
        std::cout << std::endl;

        if ((answer == '+') || (answer == '-'))
        {
            isCorrect = true;
        }
        else
        {
            std::cout << "Ответ может быть + или -(тип char), повторите ввод: ";
        }

    } while (!isCorrect);

    return answer;
}

//запрос значения для удаления
std::string AskNicknameKey()
{
    std::string answer;
    bool is = false;

    std::cout << "Введите псевдоним, по которому будет произведено удаление: ";
    do
    {
        std::cin >> answer;

        for (int i = 0; i < ARR_LEN; i++)
        {
            if (musicians[i].nickname == answer) { is = true; }
        }

        if (!is) { std::cout << "Ошибка ввода, повторите попытку: "; }
    } while (!is);

    return answer;
}

//само удаление
void NicknameDelition()
{
    char answer = DelNicknameAsk();
    int remainigElements = ARR_LEN; //кол-во не удаленных элементов

    while ((answer == '+') && (remainigElements != 0))
    {
        std::string delElement = AskNicknameKey();

        for (int i = 0; i < ARR_LEN; i++) 
        {
            if (musicians[i].nickname == delElement) 
            {
                musicians[i].nickname = "nothing";
                break;
            }
        }

        remainigElements -= 1;
        PrintRedactedMusicians();

        answer = DelNicknameAsk();
    }
}

#pragma endregion

#pragma endregion

#pragma region ListenersCount

#pragma region создание

//создание индекс-массива для listenersCount
void CreateListenersCountIndex()
{
    //заполнение индекс-массива на основе изначального массива
    for (int i = 0; i < ARR_LEN; i++)
    {
        listenersIndexes[i].listenersCount = musicians[i].listenersCount;
        listenersIndexes[i].position = i;
    }
}

#pragma endregion

#pragma region сортировки

//сортровка индекс-массива по ключу listenersCount
void ListenersCountIndexSort()
{
    ListenersCountIndex swap; //переменная, через которую будет запоминаться значение при замене

    for (int i = 0; i < ARR_LEN / 2; i++)
    {
        for (int j = 0; j < ARR_LEN - i - 1; j++)
            {
                if (listenersIndexes[j].listenersCount > listenersIndexes[j + 1].listenersCount)
                {
                    swap = listenersIndexes[j];
                    listenersIndexes[j] = listenersIndexes[j + 1];
                    listenersIndexes[j + 1] = swap;
                }
            }

        for (int j = ARR_LEN - i - 1; j > i; j--)
            {
                if (listenersIndexes[j].listenersCount < listenersIndexes[j - 1].listenersCount)
                {
                    swap = listenersIndexes[j];
                    listenersIndexes[j] = listenersIndexes[j - 1];
                    listenersIndexes[j - 1] = swap;
                }
            }
    }
}

//сортировка индекс-массива в обратном порядке
void ListenersCountIndexReversedSort() 
{
    ListenersCountIndex swap; //переменная, через которую будет запоминаться значение при замене
    ListenersCountIndexSort(); // Сначала сортируем массив

    for (int i = 0; i < ARR_LEN / 2; i++)
    {
        swap = listenersIndexes[i];
        listenersIndexes[i] = listenersIndexes[ARR_LEN - i - 1];
        listenersIndexes[ARR_LEN - i - 1] = swap;
    }
}


#pragma endregion

#pragma region рекурсивный бинарный поиск
int AskNumber() 
{
    std::string inputData;
    bool isConverted = false;
    int number;

    while (!isConverted)
    {
        std::cout << "Введите количество слушателей в месяц для поиска: ";
        std::cin >> inputData;

        try
        {
            size_t pos;
            number = stoul(inputData, &pos);

            if (pos == inputData.length())
                isConverted = true;
            else
                std::cout << "Количество слушателей за месяц должно быть целым беззнаковым числом" << std::endl;
        }

        catch (std::invalid_argument)
        {
            std::cout << "Количество слушателей за месяц должно быть числом" << std::endl;
        }

        catch (std::out_of_range)
        {
            std::cout << "Количество слушателей за месяц должно быть неотрицательным и не превышающим 140697553867517" << std::endl; // 140697553867517 - граница типа uint64_t
        }
    }

    return number;
}

int ListenersCountBinSerch(int leftBorder, int rightBorder, int number )
{
    ListenersCountIndexSort();

    if (leftBorder <= rightBorder)
    {
        int middle = (rightBorder - leftBorder) / 2 + leftBorder;
        
        if (listenersIndexes[middle].listenersCount == number)
        {
            return listenersIndexes[middle].position;
        }

        else
        {
            if (listenersIndexes[middle].listenersCount < number)
            {
                return ListenersCountBinSerch(middle + 1, rightBorder, number);
            }

            else
            {
                return ListenersCountBinSerch(leftBorder, middle - 1, number);
            }
        }
    }

    else { return -1; }
}

void ListenersCountBinSerchRealise() 
{
    SkipString();
    int number = AskNumber();
    SkipString();
    int result = ListenersCountBinSerch(0, ARR_LEN - 1, number);

    if (result == -1) 
    { 
        std::cout << std::endl;
        std::cout << "Значение не найдено" << std::endl; 
    }

    else 
    {
        std::cout << "Псевдоним исполнителя: " << musicians[result].nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << musicians[result].realName << std::endl;
        std::cout << "Лейбл исполнителя: " << musicians[result].label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[result].listenersCount << std::endl;
    }

    PrintLine();
    SkipString();
}
#pragma endregion

#pragma region редактирование элементов

//будем ли менять?
char ListenersEditAsk()
{
    char answer;
    bool isCorrect = false;
    std::cout << std::endl;
    std::cout << "Хотите ли вы изменить количество слушателей у какого-либо исполнителя? ";

    do
    {
        std::cin >> answer;
        std::cout << std::endl;

        if ((answer == '+') || (answer == '-'))
        {
            isCorrect = true;
        }
        else
        {
            std::cout << "Ответ может быть + или -(тип char), повторите ввод: ";
        }

    } while (!isCorrect);

    return answer;
}

//получаем номер изменяемого элемента
int ListenersPosition()
{
    std::string inputData;
    bool isConverted = false;
    int number;

    std::cout << "Введите номер изменяемого элемента: ";

    while ((!isConverted) || (number <= 0) || (number > ARR_LEN))
    {
        std::cin >> inputData;

        try
        {
            size_t pos;
            number = stoul(inputData, &pos);

            if (pos == inputData.length())
            {
                isConverted = true;
            }

            if ((number > ARR_LEN) || (number <= 0))
            {
                isConverted = false;
                std::cout << "Номер элемента может быть в диапазоне от 1 до " << ARR_LEN << std::endl;
                std::cout << "Повторите ввод: ";
            }
        }

        catch (std::invalid_argument)
        {
            std::cout << "Номер элемента должен быть числом, повторите ввод: ";
        }
    }

    return number - 1;
}

//само изменение
void ListenersEdit()
{
    char answer = ListenersEditAsk();
    std::string inputData;

    while (answer == '+')
    {
    
        int number = ListenersPosition();
        bool isConverted = false;
        SkipString();

        while (!isConverted)
        {
            std::cout << "Введите новое количество слушателей в месяц у артиста: ";
            std::cin >> inputData;

            try
            {
                size_t pos;
                musicians[number].listenersCount = stoul(inputData, &pos);
                if (pos == inputData.length())
                    isConverted = true;
                else
                    std::cout << "Количество слушателей за месяц должно быть целым беззнаковым числом" << std::endl;
            }

            catch (std::invalid_argument)
            {
                std::cout << "Количество слушателей за месяц должно быть числом" << std::endl;
            }

            catch (std::out_of_range)
            {
                std::cout << "Количество слушателей за месяц должно быть неотрицательным и не превышающим 140697553867517" << std::endl; // 140697553867517 - граница типа uint64_t
            }
        }

        CreateListenersCountIndex();
        ListenersCountIndexSort();

        PrintListenersCountIndexes();

        answer = ListenersEditAsk();

    }
    PrintLine();
}

#pragma endregion

#pragma region удаление элементов

//будем ли удалять?
char DelListenersAsk()
{
    char answer;
    bool isCorrect = false;
    std::cout << std::endl;
    std::cout << "Хотите ли вы удалить какой-либо элемент по количеству слушателей у исполнителя? ";

    do
    {
        std::cin >> answer;
        std::cout << std::endl;

        if ((answer == '+') || (answer == '-'))
        {
            isCorrect = true;
        }
        else
        {
            std::cout << "Ответ может быть + или -(тип char), повторите ввод: ";
        }

    } while (!isCorrect);

    return answer;
}

//поиск удаляемого элемента
int AskListenersKey()
{
    int answer;
    std::string inputData;
    bool is = false, isConverted = false;

    do
    {
        while (!isConverted)
        {
            std::cout << "Введите количество слушателей, по которому будет произведено удаление: ";
            std::cin >> inputData;

            try
            {
                size_t pos;
                answer = stoul(inputData, &pos);

                if (pos == inputData.length())
                    isConverted = true;
                
                else
                    std::cout << "Количество слушателей за месяц должно быть целым беззнаковым числом" << std::endl;
            }

            catch (std::invalid_argument)
            {
                std::cout << "Количество слушателей за месяц может быть только числом" << std::endl;
            }

            catch (std::out_of_range)
            {
                std::cout << "Количество слушателей за месяц должно быть неотрицательным и не превышающим 140697553867517" << std::endl; // 140697553867517 - граница типа uint64_t
            }
        }

        for (int i = 0; i < ARR_LEN; i++)
        {
            if (musicians[i].listenersCount == answer) { is = true; }
        }

        if (!is) { std::cout << "Ошибка ввода, повторите попытку: "; }
    } while (!is);

    return answer;
}

//само удаление
void ListenersDelition()
{
    char answer = DelListenersAsk();
    int remainingElements = ARR_LEN; //кол-во не удаленных элементов

    while ((answer == '+') && (remainingElements != 0))
    {
        int delElement = AskListenersKey();

        for (int i = 0; i < ARR_LEN; i++)
        {
            if (musicians[i].listenersCount == delElement)
            {
                musicians[i].listenersCount = -1;
                break;
            }
        }

        remainingElements -= 1;
        PrintRedactedMusicians();

        answer = DelListenersAsk();
    }
}

#pragma endregion


#pragma endregion

#pragma endregion

#pragma region Задание 2

#pragma region Описание структур деревьев

struct NickNameBenTreeNode
{
    std::string nickname;
    int index; // Индекс элемента в массиве
    NickNameBenTreeNode* left;
    NickNameBenTreeNode* right;

    NickNameBenTreeNode(std::string nick, int idx) : nickname(nick), index(idx), left(nullptr), right(nullptr) {}
};

struct ListenersBenTreeNode
{
    uint64_t listeners;
    int index; // Индекс элемента в массиве
    ListenersBenTreeNode* left;
    ListenersBenTreeNode* right;

    ListenersBenTreeNode(uint64_t listeners, int idx) : listeners(listeners), index(idx), left(nullptr), right(nullptr) {}
};

#pragma endregion

#pragma region NickName

#pragma region Создание и заполнение

//создание и расположение узлов в дереве
NickNameBenTreeNode* FillNicknameTree(NickNameBenTreeNode* link, int index)
{
    //создание узла
    if (link == nullptr)
    {
        //Проверка на "nothing" при создании узла
        if ((musicians[index].nickname == "nothing") && (musicians[index].listenersCount != -1))
            return nullptr;

        NickNameBenTreeNode* node = new NickNameBenTreeNode(musicians[index].nickname, index);
        return node;
    }

    //Проверка на "nothing" перед сравнением
    if ((musicians[index].nickname != "nothing") && (musicians[index].listenersCount != -1))
    {
        //помещение узла в левую ветвь дерева
        if (musicians[index].nickname < link->nickname)
        {
            link->left = FillNicknameTree(link->left, index);
        }

        //помещение узла в правую ветвь дерева
        if (musicians[index].nickname > link->nickname)
        {
            link->right = FillNicknameTree(link->right, index);
        }
    }

    return link;
}

//само построение дерева
NickNameBenTreeNode* CreateNickNameTree()
{
    NickNameBenTreeNode* root = nullptr;

    for (int i = 0; i < ARR_LEN; i++)
    {
        root = FillNicknameTree(root, i); 
    }
    return root;
}

#pragma endregion

#pragma region Вывод

//Функция для вывода дерева в виде таблицы
void printNicknameNode(NickNameBenTreeNode* node)
{
    if (node != nullptr)
    {
        printNicknameNode(node->left); // Сначала левое поддерево

        int index = node->index; // Получаем индекс музыканта

        //Вывод данных в формате таблицы
        std::cout << std::left << std::setw(6) << index + 1
            << std::setw(12) << musicians[index].nickname
            << std::setw(15) << musicians[index].realName
            << std::setw(10) << musicians[index].label
            << std::setw(10) << musicians[index].listenersCount << std::endl;

        printNicknameNode(node->right); // Затем правое поддерево
    }
}

//Функция для формирования шапки и печати таблицы
void printNicknameTreeTable(NickNameBenTreeNode* root)
{
    if (root != nullptr)
    {
        //Шапка таблицы
        SkipString();
        std::cout << std::left << std::setw(6) << "Номер"
            << std::setw(12) << "Псевдоним"
            << std::setw(15) << "Настоящее имя"
            << std::setw(10) << "Лейбл"
            << std::setw(10) << "Количество слушателей" << std::endl;

        printNicknameNode(root); // Начинаем обход с корня
    }
}

#pragma endregion

#pragma region Рекурсивнный бинарный поиск

// Рекурсивная функция бинарного поиска
void recursiveBinarySearch(NickNameBenTreeNode* node, const std::string& searchNickname) {
    if (node == nullptr)
    {
        std::cout << "Музыкант с псевдонимом '" << searchNickname << "' не найден" << std::endl;
    }

    else if (searchNickname == node->nickname)
    {
        int index = node->index;
        SkipString();
        std::cout << "Псевдоним исполнителя: " << musicians[index].nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << musicians[index].realName << std::endl;
        std::cout << "Лейбл исполнителя: " << musicians[index].label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[index].listenersCount << std::endl;
        SkipString();
    }

    else if (searchNickname < node->nickname) {
        recursiveBinarySearch(node->left, searchNickname); // Рекурсивный вызов для левого поддерева
    }
    else {
        recursiveBinarySearch(node->right, searchNickname); // Рекурсивный вызов для правого поддерева
    }
}

//Сама реализация бинарного поиска
void performSearchAndLoopN(NickNameBenTreeNode* root) 
{
    std::string searchNickname;

    while (true) 
    {
        std::cout << "Введите псевдоним для поиска (или '-' для выхода): ";
        std::cin >> searchNickname;

        if (searchNickname == "-") 
        {
            PrintLine();
            break; // Выход из цикла, если введен "-"
        }

        recursiveBinarySearch(root, searchNickname);
    }
}

#pragma endregion

#pragma region Удаление элементов

// Функция для удаления элемента из массива и дерева по псевдониму
void RemoveMusicianByNickname(const std::string& nicknameToRemove, NickNameBenTreeNode*& root)
{
    int indexToRemove = -1;

    // Ищем индекс музыканта по псевдониму
    for (int i = 0; i < ARR_LEN; ++i) {
        if (musicians[i].nickname == nicknameToRemove)
        {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1)
    {
        std::cout << "Музыкант с псевдонимом '" << nicknameToRemove << "' не найден" << std::endl;
        return;
    }

    // Помечаем музыканта как удаленного, присваивая псевдониму "nothing"
    musicians[indexToRemove].nickname = "nothing";

    // Перестраиваем дерево, исключая удаленный элемент
    NickNameBenTreeNode* oldRoot = root;
    root = CreateNickNameTree();
}

// Функция, которая запрашивает псевдоним для удаления или останавливает процесс
void AskUserForDeletionLoopN(NickNameBenTreeNode*& root) 
{
    std::string input;
    bool continueDeleting = true;

    while (continueDeleting) 
    {
        // Проверяем, остались ли еще элементы для удаления
        bool hasElements = false;

        for (int i = 0; i < ARR_LEN; ++i) 
        {
            if ((musicians[i].nickname != "nothing") && (musicians[i].listenersCount != -1))
            {
                hasElements = true;
                break;
            }
        }

        if (!hasElements) 
        {
            std::cout << "Вы удалили все элементы" << std::endl;
            PrintLine();
            break; // Выход из цикла и завершение работы
        }

        std::cout << "Введите псевдоним для удаления (или '-' для остановки): ";
        std::cin >> input;

        if (input == "-")
        {
            continueDeleting = false;
            SkipString();
            std::cout << "Полученное дерево:" << std::endl;
            printNicknameTreeTable(root);
            PrintLine();

        }

        else
        {
            RemoveMusicianByNickname(input, root);
            SkipString();
            std::cout << "Полученное дерево:" << std::endl;
            printNicknameTreeTable(root);
            SkipString();
        }
    }
}

#pragma endregion

#pragma endregion

#pragma region ListenersCount

#pragma region Создание и заполнение

//создание и расположение узлов в дереве
ListenersBenTreeNode* FillListenersTree(ListenersBenTreeNode* link, int index)
{
    //создание узла
    if (link == nullptr)
    {
        //Проверка на удаленность при создании узла
        if (musicians[index].listenersCount == -1)
            return nullptr;

        ListenersBenTreeNode* node = new ListenersBenTreeNode(musicians[index].listenersCount, index);
        return node;
    }

    //Проверка на удаление перед сравнением
    if ((musicians[index].listenersCount != -1) && (musicians[index].nickname != "nothing"))
    {
        //помещение узла в левую ветвь дерева
        if (musicians[index].listenersCount < link->listeners)
        {
            link->left = FillListenersTree(link->left, index);
        }

        //помещение узла в правую ветвь дерева
        if (musicians[index].listenersCount > link->listeners)
        {
            link->right = FillListenersTree(link->right, index);
        }
    }

    return link;
}

//само построение дерева
ListenersBenTreeNode* CreateListenersTree()
{
    ListenersBenTreeNode* root = nullptr;

    for (int i = 0; i < ARR_LEN; i++)
    {
        root = FillListenersTree(root, i); // root нужно обновлять
    }
    return root;
}

#pragma endregion

#pragma region Вывод

//Вспомогательная функция для вывода дерева в виде таблицы
void printListenersNode(ListenersBenTreeNode* node)
{
    if (node != nullptr)
    {
        printListenersNode(node->left); // Сначала левое поддерево

        int index = node->index; // Получаем индекс музыканта

        //Вывод данных в формате таблицы
        std::cout << std::left << std::setw(6) << index + 1
            << std::setw(12) << musicians[index].nickname
            << std::setw(15) << musicians[index].realName
            << std::setw(10) << musicians[index].label
            << std::setw(10) << musicians[index].listenersCount << std::endl;

        printListenersNode(node->right); // Затем правое поддерево
    }
}

//Функция для вывода дерева в виде таблицы
void printListenersTreeTable(ListenersBenTreeNode* root)
{
    if (root != nullptr)
    {
        //Шапка таблицы
        SkipString();
        std::cout << std::left << std::setw(6) << "Номер"
            << std::setw(12) << "Псевдоним"
            << std::setw(15) << "Настоящее имя"
            << std::setw(10) << "Лейбл"
            << std::setw(10) << "Количество слушателей" << std::endl;

        printListenersNode(root); // Начинаем обход с корня
    }
}

#pragma endregion

#pragma region Итерационный бинарный поиск

// Итерационная версия бинарного поиска по дереву
void iterativeBinarySearch(ListenersBenTreeNode* node, const uint64_t& searchNickname) 
{
    ListenersBenTreeNode* current = node;

    while (current != nullptr) 
    {
        if (searchNickname == current->listeners) 
        {
            int index = current->index;
            SkipString();
            std::cout << "Псевдоним исполнителя: " << musicians[index].nickname << std::endl;
            std::cout << "Настоящее имя исполнителя: " << musicians[index].realName << std::endl;
            std::cout << "Лейбл исполнителя: " << musicians[index].label << std::endl;
            std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[index].listenersCount << std::endl;
            SkipString();
            return; // Элемент найден, выходим из функции
        }

        else if (searchNickname < current->listeners) 
        {
            current = current->left; // Переходим в левое поддерево
        }

        else 
        {
            current = current->right; // Переходим в правое поддерево
        }
    }

    // Если цикл завершился и элемент не найден
    std::cout << "Музыкант с количеством слушателей " << searchNickname << " не найден" << std::endl;
}

// Функция для выполнения поиска в цикле
void performSearchAndLoopL(ListenersBenTreeNode* root)
{
    std::string inputData;
    bool isConverted = false, ended = false;
    int number;
 
    do{
        
        do{
            std::cout << "Введите количество слушателей в месяц для поиска(для выхода введите -): ";
            std::cin >> inputData;

            if (inputData == "-")
            {
                PrintLine();
                ended = true;
                break; // Выход из цикла, если введен "-"
            }

            try
            {
                size_t pos;
                number = stoul(inputData, &pos);

                if (pos == inputData.length())
                    isConverted = true;
                else
                    std::cout << "Количество слушателей за месяц должно быть целым беззнаковым числом" << std::endl;
            }

            catch (std::invalid_argument)
            {
                std::cout << "Количество слушателей за месяц должно быть числом" << std::endl;
            }

            catch (std::out_of_range)
            {
                std::cout << "Количество слушателей за месяц должно быть неотрицательным и не превышающим 140697553867517" << std::endl; // 140697553867517 - граница типа uint64_t
            }

        } while (!isConverted);

        iterativeBinarySearch(root, number);

    } while (!ended);
}

#pragma endregion

#pragma region Удаление элементов

// Функция для удаления элемента из массива и дерева по псевдониму
void RemoveMusicianByListeners(const uint64_t& listenersToRemove, ListenersBenTreeNode*& root)
{
    int indexToRemove = -1;

    // Ищем индекс музыканта по псевдониму
    for (int i = 0; i < ARR_LEN; ++i) {
        if (musicians[i].listenersCount == listenersToRemove)
        {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1)
    {
        std::cout << "Музыкант с количеством слушателей '" << listenersToRemove << "' не найден" << std::endl;
        return;
    }

    // Помечаем музыканта как удаленного, присваивая количеству слушателей -1
    musicians[indexToRemove].listenersCount = -1;

    // Перестраиваем дерево, исключая удаленный элемент
    ListenersBenTreeNode* oldRoot = root;
    root = CreateListenersTree();
}

// Функция, которая запрашивает псевдоним для удаления или останавливает процесс
void AskUserForDeletionLoopL(ListenersBenTreeNode*& root)
{
    std::string inputData;
    bool isConverted = false, ended = false;
    int number;

    do {
        do {
            std::cout << "Введите количество слушателей в месяц для удаления (для выхода введите -): ";
            std::cin >> inputData;

            if (inputData == "-")
            {
                PrintLine();
                ended = true;
                break; // Выход из цикла, если введен "-"
            }

            try
            {
                size_t pos;
                number = stoul(inputData, &pos);

                if (pos == inputData.length())
                    isConverted = true;
                else
                    std::cout << "Количество слушателей за месяц должно быть целым беззнаковым числом" << std::endl;
            }
            catch (std::invalid_argument)
            {
                std::cout << "Количество слушателей за месяц должно быть числом" << std::endl;
            }
            catch (std::out_of_range)
            {
                std::cout << "Количество слушателей за месяц должно быть неотрицательным и не превышающим 140697553867517" << std::endl; // 140697553867517 - граница типа uint64_t
            }

        } while (!isConverted);

        RemoveMusicianByListeners(number, root);

        SkipString();
        std::cout << "Полученное дерево:" << std::endl;
        printListenersTreeTable(root);
        SkipString();

        // Проверяем, остались ли еще элементы для удаления
        bool hasElements = false;
        for (int i = 0; i < ARR_LEN; ++i)
        {
            if ((musicians[i].nickname != "nothing") && (musicians[i].listenersCount != -1))
            {
                hasElements = true;
                break;
            }
        }

        // Если нет элементов, завершаем программу
        if (!hasElements) 
        {
            std::cout << "Вы удалили все элементы" << std::endl;
            PrintLine();
            break;
        }

    } while (!ended);
}


#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Задание 3

#pragma region Описание структур линейных списков

struct LineList
{
    Musician* musician;
    LineList* next; // Следующий элемент в порядке ввода
    LineList* nextName; // Следующий элемент в порядке сортировки по псевдониму
    LineList* nextListeners; // Следующий элемент в порядке сортировки по количеству слушателей

    LineList(Musician* mus) : musician(mus),  next(nullptr), nextName(nullptr), nextListeners(nullptr){}
};

LineList* head;
LineList* headName;
LineList* headListeners;

#pragma endregion

#pragma region Создание списков

void AddToHead(LineList*& head, LineList* elem) {
    if (!head) {
        head = elem;
        return;
    }
    LineList* curr = head;
    while (!curr->next) {
        curr = curr->next;
    }
    curr->next = elem;
}

void AddToHeadName(LineList*& head, LineList* elem) 
{
    if (head == nullptr) 
    {
        head = elem;
        return;
   }

    LineList* curr = head;
    LineList* prev = nullptr;
    while (curr) //curr != nullptr
    {
        if (curr->musician->nickname > elem->musician->nickname) 
        {
            if (prev) 
            {
                prev->nextName = elem;
                elem->nextName = curr;
                return;
            }
            elem->nextName = curr;
            head = elem;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->nextName = elem;

}

void AddToHeadListeners(LineList*& head, LineList* elem)
{
    if (head == nullptr)
    {
        head = elem;
        return;
    }

    LineList* curr = head;
    LineList* prev = nullptr;
    while (curr) //curr != nullptr
    {
        if (curr->musician->listenersCount > elem->musician->listenersCount)
        {
            if (prev)
            {
                prev->nextListeners = elem;
                elem->nextListeners = curr;
                return;
            }
            elem->nextListeners = curr;
            head = elem;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->nextListeners = elem;

}

Musician* GetNewMusician() {
    std::string nickname, realName, label, count;
    std::string count; //переменная для считывания и проверки кол-ва слушателей
    uint64_t number;
    bool isConverted = false;

    std::cout << "Введите псевдоним артиста: ";
    std::cin >> nickname;

    std::cout << "Введите настоящее имя артиста: ";
    std::cin >> realName;

    std::cout << "Введите лейбл артиста: ";
    std::cin >> label;

    while (!isConverted)
    {
        std::cout << "Введите количество слушателей в месяц у артиста: ";
        std::cin >> count;

        try
        {
            size_t pos;
            number = stoul(count, &pos);
            if (pos == count.length())
                isConverted = true;
            else
                std::cout << "Количество слушателей за месяц должно быть целым беззнаковым числом" << std::endl;
        }

        catch (std::invalid_argument)
        {
            std::cout << "Количество слушателей за месяц должно быть числом" << std::endl;
        }

        catch (std::out_of_range)
        {
            std::cout << "Количество слушателей за месяц должно быть неотрицательным и не превышающим 140697553867517" << std::endl; // 140697553867517 - граница типа uint64_t
        }
    }

    return new Musician(nickname, realName, label, number);
}

void CreateList() 
{
    std::string answer;
    do 
    {
        std::cout << "Хотите ли вы ввести элемент?(+/-)";
        std::cin >> answer;
        if (answer == "+") 
        {
            Musician* musician = GetNewMusician();
            LineList* element = new LineList(musician);
            AddToHead(head, element);
            AddToHeadListeners(headListeners, element);
            AddToHeadName(headName, element);
        }
    } while (answer == "+");

}

#pragma endregion

#pragma region Просмотр

void PrintList(LineList* head) {
    LineList* curr = head;
    int i = 1;
    while (curr) {
        std::cout << std::endl;
        std::cout << "Элемент " << i++ << std::endl;
        std::cout << "Псевдоним исполнителя: " << curr->musician->nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << curr->musician->realName << std::endl;
        std::cout << "Лейбл исполнителя: " << curr->musician->label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << curr->musician->listenersCount << std::endl;
        curr = curr->next;
    }
}

void PrintListInNickOrder(LineList* head) {
    LineList* curr = head;
    int i = 1;
    while (curr) {
        std::cout << std::endl;
        std::cout << "Элемент " << i++ << std::endl;
        std::cout << "Псевдоним исполнителя: " << curr->musician->nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << curr->musician->realName << std::endl;
        std::cout << "Лейбл исполнителя: " << curr->musician->label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << curr->musician->listenersCount << std::endl;
        curr = curr->nextName;
    }
}

void PrintListInListenersOrder(LineList* head) {
    LineList* curr = head;
    int i = 1;
    while (curr) {
        std::cout << std::endl;
        std::cout << "Элемент " << i++ << std::endl;
        std::cout << "Псевдоним исполнителя: " << curr->musician->nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << curr->musician->realName << std::endl;
        std::cout << "Лейбл исполнителя: " << curr->musician->label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << curr->musician->listenersCount << std::endl;
        curr = curr->nextListeners;
    }
}

#pragma endregion


//#pragma region Сортировки
//

//
//// Функция сравнения для сортировки по количеству слушателей
//bool compareListeners(LineList* a, LineList* b) {
//    return a->musician->listenersCount > b->musician->listenersCount;
//}
//
//LineList* SortListByNickname(LineList* head)
//{
//    if (head == nullptr) return nullptr;
//
//    LineList* sorted = nullptr;
//    LineList* current = head;
//
//    while (current != nullptr)
//    {
//        LineList* next = current->nextInputOrder;
//        LineList** insertionPoint = &sorted;
//
//        while (*insertionPoint != nullptr && compareNicknames(current, *insertionPoint))
//        {
//            insertionPoint = &((*insertionPoint)->nextNickName);
//        }
//
//        LineList* newNode = new LineList(*current);
//        newNode->nextNickName = *insertionPoint;
//        *insertionPoint = newNode;
//        current = next;
//    }
//    return sorted;
//}
//
//LineList* SortListByListeners(LineList* head)
//{
//    if (head == nullptr) return nullptr;
//
//    LineList* sorted = nullptr;
//    LineList* current = head;
//
//    while (current != nullptr)
//    {
//        LineList* next = current->nextInputOrder;
//        LineList** insertionPoint = &sorted;
//
//        while (*insertionPoint != nullptr && compareListeners(current, *insertionPoint))
//        {
//            insertionPoint = &((*insertionPoint)->nextListeners);
//        }
//
//        LineList* newNode = new LineList(*current);
//        newNode->nextListeners = *insertionPoint;
//        *insertionPoint = newNode;
//        current = next;
//    }
//
//    return sorted;
//}
//
//#pragma endregion
//
//#pragma region Создание и заполнение
//
//LineList* CreateList()
//{
//    LineList* head = nullptr;
//    LineList* tail = nullptr;
//
//    for (int i = 0; i < current_ARR_LEN; ++i) 
//    {
//        // Проверка на "удаленные" элементы
//        if (musicians[i].nickname != "nothing" && musicians[i].listenersCount != -1)
//        {
//            LineList* newNode = new LineList(&musicians[i], i);
//            if (!head)
//            {
//                head = newNode;
//                tail = newNode;
//            }
//
//            else
//            {
//                tail->nextInputOrder = newNode;
//                tail = newNode;
//            }
//        }
//    }
//    return head;
//}
//
//void PrintList(LineList* head, std::string order) {
//    LineList* current = head;
//
//    std::cout << "Список исполнителей (по " << order << "):" << std::endl;
//    SkipString();
//
//    while (current != nullptr)
//    {
//        std::cout << "  Псевдоним исполнителя: " << current->musician->nickname << std::endl;
//        std::cout << "  Настоящее имя исполнителя: " << current->musician->realName << std::endl;
//        std::cout << "  Лейбл: " << current->musician->label << std::endl;
//        std::cout << "  Количество слушателей: " << current->musician->listenersCount << std::endl;
//        SkipString();
//
//        if (order == "порядке ввода")
//        {
//            current = current->nextInputOrder;
//        }
//
//        else if (order == "увеличению псевдонима")
//        {
//            current = current->nextNickName;
//        }
//
//        else if (order == "увеличению количества слушателей")
//        {
//            current = current->nextListeners;
//        }
//        else
//        {
//            std::cout << "Неизвестный порядок вывода." << std::endl;
//            return;
//        }
//    }
//
//    PrintLine();
//}
//#pragma endregion
//
//#pragma region Поиск и удаление
//
//#pragma region Поиск(2 способа)
//
//void PrintMusician(Musician* musician, int index)
//{
//
//    SkipString();
//    std::cout << "Найденный исполнитель: " << std::endl;
//    std::cout << "Псевдоним: " << musician->nickname << std::endl;
//    std::cout << "Настоящее имя: " << musician->realName << std::endl;
//    std::cout << "Лейбл: " << musician->label << std::endl;
//    std::cout << "Количество слушателей: " << musician->listenersCount << std::endl;
//    PrintLine();
//}
//
//// Функция поиска по псевдониму (рекурсивная)
//void SearchByNicknameRecursive(LineList* head, const std::string& searchNickname, bool& found)
//{
//    if (head == nullptr)
//    {
//        if (!found)
//        {
//            std::cout << "Исполнитель с псевдонимом " << searchNickname << " не найден" << std::endl;
//        }
//        return;
//    }
//
//    if (head->musician->nickname == searchNickname)
//    {
//        PrintMusician(head->musician, head->index);
//        found = true;
//    }
//
//    if (head->nextNickName != nullptr)
//        SearchByNicknameRecursive(head->nextNickName, searchNickname, found);
//    else
//    {
//        if (!found)
//        {
//            std::cout << "Исполнитель с псевдонимом '" << searchNickname << "' не найден" << std::endl;
//        }
//        return;
//    }
//}
//
//// Функция поиска по количеству слушателей (итерационная)
//void SearchByListenersIterative(LineList* head, int searchListeners)
//{
//    bool found = false;
//    LineList* current = head;
//
//    while (current != nullptr)
//    {
//        if (current->musician->listenersCount == searchListeners)
//        {
//            PrintMusician(current->musician, current->index);
//            found = true;
//        }
//        current = current->nextListeners; // Предполагается, что список отсортирован по слушателям
//    }
//
//    if (!found) {
//        std::cout << "Исполнитель с количеством слушателей " << searchListeners << " не найден" << std::endl;
//    }
//}
//
//// Отдельная функция для выполнения поиска на основе ввода пользователя
//void PerformSearch(LineList* headNickname, LineList* headListeners) 
//{
//    std::string searchChoice;
//    while (true) 
//    {
//        std::cout << "Желаете выполнить поиск исполнителя? (+/-): ";
//        std::cin >> searchChoice;
//
//        if (searchChoice == "-") 
//        {
//            break;
//        }
//
//        else if (searchChoice == "+") 
//        {
//            std::string searchType;
//            std::cout << "По какому ключу желаете искать (n/l)? ";
//            std::cin >> searchType;
//
//            if (searchType == "n") 
//            {
//                std::string nickname;
//                std::cout << "Введите псевдоним для поиска: ";
//                std::cin >> nickname;
//                bool nicknameFound = false;
//                SearchByNicknameRecursive(headNickname, nickname, nicknameFound);
//            }
//
//            else if (searchType == "l") 
//            {
//                int listeners;
//                std::cout << "Введите количество слушателей для поиска: ";
//                std::cin >> listeners;
//
//                // Проверка ввода (для избежания исключений)
//                if (std::cin.fail()) {
//                    std::cout << "Ошибка, введено некорректное значение для количества слушателей." << std::endl;
//                    std::cin.clear(); // Сбрасываем флаг ошибки
//                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
//                    continue; // Переходим к следующей итерации цикла
//                }
//                SearchByListenersIterative(headListeners, listeners);
//            }
//
//            else 
//            {
//                std::cout << "Некорректный тип поиска." << std::endl;
//            }
//        }
//        else 
//        {
//            std::cout << "Некорректный ввод, введите + или -" << std::endl;
//        }
//        std::cout << std::endl;
//    }
//}
//
//#pragma endregion
//
//#pragma region Удаление
//
//bool IsArrayEmpty(int current_ARR_LEN) 
//{
//    for (int i = 0; i < current_ARR_LEN; ++i) 
//    {
//        if (musicians[i].nickname != "nothing" && musicians[i].listenersCount != -1) 
//        {
//            return false; // Найден хотя бы один не "удаленный" элемент
//        }
//    }
//    return true; // Все элементы "удалены"
//}
//
//void PerformDeletion(int& current_ARR_LEN) {
//    std::string deleteChoice;
//    while (true) 
//    {
//        std::cout << "Желаете удалить исполнителя? (+/-): ";
//        std::cin >> deleteChoice;
//
//        if (deleteChoice == "-") 
//        {
//            break;
//        }
//
//        else if (deleteChoice == "+") 
//        {
//            std::string deleteType;
//            std::cout << "По какому ключу желаете удалить (n/l)? ";
//            std::cin >> deleteType;
//
//            if (deleteType == "n") 
//            {
//                std::string nickname;
//                std::cout << "Введите псевдоним исполнителя для удаления: ";
//                std::cin >> nickname;
//
//                bool found = false;
//
//                for (int i = 0; i < current_ARR_LEN; ++i) 
//                {
//                    if (musicians[i].nickname == nickname) 
//                    {
//                        musicians[i].nickname = "nothing";
//                        found = true;
//
//                        // Вывод текущего состояния массива
//                        SkipString();
//
//                        // Создание и вывод линейных списков после удаления
//                        LineList* headInputOrder = CreateList();
//                        PrintList(headInputOrder, "порядке ввода");
//
//                        LineList* headNickname = SortListByNickname(headInputOrder); // Сортировка и удаление старого списка
//                        PrintList(headNickname, "увеличению псевдонима");
//
//                        LineList* headListeners = SortListByListeners(CreateList());
//                        PrintList(headListeners, "увеличению количества слушателей");
//
//                        break;
//                    }
//                }
//
//                if (!found) 
//                {
//                    std::cout << "Исполнитель с псевдонимом " << nickname << " не найден." << std::endl;
//                }
//
//            }
//
//            else if (deleteType == "l") 
//            {
//                int listeners;
//                std::cout << "Введите количество слушателей исполнителя для удаления: ";
//                std::cin >> listeners;
//
//                if (std::cin.fail()) 
//                {
//                    std::cout << "Ошибка, введено некорректное значение для количества слушателей." << std::endl;
//                    std::cin.clear();
//                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                    continue;
//                }
//
//                bool found = false;
//                for (int i = 0; i < current_ARR_LEN; ++i) 
//                {
//                    if (musicians[i].listenersCount == listeners) 
//                    {
//                        musicians[i].listenersCount = -1;
//                        std::cout << "Исполнитель с количеством слушателей " << listeners << " удален" << std::endl;
//                        found = true;
//
//                        // Создание и вывод линейных списков после удаления
//                        LineList* headInputOrder = CreateList();
//                        std::cout << "Список в порядке ввода после удаления:" << std::endl;
//                        PrintList(headInputOrder, "порядке ввода");
//
//                        LineList* headNickname = SortListByNickname(headInputOrder); // Сортировка и удаление старого списка
//                        std::cout << "Список по псевдониму после удаления:" << std::endl;
//                        PrintList(headNickname, "увеличению псевдонима");
//
//                        LineList* headListeners = SortListByListeners(CreateList());
//                        std::cout << "Список по слушателям после удаления:" << std::endl;
//                        PrintList(headListeners, "увеличению количества слушателей");
//
//                        break;
//                    }
//                }
//                if (!found) 
//                {
//                    std::cout << "Исполнитель с количеством слушателей '" << listeners << "' не найден." << std::endl;
//                }
//
//            }
//
//            else 
//            {
//                std::cout << "Некорректный тип удаления." << std::endl;
//            }
//
//            // Проверка, не удалены ли все элементы
//            if (IsArrayEmpty(current_ARR_LEN)) 
//            {
//                std::cout << "Все исполнители удалены" << std::endl;
//                break;
//            }
//        }
//
//        else 
//        {
//            std::cout << "Некорректный ввод. Пожалуйста, введите + или -" << std::endl;
//        }
//
//        SkipString();
//    }
//}
//
//#pragma endregion
//
//#pragma region Выбор действия
//
//void PerformOperations(int& current_ARR_LEN, LineList* headNickname, LineList* headListeners)
//{
//    std::string choice;
//
//    while (true)
//    {
//        if (IsArrayEmpty(current_ARR_LEN)) 
//        {
//            std::cout << "Завершение работы" << std::endl;
//            break; // Выход из PerformOperations, если все элементы удалены
//        }
//
//        std::cout << "Что вы хотите сделать? (s/d/f): ";
//        std::cin >> choice;
//
//        if (choice == "s")
//        {
//            PerformSearch(headNickname, headListeners);
//        }
//
//        else if (choice == "d")
//
//        {
//            PerformDeletion(current_ARR_LEN);
//        }
//
//        else if (choice == "f")
//
//        {
//            std::cout << "Завершение работы" << std::endl;
//            break;
//        }
//
//        else
//        {
//            std::cout << "Некорректный ввод, введите 's', 'd' или 'f'." << std::endl;
//        }
//        std::cout << std::endl;
//    }
//}
//
//#pragma endregion
//
//#pragma endregion

#pragma endregion

int main()
{
    setlocale(LC_ALL, "Russian");
    FillMusicians();
    //PrintMusicians();

#pragma region Задание 1

   /* SkipString();
    CreateNicknameIndex();
    NickNameIndexSort();
    PrintNicknameIndexes(); 
    NickNameBinSearch();
    NicknameEdit();
    NicknameDelition();
    PrintRedactedMusicians();

    SkipString();
    NickNameIndexReversedSort();
    PrintNicknameIndexes();


    SkipString();
    CreateListenersCountIndex();
    ListenersCountIndexSort();
    PrintListenersCountIndexes();
    ListenersCountBinSerchRealise();
    ListenersEdit();
    ListenersDelition();
    PrintRedactedMusicians();

    SkipString();
    ListenersCountIndexReversedSort();
    PrintListenersCountIndexes();*/

#pragma endregion
//
#pragma region Задание 2

    NickNameBenTreeNode* root1 = CreateNickNameTree(); //создание дерева
    std::cout << "Бинарное дерево, построенное по псевдониму исполнителя:" << std::endl;
    printNicknameTreeTable(root1);
    SkipString();

    performSearchAndLoopN(root1);
    SkipString();

    //AskUserForDeletionLoopN(root1);
    //SkipString();

    //ListenersBenTreeNode* root2 = CreateListenersTree(); //создание дерева
    //std::cout << "Бинарное дерево, построенное по количеству слушателей у исполнителя:" << std::endl;
    //printListenersTreeTable(root2);
    //SkipString();

    //performSearchAndLoopL(root2);
    //SkipString();

    //AskUserForDeletionLoopL(root2);
    //SkipString();

#pragma endregion


//#pragma region Задание 3
//    
//    // Создаем список в порядке ввода
//    LineArray* headInputOrder = CreateList();
//
//    // Сортируем список по псевдониму
//    LineArray* headNickname = SortListByNickname(headInputOrder);
//
//    // Сортируем список по количеству слушателей
//    LineArray* headListeners = SortListByListeners(headInputOrder);
//
//    // Выводим списки
//    PrintList(headInputOrder, "порядке ввода");
//    PrintList(headNickname, "увеличению псевдонима");
//    PrintList(headListeners, "увеличению количества слушателей");
//    SkipString();
//
//    PerformOperations(current_ARR_LEN, headNickname, headListeners);
//
//#pragma endregion

}
