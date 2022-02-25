#include <iostream>

using namespace std;

int n = 5, a[5];

class Operations
{
public:
    int Addition(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a; // перемещаем значение а в eax
            add eax, b; // складываем
            mov c, eax; // перемещаем значение eax в с
        }
        return c;
    }

    int Subtraction(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a; // перемещаем значение а в eax
            sub eax, b; // вычитаем
            mov c, eax; // перемещаем значение eax в с
        }
        return c;
    }

    int Multiplication(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            mov ebx, b;
            mul ebx;    // ebx*eax = eax
            mov c, eax;
        }
        return c;
    }

    int Division(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            mov ebx, b;
            mov edx, 0;
            div ebx; // (edx,eax)/ebx = eax, edx; где eax - результат от деления, edx - остаток
            mov c, eax;
        }
        return c;
    }

    int LogNot(int a)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            not eax; // отрицание
            mov c, eax;
        }
        return c;
    }

    int LogAnd(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            mov ebx, b;
            and ebx, eax; // выполняет побитовую операцию И
            mov c, ebx;
        }
        return c;
    }

    int LogOr(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov ebx, a;
            mov eax, b;
            or ebx, eax; // выполняет побитовую операцию ИЛИ
            mov c, ebx;
        }
        return c;
    }

    int LogXor(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov ebx, a;
            mov eax, b;
            xor ebx, eax; // выполняет побитовую операцию XOR
            mov c, ebx;
        }
        return c;
    }

    int CMP(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            mov ebx, b;
            cmp eax, ebx;
            JE m1; // равны
            mov eax, 0;
            JMP m;
            m1: mov eax, 1;
            m: mov c, eax;
        }
        return c;
    }

    int Less(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            cmp eax, b;
            JL m1;
            mov eax, 0;
            JMP m;
        m1 : mov eax, 1;
        m: mov c, eax;
        }
        return c;
    }

    int More(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            cmp eax, b;
            JG m1;
            mov eax, 0;
            JMP m;
        m1: mov eax, 1;
        m: mov c, eax;
        }
        return c;
    }

    int SHR(int a)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            shr eax, 1;
            mov c, eax;
        }
        return c;
    }

    int SHL(int a)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            shl eax, 1;
            mov c, eax;
        }
        return c;
    }

    int ROL(int a)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            rol eax, 1;
            mov c, eax;
        }
        return c;
    }

    int ROR(int a)
    {
        int c = 0;
        _asm
        {
            mov eax, a;
            ror eax, 1;
            mov c, eax;
        }
        return c;
    }

    int IndexMas()
    {
        _asm
        {
            mov ecx, n;
            lea eax, a; 

        m_Cycle:
            cmp dword ptr[eax], 0; // сравниваем
            jl m_Less;
            je m_Finish;
            
            //больше
            mov dword ptr[eax], 1;
            jmp m_Finish;

        //меньше
        m_Less:
            add dword ptr[eax], 1;

        m_Finish:
            add eax, 4;
            loop m_Cycle;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Operations numbers;
    //1. Сложение, вычитание, умножение и деление
    cout << "1. Сложение, вычитание, умножение и деление" << endl;
    cout << "5 + 12 = " << numbers.Addition(5, 12) << "\n";
    cout << "13 - 7 = " << numbers.Subtraction(13, 7) << "\n";
    cout << "7 * 9 = " << numbers.Multiplication(7, 9) << "\n";
    cout << "81 / 3 = " << numbers.Division(81, 3) << "\n";

    //2.Операции сравнения
    cout << endl << "2.Операции сравнения" << endl;
    cout << "7 = 7? Если значения равны, то выведем 1, иначе - 0. Результат: " << numbers.CMP(7, 7) << "\n";
    cout << "56 < 19? Если значения меньше, то выведем 1, иначе - 0. Результат: " << numbers.Less(56, 19) << "\n";
    cout << "12 > 5? Если значения больше, то выведем 1, иначе - 0. Результат: " << numbers.More(12, 5) << "\n";

    //3.Логические операции: not, and, or, xor
    cout << endl << "3.Логические операции: not, and, or, xor" << endl;
    cout << "Not от 15. Результат: " << numbers.LogNot(15) << "\n";
    cout << "15 AND 3? Результат: " << numbers.LogAnd(5, 4) << "\n";
    cout << "5 OR 3? Результат: " << numbers.LogOr(5, 3) << "\n";
    cout << "5 XOR 3? Результат: " << numbers.LogXor(5, 3) << "\n";

    //5.Операции сдвига
    cout << endl << "5.Операции сдвига" << endl;
    cout << "SHR: " << numbers.SHR(180) << "\n"; // сдвиг вправо
    cout << "SHL: " << numbers.SHL(16) << "\n";  // сдвиг влево
    cout << "ROL: " << numbers.ROL(1) << "\n"; // циклический сдвиг влево
    cout << "ROR: " << numbers.ROR(2) << "\n"; // циклический сдвиг вправо

    //4.Индексация по массиву
    cout << endl << "4.Индексация по массиву" << endl;
    cout << "Кол-во элементов массива: " << n << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "a[" << i + 1 << "]: ";
        cin >> a[i];
    };

    numbers.IndexMas();

    cout << "Если значение элемента меньше 0, то мы добавляем 1, если оно больше, то делаем его значение равным 1" << endl;

    cout << "Измененный массив:\n";
    for (int i = 0; i < int(n); i++)
        cout << "a[" << i + 1 << "]: " << a[i] << endl;

    system("pause");
    return 0;
};
