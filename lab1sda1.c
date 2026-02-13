#include <stdio.h>
#include <string.h>

#define SIZE 10

struct Worker {
    char fio[100];
    char position[50];
    float salary;
    int shipped_goods;
};

void inputWorker(struct Worker *w) {
    printf("Введите ФИО: ");
    fgets(w->fio, 100, stdin);
    w->fio[strcspn(w->fio, "\n")] = 0;

    printf("Введите должность: ");
    fgets(w->position, 50, stdin);
    w->position[strcspn(w->position, "\n")] = 0;

    printf("Введите зарплату: ");
    scanf("%f", &w->salary);

    printf("Введите количество отгруженных товаров: ");
    scanf("%d", &w->shipped_goods);
    getchar();
}

void printWorker(struct Worker w, int index) {
    printf("\nРаботник #%d\n", index);
    printf("ФИО: %s\n", w.fio);
    printf("Должность: %s\n", w.position);
    printf("Зарплата: %.2f\n", w.salary);
    printf("Отгружено товаров: %d\n", w.shipped_goods);
}

void editWorker(struct Worker *w) {
    int choice;

    printf("Что редактировать?\n");
    printf("1. ФИО\n2. Должность\n3. Зарплата\n4. Количество товаров\n");
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1:
            printf("Введите новое ФИО: ");
            fgets(w->fio, 100, stdin);
            w->fio[strcspn(w->fio, "\n")] = 0;
            break;
        case 2:
            printf("Введите новую должность: ");
            fgets(w->position, 50, stdin);
            w->position[strcspn(w->position, "\n")] = 0;
            break;
        case 3:
            printf("Введите новую зарплату: ");
            scanf("%f", &w->salary);
            break;
        case 4:
            printf("Введите новое количество товаров: ");
            scanf("%d", &w->shipped_goods);
            break;
        default:
            printf("Неверный выбор.\n");
    }
}

void searchWorker(struct Worker workers[], int count) {
    char searchName[100];
    printf("Введите ФИО для поиска: ");
    getchar();
    fgets(searchName, 100, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    for(int i = 0; i < count; i++) {
        if(strcmp(workers[i].fio, searchName) == 0) {
            printWorker(workers[i], i);
            return;
        }
    }
    printf("Работник не найден.\n");
}

int main() {
    struct Worker workers[SIZE];
    int count = 0;
    int choice, index;

    do {
        printf("\n1. Добавить работника\n");
        printf("2. Показать всех работников\n");
        printf("3. Редактировать работника\n");
        printf("4. Найти работника\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                if(count < SIZE) {
                    inputWorker(&workers[count]);
                    count++;
                } else {
                    printf("Массив заполнен!\n");
                }
                break;
            case 2:
                for(int i = 0; i < count; i++)
                    printWorker(workers[i], i);
                break;
            case 3:
                printf("Введите индекс: ");
                scanf("%d", &index);
                if(index >= 0 && index < count)
                    editWorker(&workers[index]);
                else
                    printf("Неверный индекс.\n");
                break;
            case 4:
                searchWorker(workers, count);
                break;
        }

    } while(choice != 0);

    return 0;
}