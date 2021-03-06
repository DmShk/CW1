// MT.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "cstdlib"
#include "iomanip"
using namespace std;

// Исключение которое я добавил находиться в фнкции DetGayss 


/*struct mat {
	int n;
	int m;
	double *a;
	mat(int n, int m) {
		a = new double[n*m];
	}
	double get(int x, int y) {
		if (x<0 and x>n - 1) {
			cout << "err";
		}
		return a[x + m * y];
	}
	void set(double val,int x, int y) {
		a[x + m * y] = val;
	}
};
*/
void output(int n, int m, double **a) //функция ввывода матрицы
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << setw(12) << a[i][j];
		}
		cout << "\n\n";
	}

}
int Rang(int n, int m, double **a);// прототип функции Ранг матрицы
double **Obrat(int n, int m, double **a);// прототип функции нахождения обратной матрицы матрицы
void Transponir(int n, int m, double **a)// функция транспонирования 
{
	double **c1;
	c1 = new double *[m];
	for (int i = 0; i < m; i++) {
		c1[i] = new double[n];
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c1[i][j] = a[j][i];
		}
	}
	
	for (int i = 0; i < n; i++) {
		delete[]a[i];
	}
	delete[]a;
	
	
	swap(m, n);// функцияя меняющая значения переменных
	output(n, m, c1);
	cout << " n = " << n << "\n";
	cout << " m = " << m << "\n";

	a = new double *[n];
	for (int i = 0; i < n; i++) {
		a[i] = new double[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; i++) {
			a[i][j] = c1[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		delete[]c1[i];
	}
	delete[]c1;
}// прототип функции транспонирования матрицы

void output(int n, double *a) //функция ввывода матрицы
{
	for (int i = 0; i < n; i++) {
		cout << setw(12) << a[i];
	}
	cout << "\n\n";
}//функция ввывода матрицы
void inputrand(int n, int m, double **a) // функция автоматического ввода матрицы
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = rand() % 10;
		}
	}
}
void input(int n, int m, double **a) //функция ручного ввода матрицы
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << " a[" << i + 1 << "][" << j + 1 << "] ";
			cin >> a[i][j];
		}
		cout << "\n";
	}
}//функция ручного ввода матрицы
/*void input(mat matr) {
	for (int i = 0; i < matr.n; i++) {
		for (int j = 0; j < matr.m; j++) {
			cout << " a[" << i + 1 << "][" << j + 1 << "] ";
			double z;
			cin >> z;
			matr.set(z, i, j);
		}
		cout << "\n";
	}
}*/
bool poz(int k, int n, double **a) //функция меняющая местами строки
{
	int st;
	double zam;
	bool ch = false;
	for (int i = k; i < n; i++) {
		if (a[i][k] != 0) {
			st = i;
			ch = true;
			break;
		}
	}
	if (ch == true) {
		for (int i = 0; i < n; i++) {
			zam = a[k][i];
			a[k][i] = a[st][i];
			a[st][i] = zam;

		}
		return true;
	}
	else {
		return false;
	}


}
bool pozv(int k, int m, double **a)  //функция меняющая местами столбцы
{
	int stb;
	bool ch = false;
	double zam;
	for (int i = 0; i < m; i++) {
		if (a[k][i] != 0) {
			stb = i;
			ch = true;
			break;
		}
	}
	if (ch == true) {
		for (int i = 0; i < m; i++) {
			zam = a[i][k];
			a[i][k] = a[i][stb];
			a[i][stb] = zam;
		}
		return true;
	}
	else {
		return false;
	}
}
double DetGayss(int n, int m, double **a) //функция нахождения определителя матрицы
{
	try { // начало исключения
		if (n != m) {
			throw 1;
		}		
	}
	catch (int) { cout << "Матрица неквадратная\n"; return NULL; }
	double DetG = 1;
	double **a1; // Массив в котором будут происходить преобразования 
	a1 = new double *[n];
	for (int i = 0; i < n; i++) {
		a1[i] = new double[m];
	}
	double x;// число на которое умнажаеться строка чтобы при вычитании на другую элемент определенного столбца стал равным нулю
	int per = 0; // переменная для счета перестановок
	
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a1[i][j] = a[i][j];
			}
		}
		for (int k = 0; k < n; k++) {
			if (a1[k][k] == 0) {
				if (poz(k, n, a1) == true) { // вызов функции для перестановки строки
					DetG *= a1[k][k];
					per++; // счетчик перестановок
				}
				else {
					DetG *= a1[k][k];
					break;
				}

			}
			else {
				DetG *= a1[k][k];
			}
			for (int g = 1; g < (n - k); g++) {
				x = a1[k + g][k] / a1[k][k];
				for (int j = 0; j < n; j++) {
					a1[k + g][j] = a1[k + g][j] - x * a1[k][j];
				}
			}

		}
 		if (per % 2 != 0) { //проверка на нечетность количества перестановок
			DetG *= -1;
		}
		return DetG;
	}
