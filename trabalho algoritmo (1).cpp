// 2211550481 ISABELA FERREIRA DA SILVA 2º ADS T2


#include <iostream>
#include <conio.h>
#include <cstring>
#include <string>
using namespace std;

struct alunos{
	long int cpf;
	string nome_aluno;
	string data_nascimento;
	float peso;
	float altura;
	int statusAluno;
};

struct idx_alunos{
	long int cpf_alu;
	int end_aluno;
};

struct professores{
	int codigo_professor;
	string nome_prof;
	string endereco;
	string telefone;
	int statusProfessor;
};

struct idx_professores{
	int cod_professor;
	int end_professor;
};

struct modalidades{
	int codigo_modalidade;
	string descricao;
	int cod_prof;
	float valor_aula;
	int limite_alunos;
	int total_alunos;
	int statusModalidade;
};

struct idx_modalidades{
	int cod_modalidade;
	int end_modalidade;
};

struct matriculas{
	int codigo_matricula;
	long int cpf_aluno;
	int cod_modalidade;
	int qtde_aulas;
	int statusMatricula;
};

struct idx_matriculas{
	int cod_matricula;
	int end_matricula;
};


//BLOCO MOVIMENTAÇÕES NA STRUCT ALUNO

float calcularImc(float peso, float altura) {
    return peso / (altura * altura);
}

int buscarAluno(struct idx_alunos indiceAluno[], int &contadorAluno, long int cpf) {
    int inicio = 0, fim = contadorAluno - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && cpf != indiceAluno[meio].cpf_alu; meio = (inicio + fim) / 2) {
        if (cpf > indiceAluno[meio].cpf_alu) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (cpf == indiceAluno[meio].cpf_alu) {
        return indiceAluno[meio].end_aluno;
    } else {
        return -1;
    }
}

void inserir_aluno(struct alunos aluno[], struct idx_alunos indiceAluno[], int &contadorAluno) {
    cout << "************* CADASTRAR NOVOS ALUNOS ****************";
    const int tamanhoMaximoVetor = 8;

    for (int i = 4; i < tamanhoMaximoVetor;) {

        

        bool alunoExiste = false;
        while (!alunoExiste) {

            cout << "\n\n*Digite o CPF do aluno (padrao 8888) " << "(digite 0 para sair): ";
            cin >> aluno[i].cpf;

            if (aluno[i].cpf == 0) {
                break;
            }

            int validarCpf = buscarAluno(indiceAluno, contadorAluno, aluno[i].cpf);
            if (validarCpf != -1) {
                cout << "CPF ja cadastrado para aluno(a): " << aluno[validarCpf].nome_aluno;
            } else {
                alunoExiste = true;
            }
        }
        if (aluno[i].cpf == 0) {
            break;
        }
        
        
        bool nomeAlunoNaoVazio = false;
        while (!nomeAlunoNaoVazio) {
            cout << "\nNome do Aluno(a): ";
            cin.ignore();
            getline(cin, aluno[i].nome_aluno);
            if (aluno[i].nome_aluno != "") {
                nomeAlunoNaoVazio = true;
            } else {
                cout << "Nome do aluno(a) nao pode estar vazio!" << endl;
            }
        }

        bool dataDeNascimentoNaoVazia = false;
        while (!dataDeNascimentoNaoVazia) {
            cout << "\nData de nascimento do Aluno(a): ";
            getline(cin, aluno[i].data_nascimento);
            if (aluno[i].data_nascimento != "") {
                dataDeNascimentoNaoVazia = true;
            } else {
                cout << "Data de nascimento do aluno não pode ser vazia!" << endl;
            }
        }

        cout << "Peso do Aluno(a): ";
        cin >> aluno[i].peso;
        cout << "Altura do aluno(a): ";
        cin >> aluno[i].altura;
        float imc = calcularImc(aluno[i].peso, aluno[i].altura);
        cout << "\nO IMC do aluno(a) é: " << imc << endl;

        if (imc < 18.5) {
            cout << "O aluno(a) " << aluno[i].nome_aluno << " está com Magreza segundo os padrões IMC" << endl;
        } else if (imc >= 18.5 && imc <= 24.99) {
            cout << "O aluno(a) " << aluno[i].nome_aluno  << " está com Peso normal segundo os padrões IMC" << endl;
        } else if (imc >= 25 && imc <= 29.99) {
            cout << "O aluno(a) " << aluno[i].nome_aluno  << " está com Sobrepeso segundo os padrões IMC" << endl;
        } else if (imc >= 30 && imc <= 34.99) {
            cout << "O aluno " << aluno[i].nome_aluno  << " está com Obesidade grau I segundo os padrões IMC" << endl;
        } else if (imc >= 35 && imc <= 39.99) {
            cout << "O aluno " << aluno[i].nome_aluno  << " está com Obesidade grau II segundo os padrões IMC" << endl;
        } else {
            cout << "O aluno(a) " << aluno[i].nome_aluno  << " está com Obesidade grau III segundo os padrões IMC"
                 << endl;
        }
        int j;
        for (j = contadorAluno - 1; j >= 0 && aluno[i].cpf < indiceAluno[j].cpf_alu; j--) {
            indiceAluno[j + 1] = indiceAluno[j];
        }
        indiceAluno[j + 1].cpf_alu = aluno[i].cpf;
        indiceAluno[j + 1].end_aluno = i;
        cout << "\n***Aluno cadastrado com Sucesso***" << endl;
        contadorAluno++;
        i++;
    }

    cout << "\n\nSaindo da insercao de alunos..." << endl;
    cin.ignore();
}

