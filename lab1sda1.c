#include <stdio.h>
#include <string.h>

#define SIZE 10

typedef struct {
    char fio[100];
    char position[50];
    float salary;
    int shipped_goods;
} Worker;

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
    } else {
        buf[0] = '\0';
    }
}

void inputWorker(Worker *w) {
    printf("Введите ФИО: ");
    readLine(w->fio, (int)sizeof(w->fio));

    printf("Введите должность: ");
    readLine(w->position, (int)sizeof(w->position));

    printf("Введите зарплату: ");
    while (scanf("%f", &w->salary) != 1) {
        printf("Ошибка ввода. Введите число (например 12500.50): ");
        clearInput();
    }
    clearInput();

    printf("Введите количество отгруженных товаров: ");
    while (scanf("%d", &w->shipped_goods) != 1) {
        printf("Ошибка ввода. Введите целое число: ");
        clearInput();
    }
    clearInput();
}

void printWorker(const Worker *w, int index) {
    printf("\n--- Работник #%d ---\n", index);
    printf("ФИО: %s\n", w->fio);
    printf("Должность: %s\n", w->position);
    printf("Зарплата: %.2f\n", w->salary);
    printf("Отгружено товаров: %d\n", w->shipped_goods);
}

void printAll(const Worker workers[], int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printWorker(&workers[i], i);
    }
}

void editWorker(Worker *w) {
    int choice;
    printf("\nЧто редактировать?\n");
    printf("1) ФИО\n");
    printf("2) Должность\n");
    printf("3) Зарплата\n");
    printf("4) Количество отгруженных товаров\n");
    printf("Выбор: ");

    if (scanf("%d", &choice) != 1) {
        clearInput();
        printf("Неверный ввод.\n");
        return;
    }
    clearInput();

    switch (choice) {
        case 1:
            printf("Новое ФИО: ");
            readLine(w->fio, (int)sizeof(w->fio));
            break;
        case 2:
            printf("Новая должность: ");
            readLine(w->position, (int)sizeof(w->position));
            break;
        case 3:
            printf("Новая зарплата: ");
            while (scanf("%f", &w->salary) != 1) {
                printf("Ошибка ввода. Введите число: ");
                clearInput();
            }
            clearInput();
            break;
        case 4:
            printf("Новое количество отгруженных товаров: ");
            while (scanf("%d", &w->shipped_goods) != 1) {
                printf("Ошибка ввода. Введите целое число: ");
                clearInput();
            }
            clearInput();
            break;
        default:
            printf("Неверный пункт.\n");
    }
}

void searchByPosition(const Worker workers[], int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    char pos[50];
    int found = 0;

    printf("Введите должность для поиска: ");
    readLine(pos, (int)sizeof(pos));

    for (int i = 0; i < count; i++) {
        if (strcmp(workers[i].position, pos) == 0) {
            printWorker(&workers[i], i);
            found = 1;
        }
    }

    if (!found) {
        printf("Работники с должностью \"%s\" не найдены.\n", pos);
    }
}

void searchByFIO(const Worker workers[], int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    char name[100];
    printf("Введите ФИО для поиска: ");
    readLine(name, (int)sizeof(name));

    for (int i = 0; i < count; i++) {
        if (strcmp(workers[i].fio, name) == 0) {
            printWorker(&workers[i], i);
            return;
        }
    }
    printf("Работник не найден.\n");
}

int main(void) {
    Worker workers[SIZE];
    int count = 0;
    int choice;

    do {
        printf("\n======= МЕНЮ =======\n");
        printf("1) Добавить работника\n");
        printf("2) Показать всех работников\n");
        printf("3) Редактировать работника по индексу\n");
        printf("4) Поиск по ФИО\n");
        printf("5) Поиск по должности\n");
        printf("0) Выход\n");
        printf("Выбор: ");

        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Неверный ввод. Попробуйте снова.\n");
            continue;
        }
        clearInput();

        switch (choice) {
            case 1:
                if (count >= SIZE) {
                    printf("Нельзя добавить: массив заполнен (макс %d).\n", SIZE);
                } else {
                    inputWorker(&workers[count]);
                    count++;
                    printf("Работник добавлен.\n");
                }
                break;

            case 2:
                printAll(workers, count);
                break;

            case 3: {
                int index;
                if (count == 0) {
                    printf("Список пуст.\n");
                    break;
                }
                printf("Введите индекс (0..%d): ", count - 1);
                if (scanf("%d", &index) != 1) {
                    clearInput();
                    printf("Неверный ввод.\n");
                    break;
                }
                clearInput();

                if (index < 0 || index >= count) {
                    printf("Неверный индекс.\n");
                } else {
                    editWorker(&workers[index]);
                }
                break;
            }

            case 4:
                searchByFIO(workers, count);
                break;

            case 5:
                searchByPosition(workers, count);
                break;

            case 0:
                printf("Выход...\n");
                break;

            default:
                printf("Нет такого пункта меню.\n");
        }

    } while (choice != 0);

    return 0;
}