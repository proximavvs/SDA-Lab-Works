#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main() {
    Worker *workers = NULL;
    int count    = 0;
    int capacity = 0;
    int choice;

    printf("Попытка загрузить данные из файла '%s'...\n", DEFAULT_FILE);
    loadFromFile(DEFAULT_FILE, &workers, &count, &capacity);

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
        printf("9. Сохранить в файл\n");
        printf("10. Загрузить из файла\n");
        printf("0. Выход (с автосохранением)\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (count == capacity) {
                    int newCapacity = capacity + 1;
                    workers  = expandArray(workers, capacity, newCapacity);
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

            case 9: {
                char fname[256];
                printf("Имя файла [Enter = '%s']: ", DEFAULT_FILE);
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                if (fgets(fname, sizeof(fname), stdin) == NULL || fname[0] == '\n') {
                    saveToFile(DEFAULT_FILE, workers, count);
                } else {
                    int len = 0;
                    while (fname[len] && fname[len] != '\n') len++;
                    fname[len] = '\0';
                    saveToFile(fname, workers, count);
                }
                break;
            }

            case 10: {
                char fname[256];
                printf("Имя файла [Enter = '%s']: ", DEFAULT_FILE);
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                if (fgets(fname, sizeof(fname), stdin) == NULL || fname[0] == '\n') {
                    loadFromFile(DEFAULT_FILE, &workers, &count, &capacity);
                } else {
                    int len = 0;
                    while (fname[len] && fname[len] != '\n') len++;
                    fname[len] = '\0';
                    loadFromFile(fname, &workers, &count, &capacity);
                }
                break;
            }

            case 0:
                printf("Сохранение данных перед выходом...\n");
                saveToFile(DEFAULT_FILE, workers, count);
                printf("Выход из программы.\n");
                break;

            default:
                printf("Неверный выбор.\n");
        }

    } while (choice != 0);

    free(workers);
    return 0;
}