void exclusaoAluno(struct idx_alunos indiceAluno[], struct alunos aluno[], int &contadorAluno, long int &cpf){
    int inicio = 0, fim = contadorAluno - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && cpf != indiceAluno[meio].cpf_alu; meio = (inicio + fim) / 2) {
        if (cpf > indiceAluno[meio].cpf_alu) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    inicio = indiceAluno[meio].end_aluno;
    if ((cpf == indiceAluno[meio].cpf_alu) && aluno[inicio].statusAluno == 0){
        aluno[inicio].statusAluno = 1;
        cout << "Aluno(a) " << aluno[inicio].nome_aluno <<" excluido" <<endl;
    } else {
        cout << "Aluno(a) nao encontrado." <<endl;
    }
}

void leituraExaustivaAluno(struct idx_alunos indiceAluno[], struct alunos aluno[], int &contadorAluno){
    for(int k = 0; k < contadorAluno; k++){
        int i = indiceAluno[k].end_aluno;
        if (aluno[i].statusAluno == 0){
            cout << "\n\nNome do aluno(a): " << aluno[i].nome_aluno;
            cout << "\nData de nascimento do aluno(a): " << aluno[i].data_nascimento;
            cout << "\nPeso do aluno(a): " << aluno[i].peso;
            cout << "\nAltura do aluno(a): " << aluno[i].altura;
        }
    }
}

void reorganizacaoAluno(struct alunos aluno[],struct idx_alunos indiceAluno[], int &contadorAluno,
						 struct alunos novoAluno[], struct idx_alunos novoIndiceAluno[], int &novoContadorAluno){
	int i = 0;
	int j = 0;
	novoContadorAluno = 0;
	for(; j <= contadorAluno; j++ ){
		i = indiceAluno[j].end_aluno;
			if (aluno[i].statusAluno == 0){
				novoAluno[novoContadorAluno].cpf = aluno[i].cpf;
				novoAluno[novoContadorAluno].nome_aluno = aluno[i].nome_aluno;
				novoAluno[novoContadorAluno].data_nascimento = aluno[i].data_nascimento;
				novoAluno[novoContadorAluno].peso = aluno[i].peso;
				novoAluno[novoContadorAluno].altura = aluno[i].altura;
				novoAluno[novoContadorAluno].statusAluno = aluno[i].statusAluno;
			    novoIndiceAluno[novoContadorAluno].cpf_alu = indiceAluno[j].cpf_alu;
				novoIndiceAluno[novoContadorAluno].end_aluno = novoContadorAluno;
			novoContadorAluno++;
		}
	}
}

void novoReorganizacaoAluno(struct alunos novoAluno[],struct idx_alunos novoIndiceAluno[], int &novoContadorAluno,
						 struct alunos aluno[], struct idx_alunos indiceAluno[], int &contadorAluno){
	contadorAluno = novoContadorAluno;
	aluno = novoAluno;
	indiceAluno = novoIndiceAluno;
}

//FIM ALUNO

//BLOCO MOVIMENTAÇÕES NA STRUCT PROFESSOR

