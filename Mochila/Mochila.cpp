#include <iostream>
#include <vector>
using namespace std;

class Item
{
public:
	string nome;
	int valor;
	int peso;
	Item() {
		this->nome = "vazio";
		this->valor = 0;
		this->peso = 0;
	}
	Item(int valor, int peso, string nome) {
		this->nome = nome;
		this->valor = valor;
		this->peso = peso;
	}
	~Item() {}

private:

};
int valor(vector<Item*> itens);
int valorMaximo(int* valores, int* pesos, int maxCap, int numeroItens);
vector<Item*> resolver(vector<Item*> itens, int maxCap);
int peso(vector<Item*> itens);


int main()
{
	vector<Item*> itens;
	string nomeI = "";
	int pesoI = 0;
	int valorI = 0;
	string continuar = "";
	int cap = 0;
	while (true) {
		cout << "Digite o nome do item\n";
		cin >> nomeI;
		cout << "Digite o peso do item\n";
		cin >> pesoI;
		cout << "Digite o valor do item\n";
		cin >> valorI;
		itens.push_back(new Item(valorI, pesoI, nomeI));
		cout << "Deseja inserir mais itens? (s/n)\n";
		cin >> continuar;
		if (continuar == "n") break;
	}
	cout << "Digite a capacidade da mochila\n";
	cin >> cap;

	vector<Item*> res = resolver(itens, cap);
	cout << "Lista de itens: \n";
	int valorTotal = 0;
	int pesoTotal = 0;
	if (valor(res) != 0 && peso(res) != 0) {
		for (int i = 0; i < res.size(); i++)
		{
			if (res[i]->valor != 0 && res[i]->peso != 0) {
				cout << "-------------------------------------\n";
				cout << "nome: " << res[i]->nome << endl;
				cout << "valor: " << res[i]->valor << endl;
				cout << "peso: " << res[i]->peso << endl;
				valorTotal += res[i]->valor;
				pesoTotal += res[i]->peso;
			}
		}
		cout << "-------------------------------------\n";
		cout << "valor total: " << valorTotal << endl;
		cout << "peso total: " << pesoTotal << endl;
		cout << "Digite qualquer coisa para fechar...";
		cin;
		return 0;
	}
	cout << "nao ha itens possiveis para colocar na mochila\n";
	cout << "Digite qualquer coisa para fechar...";
	cin;
	return 0;
}
int valor(vector<Item*> itens) {
	int total = 0;
	for (int i = 0; i < itens.size(); i++)
	{
		total += itens[i]->valor;
	}
	return total;
}

int peso(vector<Item*> itens) {
	int total = 0;
	for (int i = 0; i < itens.size(); i++)
	{
		total += itens[i]->peso;
	}
	return total;
}

int valorMaximo(int* valores, int* pesos, int maxCap, int numeroItens) {
	vector<vector<int>> matriz;
	for (int i = 0; i < numeroItens + 1; i++)
	{
		vector<int> myvector;
		for (int j = 0; j < maxCap + 1; j++)
		{
			int tempVal = j;
			myvector.push_back(tempVal);
		}
		matriz.push_back(myvector);
	}
	for (int i = 0; i < numeroItens + 1; i++) {
		for (int cap = 0; cap < maxCap + 1; cap++) {
			if (i == 0 || cap == 0) {
				matriz[i][cap] = 0;
			}
			else if (pesos[i - 1] <= cap) {
				matriz[i][cap] = max(
					valores[i - 1] + matriz[i - 1][cap - pesos[i - 1]],
					matriz[i - 1][cap]
				);
			}
			else {
				matriz[i][cap] = matriz[i - 1][cap];
			}
		}
	}
	return matriz[numeroItens][maxCap];
}

vector<Item*> resolver(vector<Item*> itens, int maxCap) {
	vector<vector<vector<Item*>>> matriz;
	//inicializa a matriz
	for (int i = 0; i < itens.size() + 1; i++)
	{
		vector<vector<Item*>> myvector;
		for (int j = 0; j < maxCap + 1; j++)
		{
			vector<Item*> tempVal;
			tempVal.push_back(new Item());
			myvector.push_back(tempVal);
		}
		matriz.push_back(myvector);
	}
	for (int i = 0; i < itens.size() + 1; i++) {
		for (int cap = 0; cap < maxCap + 1; cap++) {
			if (i == 0 || cap == 0) {
				matriz[i][cap] = { new Item() };
			}
			else if (itens[i - 1]->peso <= cap && itens[i - 1]->valor + valor(matriz[i - 1][cap - itens[i - 1]->peso]) > valor(matriz[i - 1][cap])) {
				vector<Item*> temp = matriz[i - 1][cap - itens[i - 1]->peso];
				temp.push_back(itens[i - 1]);
				matriz[i][cap] = temp;

			}
			else {
				matriz[i][cap] = matriz[i - 1][cap];
			}
		}
	}
	return matriz[itens.size()][maxCap];
}
