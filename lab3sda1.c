#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fio[100];
    char position[50];
    float salary;
    int shipped_goods;
} Worker;

void inputWorker(Worker *w) {
    printf("ФИО: ");
    scanf(" %[^\n]", w->fio);

    printf("Должность: ");
    scanf(" %[^\n]", w->position);

    printf("Зарплата: ");
    scanf("%f", &w->salary);

    printf("Количество отгруженных товаров: ");
    scanf("%d", &w->shipped_goods);
}

void printWorker(Worker w, int index) {
    printf("\nРаботник #%d\n", index);
    printf("ФИО: %s\n", w.fio);
    printf("Должность: %s\n", w.position);
    printf("Зарплата: %.2f\n", w.salary);
    printf("Отгружено: %d\n", w.shipped_goods);
}

void printAllWorkers(Worker *workers, int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printWorker(workers[i], i);
    }
}

Worker* expandArray(Worker *workers, int oldSize, int newSize) {
    Worker *newArray = (Worker*)malloc(newSize * sizeof(Worker));

    if (newArray == NULL) {
        printf("Ошибка выделения памяти.\n");
        exit(1);
    }

    for (int i = 0; i < oldSize; i++) {
        newArray[i] = workers[i];
    }

    free(workers);
    return newArray;
}

void editWorker(Worker *workers, int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    int index;
    printf("Введите индекс работника: ");
    scanf("%d", &index);

    if (index < 0 || index >= count) {
        printf("Неверный индекс.\n");
        return;
    }

    int fieldChoice;

    printf("\nЧто редактировать?\n");
    printf("1. ФИО\n");
    printf("2. Должность\n");
    printf("3. Зарплату\n");
    printf("4. Количество отгруженных товаров\n");
    printf("Выбор: ");
    scanf("%d", &fieldChoice);

    switch (fieldChoice) {
        case 1:
            printf("Новое ФИО: ");
            scanf(" %[^\n]", workers[index].fio);
            break;
        case 2:
            printf("Новая должность: ");
            scanf(" %[^\n]", workers[index].position);
            break;
        case 3:
            printf("Новая зарплата: ");
            scanf("%f", &workers[index].salary);
            break;
        case 4:
            printf("Новое количество: ");
            scanf("%d", &workers[index].shipped_goods);
            break;
        default:
            printf("Неверный выбор.\n");
    }
}

void searchByPosition(Worker *workers, int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    char key[50];
    int found = 0;

    printf("Введите должность для поиска: ");
    scanf(" %[^\n]", key);

    for (int i = 0; i < count; i++) {
        if (strcmp(workers[i].position, key) == 0) {
            printWorker(workers[i], i);
            found = 1;
        }
    }

    if (!found) {
        printf("Работники с такой должностью не найдены.\n");
    }
}

void insertWorkerAtPosition(Worker **workers, int *count, int *capacity) {
    int index;

    printf("Введите позицию для вставки (от 0 до %d): ", *count);
    scanf("%d", &index);

    if (index < 0 || index > *count) {
        printf("Неверная позиция.\n");
        return;
    }

    if (*count == *capacity) {
        int newCapacity = *capacity + 1;
        *workers = expandArray(*workers, *capacity, newCapacity);
        *capacity = newCapacity;
    }

    for (int i = *count; i > index; i--) {
        (*workers)[i] = (*workers)[i - 1];
    }

    printf("Введите данные нового работника:\n");
    inputWorker(&((*workers)[index]));
    (*count)++;

    printf("Работник успешно вставлен.\n");
}

void deleteWorkerByIndex(Worker *workers, int *count) {
    if (*count == 0) {
        printf("Список пуст.\n");
        return;
    }

    int index;
    printf("Введите индекс для удаления: ");
    scanf("%d", &index);

    if (index < 0 || index >= *count) {
        printf("Неверный индекс.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        workers[i] = workers[i + 1];
    }

    (*count)--;
    printf("Работник удалён.\n");
}

void sortWorkers(Worker *workers, int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    int fieldChoice;
    printf("\nСортировать по:\n");
    printf("1. ФИО\n");
    printf("2. Должности\n");
    printf("3. Зарплате\n");
    printf("4. Количеству отгруженных товаров\n");
    printf("Выбор: ");
    scanf("%d", &fieldChoice);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int needSwap = 0;

            switch (fieldChoice) {
                case 1:
                    if (strcmp(workers[j].fio, workers[j + 1].fio) > 0)
                        needSwap = 1;
                    break;
                case 2:
                    if (strcmp(workers[j].position, workers[j + 1].position) > 0)
                        needSwap = 1;
                    break;
                case 3:
                    if (workers[j].salary > workers[j + 1].salary)
                        needSwap = 1;
                    break;
                case 4:
                    if (workers[j].shipped_goods > workers[j + 1].shipped_goods)
                        needSwap = 1;
                    break;
                default:
                    printf("Неверный выбор поля.\n");
                    return;
            }

            if (needSwap) {
                Worker temp = workers[j];
                workers[j] = workers[j + 1];
                workers[j + 1] = temp;
            }
        }
    }

    printf("Сортировка выполнена.\n");
}

void deleteLastWorker(int *count) {
    if (*count == 0) {
        printf("Список пуст.\n");
        return;
    }

    (*count)--;
    printf("Последний работник удалён.\n");
}

int main() {
    Worker *workers = NULL;
    int count = 0;
    int capacity = 0;
    int choice;

    do {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Добавить работника в конец\n");
        printf("2. Показать всех\n");
        printf("3. Удалить последнего\n");
        printf("4. Редактировать по индексу\n");
        printf("5. Поиск по должности\n");
        printf("6. Сортировка\n");
        printf("7. Вставить работника на позицию\n");
        printf("8. Удалить работника по индексу\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (count == capacity) {
                    int newCapacity = capacity + 1;
                    workers = expandArray(workers, capacity, newCapacity);
                    capacity = newCapacity;
                }
                inputWorker(&workers[count]);
                count++;
                break;

            case 2:
                printAllWorkers(workers, count);
                break;

            case 3:
                deleteLastWorker(&count);
                break;

            case 4:
                editWorker(workers, count);
                break;

            case 5:
                searchByPosition(workers, count);
                break;

            case 6:
                sortWorkers(workers, count);
                break;

            case 7:
                insertWorkerAtPosition(&workers, &count, &capacity);
                break;

            case 8:
                deleteWorkerByIndex(workers, &count);
                break;

            case 0:
                printf("Выход из программы.\n");
                break;

            default:
                printf("Неверный выбор.\n");
        }

    } while (choice != 0);

    free(workers);
    return 0;
