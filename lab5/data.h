#ifndef DATA_H
#define DATA_H

#define DEFAULT_FILE "workers.txt"

typedef struct {
    char fio[100];
    char position[50];
    float salary;
    int shipped_goods;
} Worker;

void inputWorker(Worker *w);
void printWorker(Worker w, int index);
void printAllWorkers(Worker *workers, int count);

Worker* expandArray(Worker *workers, int oldSize, int newSize);

void editWorker(Worker *workers, int count);
void deleteWorkerByIndex(Worker *workers, int *count);
void deleteLastWorker(int *count);
void insertWorkerAtPosition(Worker **workers, int *count, int *capacity);

void searchByPosition(Worker *workers, int count);
void sortWorkers(Worker *workers, int count);

int  saveToFile(const char *filename, Worker *workers, int count);
int  loadFromFile(const char *filename, Worker **workers, int *count, int *capacity);

#endif // DATA_H