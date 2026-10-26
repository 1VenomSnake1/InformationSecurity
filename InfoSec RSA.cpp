#include <iostream>
#include <cmath>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;
using namespace std;

bool Euclid(cpp_int a, cpp_int b) {

    if (a < b) {
        cpp_int temp = a;
        a = b;
        b = temp;
    }


    cpp_int last = a;
    cpp_int a1 = a, b1 = b;
    while (last != 0) {
        last = a1 % b1;
        a1 = b1;
        b1 = last;
    }

    if (a1 == 1)
    {
        cout << "Числа " << a << " и " << b << " взаимно простые" << endl;
        return 1;
    }
    else
    {
        cout << "НОД чисел " << a << " и " << b << " равен: " << a1 << endl;
        return 0;
    }
    
}

cpp_int ExtendedEuclid(cpp_int a, cpp_int b) {
    cpp_int q;
    if (a < b) {
        cpp_int temp = a;
        a = b;
        b = temp;
    }

    cpp_int last = a;
    cpp_int a1 = a, b1 = b;
    cpp_int x1 = 1, y1 = 0;
    cpp_int x2 = 0, y2 = 1;
    while (last != 0) {
        q = a1 / b1;
        last = a1 % b1;
        cpp_int xnew = x1 - q * x2;
        cpp_int ynew = y1 - q * y2;
        a1 = b1;
        b1 = last;
        x1 = x2; x2 = xnew;
        y1 = y2; y2 = ynew;
    }
    cout << "Коэффициенты для " << a << " и " << b << " равны: x = " << x1 << ", y = " << y1 << endl;
    return y1;
}

bool Simple (long long a)
{
    switch (a)
    {
    case 1:
        return 0;
    default:
            for (cpp_int i = 2; i < a; i++)
            {
                if (a % i == 0) return 0;
            }
        return 1;
    }
}

cpp_int BV (cpp_int x, cpp_int n)
{
    cpp_int result = 1;
    
    do
    {
        if (n % 2 == 1)
            result *= x;
        x *= x;
        n /= 2;
    } while (n > 0);

    return result;
}

void RSA(vector<cpp_int> &M, vector<cpp_int> &C, vector<cpp_int> &open, vector<cpp_int> &close, int size)
{
    for (int i = 0; i < size; i++)
    {
        C[i] = BV(M[i], open[0]) % open[1];
    }
}


void RSAcheck(vector<cpp_int>& M, vector<cpp_int>& C, vector<cpp_int>& open, vector<cpp_int>& close, int size) 
{
    for (int i = 0; i < size; i++)
    {
        cout << "Шифрока: C[" << i <<"] = (M[" << i<<"]^open[0]) mod open[1] = (" << M[i] <<"^"<<open[0] << " mod " << open[1] <<" = " << BV(M[i], open[0]) % open[1] << endl;
        cout << "Расшифровка: M[" << i << "] = (C[" << i << "]^close[0]) mod close[1] = (" << M[i] << "^" << close[0] << " mod " << close[1] << " = " << BV(C[i], close[0]) % close[1] << endl;
    }
}

int main()
{
	setlocale(LC_ALL, "RU");
    long long p, q;
    cout << "Введите два числа различных простых чилса p и q: " << endl;
    cout << "p = "; cin >> p;
    cout << "q = "; cin >> q;
    if (p == q) {
        cout << "Числа одинаковые! END OF THE LINE";
        exit(0);
    }
    switch (Simple(p)*Simple(q)) //проверка на простоту чисел
    {
    case 0:
        cout << "Одно из чисел не простое! END OF THE LINE";
        exit(0);
    default:
        break;
    }

    cpp_int n = p * q; cout << "n = " << n << endl;
    cpp_int phi = (p - 1) * (q - 1); cout << "phi = " << phi << endl;

    
    //

    cpp_int e; cout << "Введите e (e удовлетворяет: {3, phi-1}; нечётное; взаимно простое число с phi)" << endl; cin >> e;
    while ((Euclid(phi, e) != 1) && (e % 2 != 0)) //выбор e
    {
        cout << "Неправильное e, выберите другое" << endl;
        cin >> e;
    }

    cpp_int d = ((ExtendedEuclid(phi, e) % phi) + phi) % phi; //высчит с нормализацей числа "d"
    //

    vector<cpp_int> open = { e, n }, close = { d, n };
    cout <<"открытый ключ { " << open[0] << " ; " << open[1] << " } " <<endl <<"закрытый ключ { "<< close[0] << " ; " << close[1] <<" }" << endl;

    int size;
    cout << "Введите размер массива: ";  cin >> size;
    vector<cpp_int> C(size), M(size);

    cout << "Вводите исходные десятичные числа не больше n" << endl;
    for (int i = 0; i < size; i++)
    {
        cin >> M[i];
    }
    RSA(M, C, open, close, size);

    for (int i = 0; i < size; i++)
    {
        cout << "С[" << i << "] = " << C[i] << " ; M[" <<i<<"] = " << M[i] << endl << endl;
    }
    RSAcheck(M, C, open, close, size);
}