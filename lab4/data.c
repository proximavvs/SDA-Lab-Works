#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


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
    if (count == 0) { printf("Список пуст.\n"); return; }

    int index;
    printf("Введите индекс работника: ");
    scanf("%d", &index);

    if (index < 0 || index >= count) { printf("Неверный индекс.\n"); return; }

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

void insertWorkerAtPosition(Worker **workers, int *count, int *capacity) {
    int index;
    printf("Введите позицию для вставки (от 0 до %d): ", *count);
    scanf("%d", &index);

    if (index < 0 || index > *count) { printf("Неверная позиция.\n"); return; }

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
    if (*count == 0) { printf("Список пуст.\n"); return; }

    int index;
    printf("Введите индекс для удаления: ");
    scanf("%d", &index);

    if (index < 0 || index >= *count) { printf("Неверный индекс.\n"); return; }

    for (int i = index; i < *count - 1; i++) {
        workers[i] = workers[i + 1];
    }
    (*count)--;
    printf("Работник удалён.\n");
}

void deleteLastWorker(int *count) {
    if (*count == 0) { printf("Список пуст.\n"); return; }
    (*count)--;
    printf("Последний работник удалён.\n");
}


void searchByPosition(Worker *workers, int count) {
    if (count == 0) { printf("Список пуст.\n"); return; }

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
    if (!found) printf("Работники с такой должностью не найдены.\n");
}

void sortWorkers(Worker *workers, int count) {
    if (count == 0) { printf("Список пуст.\n"); return; }

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
                case 1: needSwap = strcmp(workers[j].fio, workers[j+1].fio) > 0; break;
                case 2: needSwap = strcmp(workers[j].position, workers[j+1].position) > 0; break;
                case 3: needSwap = workers[j].salary > workers[j+1].salary; break;
                case 4: needSwap = workers[j].shipped_goods > workers[j+1].shipped_goods; break;
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


int saveToFile(const char *filename, Worker *workers, int count) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Ошибка: не удалось открыть файл '%s' для записи.\n", filename);
        return 0;
    }

    if (fwrite(&count, sizeof(int), 1, f) != 1) {
        printf("Ошибка записи количества записей.\n");
        fclose(f);
        return 0;
    }

    if (count > 0) {
        size_t written = fwrite(workers, sizeof(Worker), count, f);
        if ((int)written != count) {
            printf("Ошибка: записано %zu из %d работников.\n", written, count);
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    printf("Данные сохранены в файл '%s' (%d записей).\n", filename, count);
    return 1;
}

int loadFromFile(const char *filename, Worker **workers, int *count, int *capacity) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Файл '%s' не найден. Начинаем с пустого списка.\n", filename);
        return 0;
    }

    int savedCount = 0;
    if (fread(&savedCount, sizeof(int), 1, f) != 1) {
        printf("Ошибка чтения файла '%s'.\n", filename);
        fclose(f);
        return 0;
    }

    if (savedCount < 0) {
        printf("Файл повреждён (отрицательное количество записей).\n");
        fclose(f);
        return 0;
    }

    if (savedCount == 0) {
        printf("Файл '%s' пуст.\n", filename);
        fclose(f);
        return 1;
    }

    Worker *newArray = (Worker*)malloc(savedCount * sizeof(Worker));
    if (newArray == NULL) {
        printf("Ошибка выделения памяти при загрузке.\n");
        fclose(f);
        return 0;
    }

    size_t readCount = fread(newArray, sizeof(Worker), savedCount, f);
    fclose(f);

    if ((int)readCount != savedCount) {
        printf("Ошибка: прочитано %zu из %d записей.\n", readCount, savedCount);
        free(newArray);
        return 0;
    }

    free(*workers);
    *workers   = newArray;
    *count     = savedCount;
    *capacity  = savedCount;

    printf("Загружено %d работников из файла '%s'.\n", savedCount, filename);
    return 1;
}
