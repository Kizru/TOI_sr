#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#define ARR_LEN 1 //инструкция предпроцессору заменить при компеляции ARR_LEN на 1

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
        std::cout << std::endl;
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
    int position; //идекс в массиве Musician
};

struct ListenersCountIndex
{
    int listenersCount;
    int position; //идекс в массиве Musician
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

//вывод массива с удаленными элементами
void PrintRedactedMusicians() 
{
    bool isAllDeleted = true;

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
        std::cout << std::endl;
        PrintLine();
        std::cout << "Полученный массив";
        std::cout << std::endl;

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
        std::cout << std::endl;
        PrintLine();
        std::cout << "В массиве не осталось элементов";
        std::cout << std::endl;
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
            std::cout << std::endl;
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
    NickNameIndexSort();
    if (ARR_LEN % 2 != 0)
    {
        for (int i = 0; i < ARR_LEN / 2; i++)
        {
            swap = nicknameIndexes[i];
            nicknameIndexes[i] = nicknameIndexes[ARR_LEN - i - 1];
            nicknameIndexes[ARR_LEN - i - 1] = swap;
        }
    }

    else
    {
        for (int i = 0; i <= ARR_LEN / 2; i++)
        {
            swap = nicknameIndexes[i];
            nicknameIndexes[i] = nicknameIndexes[ARR_LEN - i - 1];
            nicknameIndexes[ARR_LEN - i - 1] = swap;
        }
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
    std::cout << std::endl;
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
    ListenersCountIndexSort();
    if (ARR_LEN % 2 != 0)
    {
        for (int i = 0; i < ARR_LEN / 2; i++)
        {
            swap =  listenersIndexes[i];
            listenersIndexes[i] = listenersIndexes[ARR_LEN - i - 1];
            listenersIndexes[ARR_LEN - i - 1] = swap;
        }
    }

    else
    {
        for (int i = 0; i <= ARR_LEN / 2; i++)
        {
            swap = listenersIndexes[i];
            listenersIndexes[i] = listenersIndexes[ARR_LEN - i - 1];
            listenersIndexes[ARR_LEN - i - 1] = swap;
        }
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
    std::cout << std::endl;
    int number = AskNumber();
    std::cout << std::endl;
    int result = ListenersCountBinSerch(0, ARR_LEN - 1, number);

    if (result == -1) 
    { 
        std::cout << std::endl;
        std::cout << "Значение не найдено" << std::endl; 
    }

    else 
    {
        std::cout << "Псевдоним исполнителя: " << musicians[listenersIndexes[result].position].nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << musicians[listenersIndexes[result].position].realName << std::endl;
        std::cout << "Лейбл исполнителя: " << musicians[listenersIndexes[result].position].label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[listenersIndexes[result].position].listenersCount << std::endl;
    }

    PrintLine();
    std::cout << std::endl;
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
    bool isConverted = false;

    if (answer == '+')
    {
        while (answer == '+')
        {
            int number = ListenersPosition();
            std::cout << std::endl;

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
            std::cout << "Введите количество прослушиваний, по которому будет произведено удаление: ";
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
    int remainigElements = ARR_LEN; //кол-во не удаленных элементов

    while ((answer == '+') && (remainigElements != 0))
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

        remainigElements -= 1;
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

//struct ListenersBenTree
//{
//    uint64_t listeners;
//    int index; // Индекс элемента в массиве
//    NickNameBenTreeNode* left;
//    NickNameBenTreeNode* right;
//
//    ListenersBenTree(uint64_t listeners, int idx) : listeners(listeners), index(idx), left(nullptr), right(nullptr) {}
//};

#pragma endregion

#pragma region NickName

#pragma region Создание и заполнение

//создание и расположение узлов в дереве
NickNameBenTreeNode* FillNicknameTree(NickNameBenTreeNode* link, int index)
{
    //создание узла
    if (link == nullptr)
    {
        NickNameBenTreeNode* node = new NickNameBenTreeNode(musicians[index].nickname, index);
        return node;
    }

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

    return link;
}

//само построение дерева
NickNameBenTreeNode* CreateNickNameTree()
{
    NickNameBenTreeNode* root = nullptr;

    for (int i = 0; i < ARR_LEN; i++)
    {
        root = FillNicknameTree(root, i); // root нужно обновлять
    }
    return root;
}

#pragma endregion

#pragma region Вывод

// Вспомогательная рекурсивная функция для вывода дерева в виде таблицы
void printNode(NickNameBenTreeNode* node) {
    if (node != nullptr) {
        printNode(node->left); // Сначала левое поддерево

        int index = node->index; // Получаем индекс музыканта

        // Вывод данных в формате таблицы
        std::cout << std::left << std::setw(6) << index+1
            << std::setw(12) << musicians[index].nickname
            << std::setw(15) << musicians[index].realName 
            << std::setw(10) << musicians[index].label
            << std::setw(10) << musicians[index].listenersCount << std::endl;

        printNode(node->right); // Затем правое поддерево
    }
}

// Функция для вывода дерева в виде таблицы
void printNicknameTreeTable(NickNameBenTreeNode* root) {
    if (root == nullptr) return;

    // Шапка таблицы
    SkipString();
    std::cout << std::left << std::setw(6) << "Номер"
        << std::setw(12) << "Псевдоним"
        << std::setw(15) << "Настоящее имя"
        << std::setw(10) << "Лейбл"
        << std::setw(10) << "Количество слушателей" << std::endl;

    printNode(root); // Начинаем обход с корня
}

#pragma endregion

#pragma region Рекурсивнный бинарный поиск

// Функция запроса поиска
void performSearch(NickNameBenTreeNode* root) 
{
    std::string searchNickname;
    std::cout << "Введите псевдоним для поиска: ";
    std::cin >> searchNickname;

    std::cout << "Рекурсивный поиск:" << std::endl;
    recursiveSearch(root, searchNickname);
}

// Функция для управления циклом поиска
void searchLoop(NickNameBenTreeNode* root) {
    char continueSearch = '+';

    while (continueSearch == '+') 
    {
        performSearch(root); // Вызываем функцию performSearch

        std::cout << "Продолжаем поиск? (+/-): ";
        std::cin >> continueSearch;
    }
}

//сам поиск
void recursiveSearch(NickNameBenTreeNode* root, const std::string& targetNickname) {
    if (root == nullptr)
    {
        std::cout << "Музыкант с псевдонимом '" << targetNickname << "' не найден" << std::endl;
        return;
    }

    if (targetNickname == root->nickname) {
        int index = root->index;

        std::cout << "Псевдоним исполнителя: " << musicians[index].nickname << std::endl;
        std::cout << "Настоящее имя исполнителя: " << musicians[index].realName << std::endl;
        std::cout << "Лейбл исполнителя: " << musicians[index].label << std::endl;
        std::cout << "Количество слушателей в месяц у исполнителя: " << musicians[index].listenersCount << std::endl;
        return;
    }
    else if (targetNickname < root->nickname) {
        recursiveSearch(root->left, targetNickname);
    }
    else {
        recursiveSearch(root->right, targetNickname);
    }
}

#pragma endregion

#pragma endregion

#pragma endregion


int main()
{
    setlocale(LC_ALL, "Russian");
    FillMusicians();
    //PrintMusicians();

//#pragma region Задание 1
//
//    SkipString();
//    CreateNicknameIndex();
//    //NickNameIndexSort();
//    PrintNicknameIndexes();
//    //NickNameBinSearch();
//    //NicknameEdit();
//    NicknameDelition();
//    PrintRedactedMusicians();
//
//    /*SkipString();
//    NickNameIndexReversedSort();
//    PrintNicknameIndexes();*/
//
//
//    SkipString();
//    CreateListenersCountIndex();
//    //ListenersCountIndexSort();
//    PrintListenersCountIndexes();
//    //ListenersCountBinSerchRealise();
//    //ListenersEdit();
//    ListenersDelition();
//    PrintRedactedMusicians();
//
//    /*SkipString();
//    ListenersCountIndexReversedSort();
//    PrintListenersCountIndexes();*/
//
//#pragma endregion

#pragma region Задание 2

    NickNameBenTreeNode* root = CreateNickNameTree(); //создание дерева
    std::cout << "Бинарное дерево, построенное по псевдониму исполнителя:" << std::endl;
    printNicknameTreeTable(root);
    SkipString();

    searchLoop(root);

#pragma endregion

}
