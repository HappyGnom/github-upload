#include <windows.h>
#include <cwchar>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <iomanip>

void mixUp(std::vector<std::string> &VtoMix)
{
    static auto rng = std::default_random_engine{};
    rng.seed(time(0));
    std::shuffle(std::begin(VtoMix), std::end(VtoMix), rng);
}

void chooseTask()
{
    std::ifstream task;
    std::string taskName;

    std::cout << " Enter task name : ";
    std::cin >> taskName;
    task.open(".\\Tasks\\" + taskName + ".cpp");

    if (!task.is_open())
    {
        std::cout << " Whoops! Invalid task name\n ";
        system("pause");
        return;
    }

    std::vector<std::string> original;
    std::vector<std::string> copy;
    std::string str;

    while (std::getline(task, str, '\n'))
    {
        original.push_back(str);
    }

    copy = original;
    bool retry = true;

    while (retry)
    {
        mixUp(copy);

        std::string option;
        int selectedOne = 0, selectedTwo = 0;
        while (true)
        {
            system("CLS");
            std::cout << " Write numbers to choose lines. Write \"enter\" when finished\n\n";
            for (int i = 0; i < copy.size(); i++)
            {
                if (selectedOne != 0 && i == selectedOne - 1)
                {
                    //char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
                    std::cout << ' ' << std::setw(2) << i + 1 << "| ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    std::cout << copy.at(i) << '\n';
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    continue;
                }
                std::cout << ' ' << std::setw(2) << i + 1 << "| " << copy.at(i) << '\n';
            }
            std::cout << "\n ";
            std::getline(std::cin, option, '\n');
            if (option == "enter")
            {
                break;
            }
            else
            {
                try
                {
                    if (selectedOne == 0)
                    {
                        selectedOne = std::stoi(option);
                        if (selectedOne > copy.size() || selectedOne <= 0)
                            selectedOne = 0;
                    }
                    else
                    {
                        selectedTwo = std::stoi(option);
                        if (selectedOne > copy.size() || selectedOne <= 0)
                        {
                            selectedTwo = 0;
                            break;
                        }
                        std::swap(copy[selectedOne - 1], copy[selectedTwo - 1]);
                        selectedOne = selectedTwo = 0;
                    }
                }
                catch (...)
                {
                    ;
                }
            }
        }
        retry = false;

        if (copy == original)
        {
            MessageBox(NULL, TEXT("Well Done!"), TEXT("Result"), MB_OK | MB_APPLMODAL | MB_ICONASTERISK);
        }
        else
        {
            if (MessageBox(NULL, TEXT("Wrong!"), TEXT("Result"), MB_RETRYCANCEL | MB_ICONSTOP | MB_APPLMODAL) == IDRETRY)
                retry = true;
        }
    }
    task.close();
}

int main()
{
    char option;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

    while (true)
    {
        system("CLS");

        std::cout << "\tMain Menu\n";
        std::cout << " 1. Choose a task\n";
        std::cout << " 2. Exit\n ";

        std::cin >> option;
        std::cin.ignore(100, '\n');

        system("CLS");

        switch (option)
        {
        case '1':
            chooseTask();
            break;
        case '2':
            exit(0);
            break;
        default:
            std::cout << " Wrong option\n ";
            break;
        }
    }

    return 0;
}
