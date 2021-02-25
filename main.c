#include <stdlib.h>
#include <time.h>
#include <stdio.h>




int swap_count = 0;
int comparation_count = 0;



// Генерирует случайн int побитово беря для каждого бита последний бит rand
int randint(void){
    int num = 0;
    for (int i = 0; i < 8 * sizeof(int); i++){
        num |= (rand() & 1) << i;
    }
    return num;
}

//заполняет массив a длинны n случайными числами
void random_array(int * a, int n){
    for (int i = 0; i < n; i++){
        a[i] = randint();
    }
}


//сравнение чисел по модулю, преобразование в лонг т.к. abs(INT_MIN) > INT_MAX
int less_then(int a, int b){
    comparation_count++;
    long long c = a, d = b;
    c = (c < 0)? -c: c;
    d = (d < 0)? -d: d;
    return c > d;
}

//быстрая сортировка 
void quick_sort(int * a, int n){
    //если в подмассиве меньше 2х элементов то соритровать нечего.
    if (n <= 1){
        return;
    }
    //выбираем опорный элемент (в данном случае средний)
    int mid = a[n/2];
    int left = 0, right = n - 1;
    //цикл пока левый и правый указатель не пересекутся
    do {
        //находим первый левый (правый) элемент который меньше (больше) опорного
        for (; less_then(mid, a[left]) && left < n - 1; left++);
        for (; less_then(a[right], mid) && right >= 0; right--);
        //если нашли такие то меняем их местами если левый действительно левее
        if (left <= right){
            swap_count++;
            int tmp = a[left];
            a[left] = a[right];
            a[right] = tmp;
            left++;
            right--;
        }
    } while (left <= right);


    //запускаем сортировку рекурсивно от подотрезков если есть что сортировать...
    if(right > 0) {
        quick_sort(a, right + 1);
    }
    if (left < n) {
        quick_sort(a + left, n - left);
    } 

}


//сортировка пузырком
void bubble_sort(int * a, int n){
    int current = 0;
    //пока пузырек не "доплыл" до последнего элемента проверяем в правильном ли порядке соритруются элементы
    while (current < n - 1){
        //если элементы в неправильном порядке то меняем их местами и возвращаемся в начало массива
        if (less_then(a[current], a[current + 1])){
            swap_count++;
            int tmp = a[current];
            a[current] = a[current + 1];
            a[current + 1] = tmp;
            current = 0;
        }
        //иначе переходим к следующему элоемнту
        else{
            current++;
        }
    }
}


//проверяет массив на отсортированность
int sort_check(int * a, int n){
    for (int i = 0; i < n - 1; i++){
        if (less_then(a[i],a[i + 1])){
            return 0;
        }
    }
    return 1;
}




int main(void){
    //установка сида rng
    srand(time(NULL));
    //выбор размера массива для теста
    int n = 1000;
    int a[n];
    //создавние массива для теста
    random_array(a,n);
    quick_sort(a,n);
    printf("%d\n", sort_check(a,n));
    printf("%d %d\n", comparation_count,swap_count);
    random_array(a,n);
    comparation_count = 0;
    swap_count = 0;
    bubble_sort(a,n);
    printf("%d\n", sort_check(a,n));
    printf("%d %d\n", comparation_count,swap_count);

    

    return 0;
}