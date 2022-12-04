#include <iostream>

#define N 9

// Identifica se um número está presente em uma linha
// Recebe a matriz de Sudoku, o índice da linha desejada e o número desejado - retornando o booleano
bool isPresentInRow(int grid[][N], int row, int num){
    for(unsigned int i = 0; i < N; i++){
        if(grid[row][i] == num){
            return true;
        }
    }
    return false;
}

// Identifica se um número está presente em uma coluna
// Recebe a matriz de Sudoku, o índice da coluna desejada e o número desejado - retornando o booleano
bool isPresentInColumn(int grid[][N], int column, int num){
    for(unsigned int i = 0; i < N; i++){
        if(grid[i][column] == num){
            return true;
        }
    }
    return false;
}

// Identifica se um número está presente em um bloco
// Recebe a matriz de Sudoku, o índice de início da linha do bloco desejado, o índice de início da coluna do bloco desejado e o número desejado- retornando o booleano
bool isPresentInBox(int grid[][N], int boxStartRow, int boxStartColumn, int num){
    for(unsigned int i = boxStartRow; i < (boxStartRow + 3); i++){
        for(unsigned int j = boxStartColumn; j < (boxStartColumn + 3); j++){
            if(grid[i][j] == num){
                return true;
            }
        }
    }
    return false;
}

// Imprime a matriz de sudoku formatada
void printSudoku(int grid[][N]){
    std::cout << "A solucao eh: \n";
    for(unsigned int i = 0; i < N; i++){
        for(unsigned int j = 0; j < N; j++){
            std::cout << grid[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

// Procura o primeiro espaço vazio da matriz de Sudoku
// Recebe a matriz de Sudoku e dois inteiros para a saída de informação sobre o primeiro espaço vazio - retorna o booleano
bool findEmptySpace(int grid[][N], int &row, int &column){
    for(row = 0; row < N; row++){
        for(column = 0; column < N; column++){
            if(grid[row][column] == 0){
                return true;
            }
        }
    }
    return false;
}

// Procure se o número é válido para o espaço desejado
// Recebe a matriz de Sudoku, dois inteiros para a posição desejada e o número desejado - retorna o booleano.
bool isValidPlace(int grid[][N], int row, int column, int num){
    if(((isPresentInRow(grid, row, num)) || (isPresentInColumn(grid, column, num))) || (isPresentInBox(grid, (row - row%3), (column - column%3), num))){
        return false;
    }
    else{
        return true;
    }
}

// Resolve o Sudoku
// Recebe a matriz de Sudoku - retorna o booleano
bool solveSudoku(int grid[][N]){
    int row, column; // Armazenarão primeiro espaço vazio
    if(!(findEmptySpace(grid, row, column))){ // Se não há espaços vazios, retorna true
        return true;
    }
    for(unsigned int i = 1; i <= N; i++){ // Checa números válidos para o espaço vazio
        if(isValidPlace(grid, row, column, i)){ // Se um determinado número é válido
            grid[row][column] = i; // Seta ele no quadrado
            if(solveSudoku(grid)){ // e tenta resolver o resto do Sudoku
                return true;
            }
            grid[row][column] = 0; // Caso não seja possível resolver o Sudoku com o número naquela posição, retorna-o para 0 e reinicia o processo
        }
    }
    return false; // Se há algum espaço vazio que não possa receber nenhum número, retorna false
}

int main(){
    int grid[N][N] = {
            {2, 0, 1, 8, 4, 0, 0, 6, 0},
            {0, 0, 0, 0, 6, 0, 9, 0, 0},
            {0, 0, 5, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 7, 0, 0, 3},
            {8, 0, 6, 1, 0, 0, 0, 9, 0},
            {0, 4, 0, 0, 0, 0, 0, 0, 0},
            {0, 9, 0, 4, 0, 0, 0, 0, 0},
            {0, 5, 0, 0, 0, 0, 0, 2, 0},
            {4, 0, 2, 0, 0, 1, 7, 0, 0}
    };
    if(solveSudoku(grid) == true){
        printSudoku(grid);
    }
    else{
        std::cout << "O Sudoku referido eh impossivel";
    }
    return 0;
}