double **SummMatrix(int n, int m, double **a,int k,int l,double **b) // функция суммирования матриц
{
	try {// проверка на совпадение размерностей матриц
		if (n != k || m != l) {
			throw 5;
		}
	}
	catch (int) { cout << "Невозможно сложить"; return NULL; }
	double **c;// матрица в которую будет записанн результат суммы
	c = new double *[n];
	for (int i = 0; i < n; i++) {
		c[i] = new double[m];
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
		return c;
}
double **SubtrMatrix(int n, int m, double **a, int k, int l, double **b) {
	try {// проверка на совпадение размерностей матриц
		if (n != k || m != l) {
			throw 5;
		}
	}
	catch (int) { cout << "Невозможно сложить"; return NULL; }
	double **c;// матрица куда будет записан результат вычитания матриц
	c = new double *[n];
	for (int i = 0; i < n; i++) {
		c[i] = new double[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}
double *Cramer( int n, int m, double **a) //функция решения системы уравнения методом Крамера
{
	try { // проверка являеться ли матрица квадратной
		if (n != m) {
			throw 1;
		}

	}
	catch (int) { cout << "Матрица неквадратная\n"; return NULL; }
	double D = DetGayss(n, m, a);// проврка равенства нулю определителя
	try {
		if (D == 0) {
			throw 2;
		}

	}
	catch (int) { cout << "Определитель равен нулю \n"; return NULL; }

	double **a1;
	a1 = new double *[n];
	for (int i = 0; i < n; i++) {
		a1[i] = new double[m];
	}
	double *b = new double[n];// массив расширенной части массива 
	double *x = new double [n];// массив куда будет записанно решение
		
	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a1[i][j] = a[i][j];
		}
	}

	cout << " Введите расширенную часть \n";
	
	
	for (int i = 0; i < n; i++) {
		cin >> b[i];
		cout << "\n";
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			a1[i][j] = b[i];

		}
		x[j] = DetGayss(n, m, a1) / D;
	for (int i = 0; i < n; i++) { 
			for (int j = 0; j < n; j++) {
				a1[i][j] = a[i][j];
			}
		}
	}
	delete[]a1;
	delete[]b;
	return x;
}
void multnum( int n, int m, double **a,double num )// функция произведения матрицы на число
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] *= num;
		}
	}
}
double **multm(int n, int m, double **a, int k, int l, double **b);
int main()
{
	setlocale(0, "rus");
	srand(NULL);
	int n, m,k,l;
	int choose;
	double num;
	double **a;
	int y = 1;

	cout << " n = ";
	 cin >> n;
	cout << " m = ";
	 cin >> m;
	 a = new double *[n];
	 for (int i = 0; i < n; i++) {
		 a[i] = new double[m];
	 }
	 


	cout << " Auto or no (1/0)= ";
	 cin >> choose;

	if (choose == 1) { inputrand(n, m, a); }
	else { input(n, m, a); }

	output(n, m, a);
	cout << " Выберите операцию : \n";
	cout << " 1) Вычислить определитель\n" << " 2) Транспонировать матрицу\n" << " 3) Найти обратную\n" << " 4) Решить систему линейных уравнений методом Крамера\n"<<" 5) Умножение на число\n"<<" 6) Вычислить ранг матрицы\n"<<" 7) Сложение матриц\n";
	cout << " Номер = ";
	cin >> choose;
	switch (choose) {
	case 1:////////////////////////////////////////////
	cout << " Det(A) = " << DetGayss(n, m, a) << "\n";
		break;


	case 2: Transponir(n, m, a);////////////////////////////////////
		output(n, m, a);
		
			   break;



	case 3:////////////////////////////////
	a=Obrat(n, m, a); 
	output(n, m, a);
		break;


	case 4: Cramer(n, m, a);////////////////////////////////////////
		break;


	case 5://////////////////////////////////
		cout << " num = ";
		cin >> num;
			multnum(n, m, a,num);
		output(n, m, a);
		break;


	case 6: ///////////////////////////////////////
		cout<<" Rang = "<<Rang(n, m, a)<<"\n";
		break;


	case 7:/*input(n, m, b); b=SummMatrix(n, m, a,n,m, b); output(n, m, b);
		break;*/
	case 8:
		cout << " nb = ";
		cin >> k;
		cout<< " mb = ";
		cin >> l;
		double **b;
		b = new double *[k];
		for (int i = 0; i < k; i++) {
			b[i] = new double[l];
		}
		inputrand(k, l, b);
		output(k, l, b);
		output(n, l, multm(n, m, a, k, l, b));
		break;

	default: cout << " Неверный выбор \n";
	}
	

	system("pause");
	return 0;
}
double **Obrat(int n, int m, double **a) // функция нахождения обратной матрицы
{
	try {// блок исключения
		if (n != m) {
			throw 1;
		}

	}
	catch (int) { cout << "Матрица неквадратная\n"; return NULL; }

	double **c;// массив в котором будут перезаписываться миноры
	c = new double *[n];
	for (int i = 0; i < n; i++) {
		c[i] = new double[m];
	}
	double **o;//  массив в который запишеться обратная матрица
	o = new double *[n];
	for (int i = 0; i < n; i++) {
		o[i] = new double[m];
	}
	int ic = 0, jc = 0;
	int io = 0, jo = 0;
	int b = n - 1;
	for (int is = 0; is < n; is++) {
		for (int js = 0; js < n; js++) {
			ic = 0;
			for (int i = 0; i < n; i++) {
				jc = 0;
				for (int j = 0; j < n; j++) {
					if (i != is && j != js) {
						c[ic][jc] = a[i][j];
						jc++;
					}
				}
				if (i != is) { ic++; }
			}


			if (jo == n) { jo = 0; io++; 
			 o[io][jo] = pow(-1, (is + js))*DetGayss(b, b, c);
			 jo++;
			}
			else {
			 o[io][jo] = pow(-1 , (is + js))*DetGayss(b, b, c);
			 jo++;
			}
		}
    }
	Transponir(n, m, o);// функция транспонирования
	multnum(n, m, o, (1 / DetGayss(n, m, a))); // функция умножения матрицы на число
	for (int i = 0; i < n; i++) {
		delete[]c;
	}
	
	return o;
}
int Rang(int n, int m, double **a)// функция нахождения ранга матрицы
{
	double **a1; // массив в котором будут происходить преобразования
	a1 = new double *[n];
	for (int i = 0; i < n; i++) {
		a1[i] = new double[m];
	}
	double x;
	int rang = 0;// счетчик ненулевых элементов на главной диагонали после преобразования массива
	int n1;
	int l = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a1[i][j] = a[i][j];
		}
	}

	for (int k = 0; k < n; k++) {
		if (a1[k][k] == 0) {
			if (poz(k, n, a1)==false) { // перестановка двух строк
				if (pozv(k, m, a1) == false) {// перестановка двух столбцов
					break;
				}

			}
		}
		for (int g = 1; g < (n-k); g++) {
			x = a1[k + g][k] / a1[k][k];
			for (int j = 0; j < m; j++) {
				a1[k + g][j] = a1[k + g][j] - x * a1[k][j];
			}
		}
		output(n, m, a1);
		cout << "\n\n\n";
	}
	n1 = (n > m) ? (m) : (n);
	cout << " l= " << l << "\n";
	for (int i = 0; i < n1; i++) {
			if (a1[i][i] == 0) {  break; }
			else { rang++;}
	}
	return rang;
}
double **multm(int n, int m, double **a, int k, int l, double **b) {
	try { // проверка на применимость операции произведение к данным матрицам
		if (m != k) {
			throw 3;
		}
	}
	catch (int) {
		cout << " Эти матрицы нельзя перемножить "; return NULL;
	}
	int x = 0;
	double **c;// матрица в которую будет записан результат перемножения 
	c = new double *[n];
	for (int i = 0; i < n; i++) {
		c[i] = new double[l];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < l; j++) {
			c[i][j] = 0;
		}
	}
	
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < m; j++) {
				c[k][i] += a[k][j] * b[j][i];
			}
		}
	}
	return c;
}


