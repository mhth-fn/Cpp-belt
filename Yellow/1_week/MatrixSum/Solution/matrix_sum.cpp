#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix
class Matrix{
	public:
		Matrix(){
			cols = 0;
			rows = 0;
		}
		Matrix(int new_rows, int new_cols){
			Reset(new_rows, new_cols);
		}

		void Reset(int new_rows, int new_cols){
			if (new_rows < 0 || new_cols < 0){
				throw out_of_range("Invalid param");
			}
			if (new_rows == 0 || new_cols == 0){
				new_rows = new_cols = 0;
			}
			cols = new_cols;
			rows = new_rows;
			
			matrix.assign(rows, vector<int>(cols));
		}

		int& At(int row, int col){
			return matrix.at(row).at(col);
		}
		
		int At(int row, int col) const{
			return matrix.at(row).at(col);
		}

		int GetNumRows() const{
			return rows;
		}
		
		int GetNumColumns() const{
			return cols;
		}
	private:
		int cols;
		int rows;
		vector<vector<int>> matrix;
};

istream& operator>>(istream& stream, Matrix& M){
	int rows, cols;
	stream >> rows >> cols;
	M.Reset(rows, cols);
	
	for (int i = 0; i != M.GetNumRows(); ++i){
		for (int j = 0; j != M.GetNumColumns(); ++j){
			stream >> M.At(i, j);
		}
	}
	
	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& M){
	stream << M.GetNumRows() << " " << M.GetNumColumns() << '\n';
	for (int i = 0; i != M.GetNumRows(); ++i){
		for (int j = 0; j != M.GetNumColumns(); ++j){
			if (j != 0){
				stream << " ";
			}
			stream << M.At(i, j);
		}
		stream << endl;
	}
	
	return stream;
}

bool operator==(const Matrix M1, const Matrix M2){
	if (M1.GetNumColumns() == M2.GetNumColumns() && M1.GetNumRows() == M2.GetNumRows()){
		for (int i = 0; i != M1.GetNumRows(); ++i){
			for (int j = 0; j != M2.GetNumColumns(); ++j){
				if (M1.At(i, j) != M2.At(i, j)){
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    throw invalid_argument("");
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    throw invalid_argument("");
  }

  Matrix result(one.GetNumRows(), one.GetNumColumns());
  for (int row = 0; row < result.GetNumRows(); ++row) {
    for (int column = 0; column < result.GetNumColumns(); ++column) {
      result.At(row, column) = one.At(row, column) + two.At(row, column);
    }
  }

  return result;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;
 
	return 0;
}
