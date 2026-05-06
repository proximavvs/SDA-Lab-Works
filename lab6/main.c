#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "tree.h"

int main() {
    Worker *workers = NULL;
    int count = 0;
    int capacity = 0;
    int choice;

    Node *root = NULL;

    printf("Попытка загрузить данные из файла '%s'...\n", DEFAULT_FILE);
    loadFromFile(DEFAULT_FILE, &workers, &count, &capacity);

    // заполняем дерево из массива
    for (int i = 0; i < count; i++) {
        root = insertNode(root, workers[i]);
    }

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
        printf("11. Обход дерева (inorder)\n");
        printf("12. Обход дерева (preorder)\n");
        printf("13. Обход дерева (postorder)\n");
        printf("14. Поиск в дереве по ФИО\n");
        printf("15. Удалить узел дерева\n");
        printf("16. Минимальный элемент\n");
        printf("17. Максимальный элемент\n");
        printf("18. Высота дерева\n");
        printf("19. Сохранить дерево в файл\n");
        printf("0. Выход (с автосохранением)\n");
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
                root = insertNode(root, workers[count]); // добавляем в дерево
                count++;
                break;

            case 2:
                printAllWorkers(workers, count);
                break;

            case 3:
                deleteLastWorker(&count);
                printf("Дерево НЕ обновляется\n");
                break;

            case 4:
                editWorker(workers, count);
                printf("Дерево НЕ обновляется\n");
                break;

            case 5:
                searchByPosition(workers, count);
                break;

            case 6:
                sortWorkers(workers, count);
                break;

            case 7:
                insertWorkerAtPosition(&workers, &count, &capacity);
                printf("Дерево НЕ обновляется\n");
                break;

            case 8:
                deleteWorkerByIndex(workers, &count);
                printf("Дерево НЕ обновляется\n");
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

                // пересобираем дерево
                freeTree(root);
                root = NULL;
                for (int i = 0; i < count; i++) {
                    root = insertNode(root, workers[i]);
                }

                break;
            }

            case 11:
                inorder(root);
                break;

            case 12:
                preorder(root);
                break;

            case 13:
                postorder(root);
                break;

            case 14: {
                char key[100];
                printf("Введите ФИО: ");
                scanf(" %[^\n]", key);

                Node *found = searchNode(root, key);
                if (found)
                    printWorker(found->data, 0);
                else
                    printf("Не найден\n");

                break;
            }

            case 15: {
                char key[100];

                printf("Введите ФИО для удаления: ");
                scanf(" %[^\n]", key);

                root = deleteNode(root, key);

                printf("Узел удалён\n");
                break;
            }

            case 16: {
                Node *min = findMin(root);

                if (min)
                    printWorker(min->data, 0);
                else
                    printf("Дерево пустое\n");

                break;
            }

            case 17: {
                Node *max = findMax(root);

                if (max)
                    printWorker(max->data, 0);
                else
                    printf("Дерево пустое\n");

                break;
            }

            case 18:
                printf("Высота дерева: %d\n", treeHeight(root));
                break;

            case 19: {

                FILE *f = fopen("tree.txt", "w");

                if (!f) {
                    printf("Ошибка открытия файла\n");
                    break;
                }

                saveTreeToFile(root, f);

                fclose(f);

                printf("Дерево сохранено в tree.txt\n");
                break;
            }

            case 0:
                printf("Сохранение перед выходом...\n");
                saveToFile(DEFAULT_FILE, workers, count);
                break;

            default:
                printf("Неверный выбор.\n");
        }

    } while (choice != 0);

    free(workers);
    deleteWholeTree(root);

    return 0;
}