int buscarProfessorExistente(struct idx_professores indiceProfessor[], int contadorProfessor, int codigoDoProfessor) {
    int inicio = 0, fim = contadorProfessor - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigoDoProfessor != indiceProfessor[meio].cod_professor; meio = (inicio + fim) / 2) {
        if (codigoDoProfessor > indiceProfessor[meio].cod_professor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (codigoDoProfessor == indiceProfessor[meio].cod_professor) {
        return indiceProfessor[meio].end_professor;
    } else {
        return -1;
    }
}

void inserir_professor(struct idx_professores indiceProfessor[], struct professores professor[], int &contadorProfessor) {
    cout << "\n\n\n************* CADASTRAR NOVOS PROFESSORES ****************";
    const int tamanhoMaximoVetor = 8;
    for (int i = 4; i < tamanhoMaximoVetor;) {
        

        bool professorExiste = false;
        while (!professorExiste) {
            cout << "\n\n*Digite o codigo do professor (padrao 88) " << "(digite 0 para sair): ";
            cin >> professor[i].codigo_professor;
            if (professor[i].codigo_professor == 0) {
                break;
            }
            int validaCodigo = buscarProfessorExistente(indiceProfessor, contadorProfessor, professor[i].codigo_professor);
            if (validaCodigo != -1) {
                cout << "Codigo ja cadastrado para o professor(a): " << professor[validaCodigo].nome_prof;
            } else {
                professorExiste = true;
            }
        }
        if (professor[i].codigo_professor == 0) {
            break;
        }

        bool nomeProfessorNaoVazio = false;
        while (!nomeProfessorNaoVazio) {
            cout << "Nome do Professor(a): ";
            cin.ignore();
            getline(cin, professor[i].nome_prof);
            if (professor[i].nome_prof != "") {
                nomeProfessorNaoVazio = true;
            } else {
                cout << "Nome do professor pode nao estar vazio!" << endl;
            }
        }

        bool enderecoNaoVazio = false;
        while (!enderecoNaoVazio) {
            cout << "Endereco do professor(a): ";
            getline(cin, professor[i].endereco);
            if (professor[i].endereco != "") {
                enderecoNaoVazio = true;
            } else {
                cout << "Endereco nao pode ser vazio" << endl;
            }
        }

        bool telefoneNaoVazio = false;
        while (!telefoneNaoVazio) {
            cout << "Telefone do professor(a): ";
            getline(cin, professor[i].telefone);
            if (professor[i].telefone != "") {
                telefoneNaoVazio = true;
            } else {
                cout << "Telefone nao pode ser vazio" << endl;
            }
        }

        int j;
        for (j = contadorProfessor - 1; j >= 0 && professor[i].codigo_professor < indiceProfessor[j].cod_professor; j--) {
            indiceProfessor[j + 1] = indiceProfessor[j];
        }
        indiceProfessor[j + 1].cod_professor = professor[i].codigo_professor;
        indiceProfessor[j + 1].end_professor = i;
        cout << "\n***Professor cadastrado com Sucesso***" << endl;
        contadorProfessor++;
        i++;
    }
    cout << "\n\nSaindo da insercao de professores...." << endl;
    cin.ignore();
}


void exclusaoProfessor(struct idx_professores indiceProfessor[], struct professores professor[], int &contadorProfessor, int &codigo){
    int inicio = 0, fim = contadorProfessor - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigo != indiceProfessor[meio].cod_professor; meio = (inicio + fim) / 2) {
        if (codigo > indiceProfessor[meio].cod_professor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    inicio = indiceProfessor[meio].end_professor;
    if((codigo == indiceProfessor[meio].cod_professor) && professor[inicio].statusProfessor == 0){
        professor[inicio].statusProfessor = 1;
        cout << "Professor(a) " << professor[inicio].nome_prof <<" excluido" <<endl;
    } else {
        cout << "Professor(a) nao encontrado." <<endl;
    }
}

void leituraExaustivaProfessor(struct idx_professores indiceProfessor[], struct professores professor[], int contadorProfessor){
    for(int k = 0; k < contadorProfessor; k++){
        int i = indiceProfessor[k].end_professor;
        if(professor[i].statusProfessor == 0){
            cout << "\n\nNome do professor(a): " << professor[i].nome_prof;
            cout << "\nEndereco do professor(a): " << professor[i].endereco;
            cout << "\nTelefone do professor(a): " << professor[i].telefone;
        }
    }
}


void reorganizacaoProfessor(struct professores professor[], struct idx_professores indiceProfessor[], 
int contadorProfessor, struct professores novoProfessor[], struct idx_professores novoIndiceProfessor[], int &novoContadorProfessor){
	int i = 0;
	int j = 0;
	novoContadorProfessor = 0;
	for(; j <= contadorProfessor; j++){
		i = indiceProfessor[j].end_professor;
			if(professor[i].statusProfessor == 0){
				novoProfessor[novoContadorProfessor].codigo_professor = professor[i].codigo_professor;
				novoProfessor[novoContadorProfessor].nome_prof = professor[i].nome_prof;
				novoProfessor[novoContadorProfessor].endereco = professor[i].endereco;
				novoProfessor[novoContadorProfessor].telefone = professor[i].telefone;
				novoProfessor[novoContadorProfessor].statusProfessor = professor[i].statusProfessor;
				
				novoIndiceProfessor[novoContadorProfessor].cod_professor = indiceProfessor[j].cod_professor;
				indiceProfessor[novoContadorProfessor].end_professor = novoContadorProfessor;
				novoContadorProfessor++;
		}
	}
}


void novoReorganizacaoProfessor(struct professores novoProfessor[], struct idx_professores novoIndiceProfessor[], int &novoContadorProfessor,
						 	struct professores professor[], struct idx_professores indiceProfessor[], int &contadorProfessor){
	contadorProfessor = novoContadorProfessor;
	professor = novoProfessor;
	indiceProfessor = novoIndiceProfessor;
}

//FIM FROPESSOR

//BLOCO MOVIMENTAÇÕES NA MODALIDADE


int buscarProfessorModalidade(struct idx_professores indiceProfessor[], int contadorProfessor, int codigoDoProfessor) {
    int inicio = 0, fim = contadorProfessor - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigoDoProfessor != indiceProfessor[meio].cod_professor; meio = (inicio + fim) / 2) {
        if (codigoDoProfessor > indiceProfessor[meio].cod_professor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (codigoDoProfessor == indiceProfessor[meio].cod_professor) {
        return indiceProfessor[meio].end_professor;
    } else {
        return -1;
    }
}

int buscarModalidadeExistente(struct idx_modalidades indiceModalidade[], int &contadorModalidade, int &codigoModalidade) {
    int inicio = 0, fim = contadorModalidade - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigoModalidade != indiceModalidade[meio].cod_modalidade; meio = (inicio + fim) / 2) {
        if (codigoModalidade > indiceModalidade[meio].cod_modalidade) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (codigoModalidade == indiceModalidade[meio].cod_modalidade) {
        return indiceModalidade[meio].end_modalidade;
    } else {
        return -1;
    }
}

void inserir_modalidade(struct modalidades modalidade[], struct idx_modalidades indiceModalidade[], int &contadorModalidade,
                           struct professores professor[], struct idx_professores indiceProfessor[],
                           int &contadorProfessor) {
    cout << "\n\n\n************* CADASTRAR NOVAS MODALIDADES ****************";

    const int tamanhoMaximoVetor = 8;

    for (int i = 4; i < tamanhoMaximoVetor;) {
        

        bool modalidadeExiste = false;
        while (!modalidadeExiste) {
            cout << "\n\n*Digite o codigo da Modalidade (padrao 88) " << "(digite 0 para sair): ";
            cin >> modalidade[i].codigo_modalidade;
            if (modalidade[i].codigo_modalidade == 0) {
                break;
            }
            int validarCodigo = buscarModalidadeExistente(indiceModalidade, contadorModalidade, modalidade[i].codigo_modalidade);
            if (validarCodigo != -1) {
                cout << "Codigo ja cadastrado para Modalidade: " << modalidade[validarCodigo].descricao;
            } else {
                modalidadeExiste = true;
            }
        }
        if (modalidade[i].codigo_modalidade == 0) {
            break;
        }
        cin.ignore();
        bool descricaoNaoVazia = false;
        while (!descricaoNaoVazia) {
            cout << "\nDescrição da Modalidade: ";
            getline(cin, modalidade[i].descricao);
            if (modalidade[i].descricao != "") {
                descricaoNaoVazia = true;
            } else {
                cout << "Descrição não pode ser vazia" << endl;
            }
        }

        cout << "\nTotal de alunos cadastrados na Modalidade: ";
        cin >> modalidade[i].total_alunos;

        bool maiorQue0 = false;
        while (!maiorQue0) {
            cout << "\nLimite de alunos que podem estar cadastrado na Modalidade: ";
            cin >> modalidade[i].limite_alunos;
            if (modalidade[i].limite_alunos <= 0) {
                cout << "Limite deve ser maior que 0" << endl;
            } else if(modalidade[i].total_alunos > modalidade[i].limite_alunos){
                cout <<"O limite deve ser maior que o numero de cadastrados" << endl;
            } else {
                maiorQue0 = true;
            }
        }
        cout << "\nValor da aula da Modalidade: ";
        cin >> modalidade[i].valor_aula;

        bool encontrouProfessor = false;
        while (!encontrouProfessor) {
            cout << "\nCódigo do professor da Modalidade: ";
            cin >> modalidade[i].cod_prof;
            int codigoASerProcurado = modalidade[i].cod_prof;
            int resultadoBuscarProfessor = buscarProfessorModalidade(indiceProfessor, contadorProfessor, codigoASerProcurado);
            if (resultadoBuscarProfessor == -1) {
                cout << "Professor não encontrado, digite um código existente";
            } else {
                cout << "Professor(a): " << professor[resultadoBuscarProfessor].nome_prof << endl;
                encontrouProfessor = true;
            }
        }

        int j;
        for (j = contadorModalidade - 1;
             j >= 0 && modalidade[i].codigo_modalidade < indiceModalidade[j].cod_modalidade; j--) {
            indiceModalidade[j + 1] = indiceModalidade[j];
        }
        indiceModalidade[j + 1].cod_modalidade = modalidade[i].codigo_modalidade;
        indiceModalidade[j + 1].end_modalidade = i;
        cout << "\n***Modalidade cadastrada com Sucesso***" << endl;
        contadorModalidade++;
        i++;
    }
    cout << "\n\nSaindo da insercao de modalidades....";
    cin.ignore();
}


void exclusaoModalidade(struct idx_modalidades indiceModalidade[], struct modalidades modalidade[], int &contador, int &codigo){
    int inicio = 0, fim = contador - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigo != indiceModalidade[meio].cod_modalidade; meio = (inicio + fim) / 2) {
        if (codigo > indiceModalidade[meio].cod_modalidade) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    inicio = indiceModalidade[meio].end_modalidade;
    if((codigo == indiceModalidade[meio].cod_modalidade) && modalidade[inicio].statusModalidade == 0){
        modalidade[inicio].statusModalidade = 1;
        cout << "Modalidade " << modalidade[inicio].descricao << " excluida"<<endl;
    } else {
        cout << "Modalidade nao encontrada." <<endl;
    }
}

void leituraExaustivaModalidade(struct idx_modalidades indiceModalidade[], struct modalidades modalidade[], int contadorModalidade, professores professor[]){
    for(int k = 0; k < contadorModalidade; k++){
        int i = indiceModalidade[k].end_modalidade;
        if(modalidade[i].statusModalidade == 0){
        	cout << "\n\nCodigo da modalidade: " << modalidade[i].codigo_modalidade;
            cout << "\nDescricao da modalidade: " << modalidade[i].descricao;
            cout << "\nCodigo do professor: " << modalidade[i].cod_prof;
            cout << "\nNome do professor: " << professor[i].nome_prof;
            cout << "\nLimite de alunos: " << modalidade[i].limite_alunos;
            cout << "\nTotal de alunos: " << modalidade[i].total_alunos;
            cout << "\nValor da aula: " << modalidade[i].valor_aula;
        }
    }
}

void reorganizacaoModalidade(struct modalidades modalidade[], struct idx_modalidades indiceModalidade[], 
							int &contadorModalidade, struct modalidades novoModalidade[], struct idx_modalidades novoIndiceModalidade[], int &novoContadorModalidade){
	int i = 0;
	int j = 0;
	novoContadorModalidade = 0;
	for(; j <= contadorModalidade; j++){
		i = indiceModalidade[j].end_modalidade;
			if(modalidade[i].statusModalidade == 0){
				novoModalidade[novoContadorModalidade].codigo_modalidade = modalidade[i].codigo_modalidade;
				novoModalidade[novoContadorModalidade].descricao = modalidade[i].descricao;
				novoModalidade[novoContadorModalidade].cod_prof = modalidade[i].cod_prof;
				novoModalidade[novoContadorModalidade].valor_aula = modalidade[i].valor_aula;
				novoModalidade[novoContadorModalidade].limite_alunos = modalidade[i].limite_alunos;
				novoModalidade[novoContadorModalidade].total_alunos = modalidade[i].total_alunos;
				novoModalidade[novoContadorModalidade].statusModalidade = modalidade[i].statusModalidade;
				
				novoIndiceModalidade[novoContadorModalidade].cod_modalidade = indiceModalidade[j].cod_modalidade;
				indiceModalidade[novoContadorModalidade].end_modalidade = novoContadorModalidade;
				novoContadorModalidade++;
		}
	}
}

void novoReorganizacaoModalidade(struct modalidades novoModalidade[], struct idx_modalidades novoIndiceModalidade[], int &novoContadorModalidade,
						 	struct modalidades modalidade[], struct idx_modalidades indiceModalidade[], int &contadorModalidade){
	contadorModalidade = novoContadorModalidade;
	modalidade = novoModalidade;
	indiceModalidade = novoIndiceModalidade;
}

//FIM MODALIDADE

//BLOCO MOVIMENTAÇÕES STRUCT MATRICULA

int buscarModalidadeMatricula(struct idx_modalidades indiceModalidade[], int &contadorModalidade, int codigoModalidade) {
    int inicio = 0, fim = contadorModalidade - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigoModalidade != indiceModalidade[meio].cod_modalidade; meio = (inicio + fim) / 2) {
        if (codigoModalidade > indiceModalidade[meio].cod_modalidade) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (codigoModalidade == indiceModalidade[meio].cod_modalidade) {
        return indiceModalidade[meio].end_modalidade;
    } else {
        return -1;
    }
}

int buscarAlunoMatricula(struct idx_alunos indiceAluno[], int &contadorAluno, int cpfDoAluno) {
    int inicio = 0, fim = contadorAluno - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && cpfDoAluno != indiceAluno[meio].cpf_alu; meio = (inicio + fim) / 2) {
        if (cpfDoAluno > indiceAluno[meio].cpf_alu) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (cpfDoAluno == indiceAluno[meio].cpf_alu) {
        return indiceAluno[meio].end_aluno;
    } else {
        return -1;
    }
}

int buscarMatricula(struct idx_matriculas indiceMatricula[], int contadorMatricula, int codigoDaMatricula) {
    int inicio = 0, fim = contadorMatricula - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigoDaMatricula != indiceMatricula[meio].cod_matricula; meio = (inicio + fim) / 2) {
        if (codigoDaMatricula > indiceMatricula[meio].cod_matricula) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (codigoDaMatricula == indiceMatricula[meio].cod_matricula) {
        return indiceMatricula[meio].end_matricula;
    } else {
        return -1;
    }
}

void inserir_matricula(struct matriculas matricula[], struct idx_matriculas indiceMatricula[], int &contadorMatricula, 
					  struct modalidades modalidade[ ], struct idx_modalidades indiceModalidade[], int &contadorModalidade,
					 struct alunos aluno[], idx_alunos indiceAluno[], int &contadorAluno) {
    cout << "\n\n\n***** CADASTRAR NOVAS MATRICULAS ******";
    const int tamanhoMaximoVetor = 10;

    for(int i = 4; i < tamanhoMaximoVetor;){
        cout << "\nQUAL INDICE QUE EU TO?: " << i;

        bool matriculaExiste = false;
        while(!matriculaExiste) {
            cout << "\n\n*Digite o código da Matricula" << "(digite 0 para sair): ";
            cin >> matricula[i].codigo_matricula;
            if (matricula[i].codigo_matricula == 0) {
                break;
            }
            int validarCodigo = buscarMatricula(indiceMatricula, contadorMatricula, matricula[i].codigo_matricula);
            if (validarCodigo != -1) {
                cout << "Codigo já cadastrado na matricula do CPF: " << matricula[validarCodigo].cpf_aluno << endl;
            } else {
                matriculaExiste = true;
            }
        }
        if (matricula[i].codigo_matricula == 0) {
            break;
        }

        bool cpfExiste = false;
        while(!cpfExiste){
            cout << "Digite o CPF do aluno: ";
            cin >> matricula[i].cpf_aluno;
            int cpfProcurado = matricula[i].cpf_aluno;
            int resultadoBuscaCpf = buscarAlunoMatricula(indiceAluno, contadorAluno, cpfProcurado);
            if (resultadoBuscaCpf != -1) {
                cout << "Nome do Aluno(a): " << aluno[resultadoBuscaCpf].nome_aluno << endl;
                cpfExiste = true;
            } else {
                cout << "Aluno(a) não encontrado." << endl;
            }
        }

        bool modalidadeExiste = false;
        while(!modalidadeExiste){
            cout << "Digite o código da modalidade: ";
            cin >> matricula[i].cod_modalidade;
            int modalidadeProcurada = matricula[i].cod_modalidade;
            int resultadoBuscaModalidade = buscarModalidadeMatricula(indiceModalidade, contadorModalidade, modalidadeProcurada);
            if(resultadoBuscaModalidade != -1){
                cout << "Modalidade: " << modalidade[resultadoBuscaModalidade].descricao << endl;
            } else {
                cout <<"Modalidade não encontrada." << endl;
                continue;
            }
            int pessoasCadastradasNaModalidade = modalidade[resultadoBuscaModalidade].total_alunos;
            int limiteDePessoasNaModalidade = modalidade[resultadoBuscaModalidade].limite_alunos;

            if (pessoasCadastradasNaModalidade < limiteDePessoasNaModalidade) {
                cout << "\nHá vagas disponiveis nessa modalidade" << endl;
                modalidade[resultadoBuscaModalidade].total_alunos = modalidade[resultadoBuscaModalidade].total_alunos + 1;
                cout << "\n****Aluno matriculado com sucesso!" << endl;
                cout << "\nAlunos matriculados: " << modalidade[resultadoBuscaModalidade].total_alunos << endl;
                cout << "Limite de alunos da modalidade: " << limiteDePessoasNaModalidade << endl;
                modalidadeExiste = true;
            } else {
                cout << "\nNão há vagas disponíveis nessa modalidade." << endl;
            }
        }
        bool qtdeAulas = false;
        while(!qtdeAulas){
            cout << "Quantidade de aulas: ";
            cin >> matricula[i].qtde_aulas;

            if(matricula[i].qtde_aulas <= 0){
                cout << "O numero de aulas não pode ser igual ou menor que 0" <<endl;
            } else {
                qtdeAulas = true;
            }
        }
        int j;
        for (j = contadorMatricula - 1; j >= 0 && matricula[i].codigo_matricula < indiceMatricula[j].cod_matricula; j--) {
            indiceMatricula[j + 1] = indiceMatricula[j];
        }
        indiceMatricula[j + 1].cod_matricula = matricula[i].codigo_matricula;
        indiceMatricula[j + 1].end_matricula = i;
        cout << "\n**Matricula cadastrada com Sucesso**" << endl;
        contadorMatricula++;
        i++;
    }

}





void exclusaoMatricula(struct idx_matriculas indiceMatricula[], struct matriculas matricula[], int &contadorMatricula, int &codigo){
    int inicio = 0, fim = contadorMatricula - 1;
    int meio = (inicio + fim) / 2;
    for (; fim >= inicio && codigo != indiceMatricula[meio].cod_matricula; meio = (inicio + fim) / 2) {
        if (codigo > indiceMatricula[meio].cod_matricula) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    inicio = indiceMatricula[meio].end_matricula;
    if((codigo == indiceMatricula[meio].cod_matricula) && matricula[inicio].statusMatricula == 0){
        matricula[inicio].statusMatricula = 1;
        cout << "Matricula " << matricula[inicio].codigo_matricula << " excluida"<<endl;
    } else {
        cout << "Matricula nao encontrada." <<endl;
    }
}

void leituraExaustivaMatricula(struct idx_matriculas indiceMatricula[], struct matriculas matricula[], int contadorMatricula, alunos aluno[]){
    for(int k = 0; k < contadorMatricula; k++){
        int i = indiceMatricula[k].end_matricula;
        if(matricula[i].statusMatricula == 0){
            cout << "\n\nCodigo da matricula: " << matricula[i].codigo_matricula;
            cout << "\nCodigo da modalidade: " << matricula[i].cod_modalidade;
            cout << "\nCPF do aluno: " << matricula[i].cpf_aluno;
            cout << "\nNome do aluno: " << aluno[i].nome_aluno;
            cout << "\nQuantidade de aulas: " << matricula[i].qtde_aulas;
        }
    }
}


void reorganizacaoMatricula(struct matriculas matricula[], struct idx_matriculas indiceMatricula[], int &contadorMatricula, 
							struct matriculas novoMatricula[], struct idx_matriculas novoIndiceMatricula[], int &novoContadorMatricula){
	int i = 0;
	int j = 0;
	novoContadorMatricula = 0;
	for(; j <= contadorMatricula; j++){
		i = indiceMatricula[j].end_matricula;
			if(matricula[i].statusMatricula == 0){
				novoMatricula[novoContadorMatricula].codigo_matricula = matricula[i].codigo_matricula;
				novoMatricula[novoContadorMatricula].cod_modalidade = matricula[i].cod_modalidade;
				novoMatricula[novoContadorMatricula].cpf_aluno = matricula[i].cpf_aluno;
				novoMatricula[novoContadorMatricula].qtde_aulas = matricula[i].qtde_aulas;
				novoMatricula[novoContadorMatricula].statusMatricula = matricula[i].statusMatricula;

				novoIndiceMatricula[novoContadorMatricula].cod_matricula = indiceMatricula[j].cod_matricula;
				indiceMatricula[novoContadorMatricula].end_matricula = novoContadorMatricula;
				novoContadorMatricula++;
		}
	}
}

void novoReorganizacaoMatricula(struct matriculas novoMatricula[], struct idx_matriculas novoIndiceMatricula[], int &novoContadorMatricula,
						 		struct matriculas matricula[], struct idx_matriculas indiceMatricula[], int &contadorMatricula){
	contadorMatricula = novoContadorMatricula;
	matricula = novoMatricula;
	indiceMatricula = novoIndiceMatricula;
}

//FIM MATRICULA

//VALOR FATURADO MODALIDADE

/*void calcularLucro(struct idx_modalidades indiceModalide[], struct modalidades modalidade[], struct idx_matriculas indiceMatricula[], 
					struct matriculas matricula[], struct idx_professores indiceProfessor[], struct professores professor[], 
						int &contadorModalidade, int &contadorMatricula, int &contadorProfessor){
    int codigoDaModalidade;
    cout << "\n\n\tDigite o codigo da modalidade: ";
    cin >> codigoDaModalidade;
    
	int resultadoBuscaModalidade = buscarModalidadeExistente(indiceModalide, contadorModalidade, codigoDaModalidade);
	float valorDaAula = modalidade[resultadoBuscaModalidade].valor_aula;
	cout << "\n\n\tValor da aula: " << valorDaAula;
	
	
	int codigoDoProfessor = modalidade[resultadoBuscaModalidade].cod_prof;
    int resultadobuscaProfessor = buscarProfessorExistente(indiceProfessor, contadorProfessor, codigoDoProfessor);
    
    cout << "\n\n\tDescricao: " << modalidade[resultadoBuscaModalidade].descricao;
    cout << "\n\n\tProfessor(a): " << professor[resultadobuscaProfessor].nome_prof;
     /*int resultadoBuscaModalidade = buscarModalidadeExistente(indiceModalide, contadorModalidade, codigoDaModalidade);
     float valorDaAula = modalidade[resultadoBuscaModalidade].valor_aula;
     int codigoDoProfessor = modalidade[resultadoBuscaModalidade].cod_prof;
     int resultadobuscaProfessor = buscarProfessorExistente(indiceProfessor, contadorProfessor, codigoDoProfessor);
     cout << "Descrição: " << modalidade[resultadoBuscaModalidade].descricao;
     cout << "Professor(a): " << professor[resultadobuscaProfessor].nome_prof;
    int quantidadeDeAula = 0;
    for(int i = 0; i < contadorMatricula; i++){
        if(codigoDaModalidade == matricula[i].codigo_matricula){
            quantidadeDeAula += matricula[i].qtde_aulas;
        }
    }
     
    cout << "\n\n\tQtde de aulas: " << quantidadeDeAula;
    cout << "\n\n\tLucro: " << quantidadeDeAula * valorDaAula;
}*/

void calcularLucro(struct idx_modalidades indiceModalidade[], struct modalidades modalidade[], struct idx_matriculas indiceMatricula[], struct matriculas matricula[], 
					struct idx_professores indiceProfessor[], struct professores professor[], int &contadorModalidade, int &contadorMatricula, int &contadorProfessor){
    int codigoDaModalidade;
    cout << "Digite o codigo da modalidade: ";
    cin >> codigoDaModalidade;

    int resultadoBuscaModalidade = buscarModalidadeExistente(indiceModalidade, contadorModalidade, codigoDaModalidade);
    float valorDaAula = modalidade[resultadoBuscaModalidade].valor_aula;
    int codigoDoProfessor = modalidade[resultadoBuscaModalidade].cod_prof;
    int resultadobuscaProfessor = buscarProfessorExistente(indiceProfessor, contadorProfessor, codigoDoProfessor);
    cout << "\nDescricao: " << modalidade[resultadoBuscaModalidade].descricao;
    cout << "\nProfessor(a): " << professor[resultadobuscaProfessor].nome_prof;
    cout << "\nValor da aula: " << valorDaAula;


     int quantidadeDeAula = 0;
     for(int i = 0; i < contadorMatricula; i++){
         if(codigoDaModalidade == matricula[i].cod_modalidade){
             quantidadeDeAula += matricula[i].qtde_aulas;
         }
     }
     cout <<"\nQuantidade de aula: " << quantidadeDeAula;
     float lucro = quantidadeDeAula * valorDaAula;
     cout << "\nLucro: " << lucro;
}



int main(){

	struct alunos aluno[8] = {
		{1111,"isabela","16/02/04",67,1.60,0},
		{3333,"pedro","16/10/98",78,1.80,0},
		{2222,"raquel","11/05/04",60,1.58,0},
		{4444, "vitor", "31/01/03", 92, 1.82, 0}
	};
	struct idx_alunos indiceAluno[8] = {
		{1111,0},
		{2222,1},
		{3333,2},
		{4444, 3}
	};
	struct professores professor[8] = {
		{8,"Bruno","ruaA", "996773701",0},
		{10,"Begosso","ruaB", "996858527",0},
		{6,"Talo","ruaC", "997882040",0},
		{12, "Diomara", "ruaD", "996070806", 0}
	};
	struct idx_professores indiceProfessor[8] = {
		{6,1},
		{12,3},
		{8,0},
		{10,2}
	};
	struct modalidades modalidade[8] = {
		{2,"musculacao",10,100,10,2,0},
		{3,"pilates",8,150,8,1,0},
		{1,"crossfit",6,120,5,1,0},
		{4, "muay thai", 12, 110, 6, 3, 0}
	};
	struct idx_modalidades indiceModalidade[8] = {
		{1,2},
		{2,0},
		{3,1},
		{4, 3}
	};
	struct matriculas matricula[8] = {
		{12,2222,3,2,0},
		{13,3333,2,5,0},
		{11,1111,4,5,0},
		{14,4444,1,3,0}
	};
	struct idx_matriculas indiceMatricula[8] = {
		{11,2},
		{12,0},
		{13,1},
		{14,3}
	};
	
	int contadorAluno = 4;
	int contadorProfessor = 4;
	int contadorModalidade = 4;
	int contadorMatricula = 4;
	int fim = -1;
	int sair;
	int opcao;
	long int cpf; 
	int cod;
	
	struct alunos novoAluno[8];
	struct idx_alunos novoIndiceAluno[8];
	int novoContadorAluno;
	
	struct professores novoProfessor[8];
	struct idx_professores novoIndiceProfessor[8];
	int novoContadorProfessor;
	
	struct modalidades novoModalidade[8];
	struct idx_modalidades novoIndiceModalidade[9];
	int novoContadorModalidade;
	
	struct matriculas novoMatricula[8];
	struct idx_matriculas novoIndiceMatricula[8];
	int novoContadorMatricula;
	
	while(sair == 0){
		system("cls");
		cout << "\t\tOpcoes:\n\n";
		cout << "\t\t\t1 - Inserir aluno \n\n";
		cout << "\t\t\t2 - Excluir aluno \n\n";
		cout << "\t\t\t3 - Leitura exaustiva dos alunos \n\n";
		cout << "\t\t\t4 - Reorganizar indices dos alunos \n\n";
		cout << "\t\t\t5 - Inserir professor \n\n";
		cout << "\t\t\t6 - Excluir professor \n\n";
		cout << "\t\t\t7 - Leitura exaustiva professor \n\n";
		cout << "\t\t\t8 - Reorganizar indices dos professores \n\n";
		cout << "\t\t\t9 - Inserir modalidade\n\n";
		cout << "\t\t\t10 - Excluir modalidade\n\n";
		cout << "\t\t\t11 - Leitura exaustiva modalidade \n\n";
		cout << "\t\t\t12 - Reorganizar indices das modalidades \n\n";
		cout << "\t\t\t13 - Inserir matricula\n\n";
		cout << "\t\t\t14 - Excluir matricula\n\n";
		cout << "\t\t\t15 - Leitura exaustiva matricula \n\n";
		cout << "\t\t\t16 - Reorganizar indices das matriculas \n\n";
		cout << "\t\t\t17 - calcular faturamento \n\n";
		cout << "\t\t\t18 - Encerrar o programa\n\n";
		cout << "\t\tESCOLHA: ";
		cin >> opcao;
		
		
		switch(opcao){
			
			case 1:{
				system("cls");
            	inserir_aluno(aluno, indiceAluno, contadorAluno);
				cout<<" \n\nTecle algo para retornar ao Menu." << endl;
				getch();
				break;
			}
			
			case 2:{
				system("cls");
        		cout << "\n\nInforme o CPF do aluno a ser EXCLUIDO (0 para Encerrar): ";
        		cin >> cpf;
        		if (cpf != 0)
            	exclusaoAluno(indiceAluno, aluno, contadorAluno, cpf);
            	cout << " \n\nTecle algo para retornar ao Menu." << endl;
				getch();
				break;
			}
			
			case 3:{
				system("cls");
				leituraExaustivaAluno(indiceAluno, aluno, contadorAluno);
				getch();
				break;
			}
			
			case 4:{
				system("cls");
				reorganizacaoAluno(aluno, indiceAluno, contadorAluno, novoAluno, novoIndiceAluno, novoContadorAluno);
				getch();
				
				cout<<"Reorganizando...\n\n Tecle algo para finalizar."<<endl;
				novoReorganizacaoAluno(novoAluno, novoIndiceAluno, novoContadorAluno, aluno, indiceAluno, contadorAluno);
				cout<<"\n\nReorganizacao de indice de alunos concluida com sucesso! \n\n Tecle algo para retornar ao menu principal"<<endl;
				
				getch();
				break;
		}		
			
			case 5:{	
				system("cls");
             	inserir_professor(indiceProfessor, professor, contadorProfessor);
				getch();
				break;
			}
			
			case 6:{
				system("cls");
				cout << "\n\nInforme o codigo do PROFESSOR a ser EXCLUIDO (0 para Encerrar): ";
        		cin >> cod;
        		if (cod != 0)
					exclusaoProfessor(indiceProfessor, professor, contadorProfessor, cod);
				cout<<" \n\nTecle algo para retornar ao Menu."<<endl;
				getch();
				break;	
			}
			
			case 7:{
				system("cls");
				leituraExaustivaProfessor(indiceProfessor, professor, contadorProfessor);
				getch();
				break;
			}
			
			case 8:{
				system("cls");
				reorganizacaoProfessor(professor, indiceProfessor, contadorProfessor, novoProfessor, novoIndiceProfessor, novoContadorProfessor);
				getch();
				
				cout << "Reorganizando...\n\n Tecle algo para finalizar."<<endl;
				novoReorganizacaoProfessor(novoProfessor, novoIndiceProfessor, novoContadorProfessor, professor, indiceProfessor, contadorProfessor);
				cout << "Reorganização concluida com sucesso! Tecle para retornar." << endl;
				getch();
				break;
			}
			
			case 9:{
				system("cls");
             		inserir_modalidade(modalidade, indiceModalidade, contadorModalidade, professor, indiceProfessor, contadorProfessor);
				cout<<" \n\nTecle algo para retornar ao Menu." << endl;
				getch();
				break;
			}
			
			case 10:{
				system("cls");
				cout << "\n\nInforme o codigo da MODALIDADE a ser EXCLUIDA (0 para Encerrar): ";
        		cin >> cod;
        		if (cod != 0)
					exclusaoModalidade(indiceModalidade, modalidade, contadorModalidade, cod);
				cout<<" \n\nTecle algo para retornar ao Menu."<<endl;
				getch();
				break;	
			}
			
			case 11:{
				system("cls");
				leituraExaustivaModalidade(indiceModalidade, modalidade, contadorModalidade, professor);
				getch();
				break;
			}
			
			case 12:{
				system("cls");
				reorganizacaoModalidade(modalidade, indiceModalidade, contadorModalidade, novoModalidade, novoIndiceModalidade, novoContadorModalidade);
				getch();
				
				cout << "Reorganizando...\n\n Tecle algo para finalizar."<<endl;
				novoReorganizacaoModalidade(novoModalidade, novoIndiceModalidade, novoContadorModalidade, modalidade, indiceModalidade, contadorModalidade);
				cout << "Reorganização concluida com sucesso! Tecle para retornar." << endl;
				getch();
				break;
			}			
			
			case 13:{
				system("cls");
             	inserir_matricula(matricula, indiceMatricula, contadorMatricula, modalidade, indiceModalidade, contadorModalidade, aluno, indiceAluno, contadorAluno);
				cout<<" \n\nTecle algo para retornar ao Menu." << endl;
				getch();
				break;
			}
			
			case 14:{
				system("cls");
				cout << "\n\nInforme o codigo da MATRICULA a ser EXCLUIDA (0 para Encerrar): ";
        		cin >> cod;
        		if (cod != 0)
					exclusaoMatricula(indiceMatricula, matricula, contadorMatricula, cod);
				cout<<" \n\nTecle algo para retornar ao Menu."<<endl;
				getch();
				break;			
			} 
			
			case 15:{
				system("cls");
				leituraExaustivaMatricula(indiceMatricula, matricula, contadorMatricula, aluno);
				getch();
				break;
			}
			
			case 16:{
				system("cls");
				reorganizacaoMatricula(matricula, indiceMatricula, contadorMatricula, novoMatricula, novoIndiceMatricula, novoContadorMatricula);
				getch();
				
				cout << "Reorganizando...\n\n Tecle algo para finalizar."<<endl;
				novoReorganizacaoMatricula(novoMatricula, novoIndiceMatricula, novoContadorMatricula, matricula, indiceMatricula, contadorMatricula);
				cout << "\aReorganização concluida com sucesso! Tecle para retornar." << endl;
				getch();
				break;
			}
			
			case 17:{
				system("cls");
				calcularLucro(indiceModalidade, modalidade, indiceMatricula, matricula, indiceProfessor, professor, contadorModalidade, contadorMatricula, contadorProfessor);
				getch();
				break;
			}
			
			case 18:{
				system("cls");
				char Encerrar='N';
				cout<<"\n\nDeseja encerrar o programa? (S/N) : ";
				sair=toupper(getche());
				if(Encerrar=='S'){
					cout<<"\n\nSaindo do programa...";
					
				}
				getch();
				break;	
			} 	
		}
	}
	
}













