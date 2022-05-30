#include <iostream>
#include "queue.h"
#include "tests.h"
#include "individualTask.h"
#include "menu_functions.h"

/*
    Task: in queue find max elements and delete them
*/

int main() {
    Queue queue;    
    Direction view_direction = Direction::FRONT; // set directions for view (from head -> tail or from tail -> head)

    while (true) {
        system("cls");

        ShowMenuHeader(queue, view_direction);
        int choice = CheckNum();

        switch (choice) {
            case 0: {
                RunTests();
                break;
            }
            case 1: case 2: case 3: {
                Push(queue, choice);
                break;
            }
            case 4: {
                SwapViewDirection(view_direction);
                continue;
            }
            case 5: {
                // Чтобы не срабатывало system("pause"), если захотел вернуться на предыдущий шаг.
                if (!Pop(queue))
                    continue;

                break;
            }
            case 6: {
                queue.clear(false);
                break;
            }
            case 7: {
                queue.sort();
                break;
            }
            case 8: {
                try {
                    queue.pop(FindMax(queue));
                }
                catch (std::runtime_error& e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }
            default: {
                std::cout << std::setw(50) << std::right << "Bye!\n";
                return 0;
            }
        }
        std::cout << '\n';
        system("pause");
    }
    return 0;
}
