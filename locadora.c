#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // biblioteca para linux


// unindo CPF e CNPJ em um mesmo espaço
typedef union cpf_cnpj
{
    char cpf[11];
    char cnpj[14];
}
cpf_cnpj;


// estrutura de endereco
typedef struct endereco
{
    char *rua;
    int   num;
    char *bairro;
    char *cidade;
    char *estado;
}
endereco;


// estrutura de usuarios cadastrados (informações sobre o usuário)
typedef struct cadastros
{
    char     usuario[50];
    char     senha[50];
    char     *nome;
    char     *sobrenome;
    int       ano_nasc;
    char      num_cnh[9];
    cpf_cnpj  documento;
    long int  contato;
    endereco *end;
}
cadastros;

// estrutura de aluguel de veículo
typedef struct aluguel
{
    int op_valor;
    int op_carro;
    char op_modelo[20];
    int diaria;

} veiculos;


// declarando variáveis globais para pegar usuário e senha
char *usuario_digitado;
char *senha_digitada;


// Funções para solicitar usuario e senha
void solicitar_usuario();
void solicitar_senha();

// Função de cadastro
cadastros *cadastro_usuario();

// perguntas frequentes
void faq();

// carros
void carros();


int main(int argc, char *argv[])
{
    // declarando variáveis
    int         inicio; // variável para solicitar qual opção o usuário deseja
    cadastros  *usuario_cadastrado; // variável de cadastro
    // apresentação
    system("clear");
    printf("######## Bem-vindo a locadora Alugue Já! #######\n\n"); // saudação

    // solicitar opção que o usuário deseja
    printf("Digite a opção que deseja: \n\n"
           "Para fazer login com uma conta existente, digite 1\n\n"
           "Para cadastrar um usuário, digite 2\n\n"
           "Para suporte, digite 3\n\nDigite a opção que deseja: ");
    scanf("%i", &inicio);

    while (inicio < 1 || inicio > 3) // loop para repetir caso o usuário não digite nenhuma das 3 opções (1, 2, 3)
    {
        printf("Opção inválida!!\nDigite novamente: ");
        getchar();
        scanf("%i", &inicio);
    }


    // caso 1: login
    switch (inicio)
    {
        case 1:

            // limpar o terminal
            system("clear");

            // detalhe visual
            printf("######## LOGIN ########\n");

            // solicitando nome de usuario
            solicitar_usuario();
            // solicitando senha de login
            solicitar_senha();

            break;

        // case 2: Novo cadastro
        case 2:

            // limpar o terminal
            system("clear");

            // detalhe visual
            printf("######## CADASTRO DE USUÁRIO ########\n");

            // armazenar as informações do usuário em uma variável
            usuario_cadastrado = cadastro_usuario();

            // limpar o terminal
            system("clear");

            // mostrar na tela que o cadastro foi realizado
            printf("----------------------------------\n"
                   "| CADASTRO REALIZADO COM SUCESSO |\n"
                   "----------------------------------\n");

            // "redirecionar" para a tela de login
            printf("######## LOGIN ########\n");
            solicitar_usuario();
            solicitar_senha();

            break;

        // caso 3: informações
        case 3:
            printf("######## SUPORTE ########\n");

            // função que mostra as perguntas frequentes/informações para contato
            faq();

            // encerrar o programa
            return 0;
    } // fecha escopo do switch e entra no programa, depois do login.


    // limpar o terminal
    system("clear");

    // variáveis para o switch case

    int flag         = 1; // variável de controle da interface pós login
    do // do while para repetir o programa quantas vezes for necessário
    {
        // saudação ao usuário e perguntar o que deseja
        printf("----------------\n"
                "| BEM VINDO!!! |\n"
                "----------------\n"
                "Qual opção deseja?\n\n"
                "Digite 1 para ALUGAR um carro\n\n"
                "Digite 2 para INFORMAÇÕES E SUPORTE\n\n"
                "Digite 0 para FECHAR O APLICATIVO\n\n");
        scanf("%i", &flag); // pegar o que o usuário deseja

        // repetir a pergunta caso o usuário não digite uma opção válida
        while (flag != 0 && flag != 1 && flag != 2)
        {
            printf("OPÇÃO INVÁLIDA!!!\n"
                   "Digite novamente (1, 2, ou 0):\n");
            scanf("%i", &flag);
        }

        // switch para retornar a opção que o usuário digitou
        switch(flag)
        {
            case 0:
                // limpar o terminal
                system("clear");

                // encerrar o programa
                printf("Encerrando o programa!\n");

                // liberar memoria se o usuario entrou a partir do cadastro
                if (inicio == 2)
                {
                    free(usuario_cadastrado->end);
                    free(usuario_cadastrado);
                }

                return 0;

            case 1:
                // limpar o terminal
                system("clear");

                // função de aluguel de carros
                carros();

                break;

            case 2:
                // limpar o terminal
                system("clear");

                // mostrar perguntas frequentes e informações para suporte
                faq();

                // parar o programa por 5 segundos
                sleep(10);
                break;
        }

    }
    while(flag != 0);

    free(usuario_cadastrado->end);
    free(usuario_cadastrado);
}


// solicitar usuario
void solicitar_usuario()
{
    // alocar memoria para o usuario
    usuario_digitado = malloc(sizeof(char *));
    printf("Digite o nome de usuário: ");
    getchar(); // limpar buffer
    scanf("%[ -Ý]", usuario_digitado); // pegar o que foi digitado e armazenar na variável global
    printf("\n");

    // liberar a memoria
    free(usuario_digitado);
}

// solicitar senha
void solicitar_senha()
{
    // alocar memoria para a senha
    senha_digitada = malloc(sizeof(char *));
    printf("Digite a senha: ");
    getchar(); // limpar buffer
    scanf("%[ -Ý]", senha_digitada); // pegar o que foi digitado e armazenar na variável global
    printf("\n");

    // liberar a memoria
    free(senha_digitada);
}

// cadastrar usuario
cadastros *cadastro_usuario()
{
    // enum para pegar o tipo de documento (cpf ou cnpj)
    enum documento
    {
        cpf = 1,
        cnpj = 2
    };
    enum documento tipo_doc;

    // variavel temporaria para cadastro
    cadastros *usuario = malloc(sizeof(cadastros));

    // solicitando informações de cadastro
    // nome de usuario
    printf("##### INFORMAÇÕES DE LOGIN #####\n\n"); // detalhe visual
    printf("Nome de usuário: ");
    getchar();
    scanf("%[ -Ý]", usuario->usuario);

    // senha
    do // usar do while para executar as linhas de código ao menos 1 vez
    {
    printf("Senha (de 8 a 50 digitos): ");
    getchar();
    scanf("%[ -Ý]", usuario->senha);
    }
    while (strlen(usuario->senha) < 8 || strlen(usuario->senha) > 50);


    // nome
    usuario->nome = malloc(sizeof(char *));
    printf("##### INFORMAÇÕES DE CADASTRO #####\n\n"); // detalhe visual
    printf("Primeiro nome: ");
    getchar();
    scanf("%[ -Ý]", usuario->nome);

    // sobrenome
    usuario->sobrenome = malloc(sizeof(char *));
    printf("Sobrenome: ");
    getchar();
    scanf("%[ -Ý]", usuario->sobrenome);


    // Idade (ano de nascimento)
    printf("Ano de nascimento: ");
    getchar();
    scanf("%i", &usuario->ano_nasc);


    // número da cnh
    printf("Número de registro da CNH: ");
    getchar();
    scanf("%[ -Ý]", usuario->num_cnh);


    // tipo e numero do documento
    // loop para solicitar, checar tipo do doc e repetir se necessário
    do
    {
        printf("CPF ou CNPJ? (Digite 1 para CPF ou 2 para CNPJ)");
        getchar();
        scanf("%i", &tipo_doc);
    }
    while (tipo_doc != 1 && tipo_doc != 2);

    // switch case para solicitar o num do documento a partir do tipo
    switch (tipo_doc)
    {
        case cpf:
            printf("Nº do documento (apenas números): ");
            getchar();
            scanf("%[ -Ý]", usuario->documento.cpf);
            break;

        case cnpj:
            printf("Nº do documento (apenas números): ");
            getchar();
            scanf("%[ -Ý]", usuario->documento.cnpj);
            break;
    }


    // telefone para contato
    printf("Telefone para contato (apenas números): ");
    getchar();
    scanf("%li", &usuario->contato);


    // informações de endereço
    printf("##### ENDEREÇO #####\n\n"); // detalhe visual

    // alocar memoria para o endereco
    usuario->end = malloc(sizeof(char *));

    // rua
    usuario->end->rua = malloc(sizeof(char *));
    printf("Rua: ");
    getchar();
    scanf("%[ -Ý]", usuario->end->rua);

    // número
    printf("Número: ");
    scanf("%i", &usuario->end->num);

    // bairro
    usuario->end->bairro = malloc(sizeof(char *));
    printf("Bairro: ");
    getchar();
    scanf("%[ -Ý]", usuario->end->bairro);

    // cidade
    usuario->end->cidade = malloc(sizeof(char *));
    printf("Cidade: ");
    getchar();
    scanf("%[ -Ý]", usuario->end->cidade);

    // estado
    usuario->end->estado = malloc(sizeof(char *));
    printf("Estado: ");
    getchar();
    scanf("%[ -Ý]", usuario->end->estado);

    // retornar a variável temporária "usuario"
    return usuario;

}


void faq()
{
    // print para perguntas frequentes
    printf("------------------------\n"
        "| PERGUNTAS FREQUENTES |\n"
        "------------------------\n"
        "1. O que precisa para ALUGAR um de nossos carros?\n"
        "   º Ser maior de idade (18 anos+)\n"
        "   º Possuir Carteira Nacional de Habilitação (CNH) em dia\n"
        "   º Apresentação de documentos (CPF, ou CNPJ)\n"
        "   º Cartão válido e com limite\n\n"
        "2. Problemas com o carro (Acidente, pane, furto e roubo):\n"
        "   º Acidente:\n"
        "       > Em caso de acidentes, não se preoupe, você terá todo o nosso apoio.O primeiro passo é entrar em contato com as autoridades (Polícia, Bombeiros ou SAMU).\n"
        "       > Em seguida, entre em contato com a nossa Assistência pelo telefone ou WhatsApp (83) 9-9999-9999 para que possamos te auxiliar no que for preciso.\n"
        "       > Depois, você precisa registrar o Boletim de Ocorrência e ir até uma de nossas agências para preencher o Aviso de Sinistro.\n"
        "       > O Boletim de Ocorrência deve ser registrado no órgão responsável e apresentado no máximo em 48 horas a uma de nossas agências.\n\n"
        "   º Furto ou roubo do carro:\n"
        "       > Também receberá todo o nosso apoio\n"
        "       > Faça o registro do Boletim de Ocorrência no órgão responsável e comunique a nossa Central o ocorrido, pelo telefone ou WhatsApp de número (83) 9-9999-9999.\n"
        "       > Depois, com o BO em mãos, vá até uma de nossas agências para formalizar o aviso de Sinistro em até de 48 horas.\n\n"
        "   º Carro roubado e recuperado, mesmo assim tenho que pagar?\n"
        "       > Sim! Ainda que o carro tenha sido recuperado é necessário realizar o pagamento do Custo pré Fixado de Limite de Danos, conforme valores previstos no seu contrato.\n\n"
        "   º pane mecânica:\n"
        "       > Entre em contato imediatamente com a Assistência a Clientes 24h ((83) 9-9999-9999) para que possamos te auxiliar no que for preciso. O número também funciona como WhatsApp.\n"
        "       > Caso necessário, seu carro vai ser substituído por um da mesma categoria, sem nenhum custo adicional\n\n"
        "--------------------------------------------\n"
        "|  CASO NÃO TENHA ENCONTRADO SUA DÚVIDA    |\n"
        "|        ENTRE EM CONTATO CONOSCO:         |\n"
        "|            (83) 9-9999-9999              |\n"
        "--------------------------------------------\n\n"
        );

}

void carros()
{
    veiculos *veiculo = malloc(sizeof(veiculos));
    int ctrl = 0; // Variavel de controle de saida de do-while
    do
    {

        printf("-------------------\n"
               "|     ALUGUEL     |\n"
               "-------------------\n"
               "Quanto deseja gastar (orçamento)?\n\n"
               "Digite 1 para preços de R$ 100 a R$ 149\n\n"
               "Digite 2 para preços de R$ 150 a R$ 199\n\n"
               "Digite 3 para preços de R$ 200 a R$ 299\n\n"
               "Digite 4 para preços de acima de R$ 300\n\n"
               "Digite 0 para VOLTAR\n\n");
        scanf("%d", &veiculo->op_valor); // Armazena o grupo de orcamento

        system("clear");
        // voltar para o escopo principal caso o cliente digite 0
        if (veiculo->op_valor == 0)
        {
            system("clear");
            return;
        }

        switch (veiculo->op_valor) // swtich case para mostrar carros de acordo com o orçamento
        {
        // carros entre 100 e 149 reais
        case 1:
            do
            {
                printf("-----------------------\n"
                       "|   ESCOLHA UM CARRO  |\n"
                       "-----------------------\n"
                       "Qual carro voce deseja?\n\n"
                       "Digite 1 para Fiat Mobi\n"
                       "    preço R$100.00\n\n"
                       "Digite 2 para VW Gol\n"
                       "    preço R$110.00\n\n"
                       "Digite 3 para Renault Kwid\n"
                       "    preço R$120.00\n\n"
                       "Digite 4 para CHEV Onix Hatch\n"
                       "    preço R$130.00\n\n"
                       "Digite 5 para Hyundai HB20\n"
                       "    preço R$140.00\n\n"
                       "Digite 6 para Toyota Etios Hatch\n"
                       "    preço R$149.00\n\n"
                       "Digite 0 para VOLTAR\n\n");
                scanf("%d", &veiculo->op_carro); // Armazena o veiculo

                switch (veiculo->op_carro)
                {
                    // switch case para alterar e salvar dados do carro selecionado
                    case 1:
                        veiculo->op_valor = 100;                 // definir valor do veiculo
                        strcpy(veiculo->op_modelo, "Fiat Mobi"); // definir modelo do veiculo
                        ctrl = 1;                               // variável de controle para quebra o loop após o aluguel
                        break;

                    case 2:
                        veiculo->op_valor = 110;
                        strcpy(veiculo->op_modelo, "VW Gol");
                        ctrl = 1;
                        break;

                    case 3:
                        veiculo->op_valor = 120;
                        strcpy(veiculo->op_modelo, "Renault Kwid");
                        ctrl = 1;
                        break;

                    case 4:
                        veiculo->op_valor = 130;
                        strcpy(veiculo->op_modelo, "CHEV Onix Hatch");
                        ctrl = 1;
                        break;

                    case 5:
                        veiculo->op_valor = 140;
                        strcpy(veiculo->op_modelo, "Hyundai HB20");
                        ctrl = 1;
                        break;

                    case 6:
                        veiculo->op_valor = 149;
                        strcpy(veiculo->op_modelo, "Toyota Etios Hatch");
                        ctrl = 1;
                        break;

                    case 0: // Voltar
                        system("clear");
                        break;

                    default:
                        printf("DIGITE UM COMANDO VÁLIDO!!\n");
                        break;
                }

            }
            while ((veiculo->op_carro != 0) && (ctrl != 1)); // Enquanto alguma opcao valida nao for escolhida
            break;

        // carros entre 150 e 199 reais
        case 2:
            do
            {
                printf("-----------------------\n"
                       "|   ESCOLHA UM CARRO  |\n"
                       "-----------------------\n"
                       "Qual carro voce deseja?\n"
                       "Digite 1 para Fiat Cronos\n"
                       "    preço: R$150.00\n\n"
                       "Digite 2 para VW Virtus\n"
                       "    preço: R$160.00\n"
                       "Digite 3 para Renault Logan\n"
                       "    preço: R$170.00\n\n"
                       "Digite 4 para CHEV Prisma\n"
                       "    preço: R$180.00\n\n"
                       "Digite 5 para Hyundai HB20S\n"
                       "    preço: R$190.00\n\n"
                       "Digite 6 para Toyota Etios Sedan\n"
                       "    preço: R$199.00\n\n"
                       "Digite 0 para VOLTAR\n\n");
                scanf("%d", &veiculo->op_carro); // Armazena o veiculo

                switch (veiculo->op_carro) // mostrar carros que estão no orçamento digitado
                {
                    case 1:
                        veiculo->op_valor = 150;
                        strcpy(veiculo->op_modelo, "Fiat Cronos");
                        ctrl = 1;
                        break;

                    case 2:
                        veiculo->op_valor = 160;
                        strcpy(veiculo->op_modelo, "VW Virtus");
                        ctrl = 1;
                        break;

                    case 3:
                        veiculo->op_valor = 170;
                        strcpy(veiculo->op_modelo, "Renault Logan");
                        ctrl = 1;
                        break;

                    case 4:
                        veiculo->op_valor = 180;
                        strcpy(veiculo->op_modelo, "CHEV Prisma");
                        ctrl = 1;
                        break;

                    case 5:
                        veiculo->op_valor = 190;
                        strcpy(veiculo->op_modelo, "Hyundai HB20S");
                        ctrl = 1;
                        break;

                    case 6:
                        veiculo->op_valor = 199;
                        strcpy(veiculo->op_modelo, "Toyota Etios Sedan");
                        ctrl = 1;
                        break;

                    case 0: // Voltar
                        system("clear");
                        break;

                    default:
                        system("clear");
                        printf("DIGITE UM COMANDO VÁLIDO!!\n");
                        break;

                }
            }
            while ((veiculo->op_carro != 0) && (ctrl != 1));
            break;

        // carros entre 200 e 299 reais
        case 3:
            do
            {
                printf("-----------------------\n"
                       "|   ESCOLHA UM CARRO  |\n"
                       "-----------------------\n"
                       "Qual carro voce deseja?\n"
                       "Digite 1 para Fiat Pulse\n"
                       "    preço: R$200.00\n\n"
                       "Digite 2 para VW T-Cross\n"
                       "    preço: R$210.00\n\n"
                       "Digite 3 para Renault Duster\n"
                       "    preço: R$230.00\n\n"
                       "Digite 4 para Nissan Kicks\n"
                       "    preço: R$250.00\n\n"
                       "Digite 5 para Hyundai Creta\n"
                       "    preço: R$280.00\n\n"
                       "Digite 6 para Toyota Corolla\n"
                       "    preço: R$299.00\n\n"
                       "Digite 0 para VOLTAR\n");
                scanf("%d", &veiculo->op_carro); // Armazena o veiculo

                switch (veiculo->op_carro) // mostrar carros que estão entre o orçamento
                {
                    case 1:
                        veiculo->op_valor = 200;
                        strcpy(veiculo->op_modelo, "Fiat Pulse");
                        ctrl = 1;
                        break;

                    case 2:
                        veiculo->op_valor = 210;
                        strcpy(veiculo->op_modelo, "VW T-Cross");
                        ctrl = 1;
                        break;

                    case 3:
                        veiculo->op_valor = 230;
                        strcpy(veiculo->op_modelo, "Renault Duster");
                        ctrl = 1;
                        break;

                    case 4:
                        veiculo->op_valor = 250;
                        strcpy(veiculo->op_modelo, "Nissan Kicks");
                        ctrl = 1;
                        break;

                    case 5:
                        veiculo->op_valor = 280;
                        strcpy(veiculo->op_modelo, "Hyundai Creta");
                        ctrl = 1;
                        break;

                    case 6:
                        veiculo->op_valor = 299;
                        strcpy(veiculo->op_modelo, "Toyota Corolla");
                        ctrl = 1;
                        break;

                    case 0: // Voltar
                        system("clear");
                        break;

                    default:
                        system("clear");
                        printf("DIGITE UM COMANDO VÁLIDO!!\n");
                        break;

                }
            }
            while ((veiculo->op_carro != 0) && (ctrl != 1));
            break;

        // orçamento acima de 300 reais
        case 4:
            do
            {
                printf("-----------------------\n"
                       "|   ESCOLHA UM CARRO  |\n"
                       "-----------------------\n"
                       "Qual carro voce deseja?\n"
                       "Digite 1 para Mitsubishi Outlander\n"
                       "Digite R$310.00\n\n"
                       "Digite 2 para Audi A4\n"
                       "    preço: R$350.00\n\n"
                       "Digite 3 para BMW 320i\n"
                       "    preço: R$360.00\n\n"
                       "Digite 4 para Mercedes Benz A250\n"
                       "    preço: R$380.00\n\n"
                       "Digite 5 para CHEV S-10\n"
                       "    preço: R$385.00\n\n"
                       "Digite 6 para Toyota SW4\n"
                       "    preço: R$390.00\n\n"
                       "Digite 0 para Voltar\n");
                scanf("%d", &veiculo->op_carro); // Armazena o veiculo

                switch (veiculo->op_carro) // mostrar veículos dentro do orçamento
                {
                    case 1:
                        veiculo->op_valor = 310;
                        strcpy(veiculo->op_modelo, "Mitsubishi Outlander");
                        ctrl = 1;
                        break;

                    case 2:
                        veiculo->op_valor = 350;
                        strcpy(veiculo->op_modelo, "Audi A4");
                        ctrl = 1;
                        break;

                    case 3:
                        veiculo->op_valor = 360;
                        strcpy(veiculo->op_modelo, "BMW 320i");
                        ctrl = 1;
                        break;

                    case 4:
                        veiculo->op_valor = 380;
                        strcpy(veiculo->op_modelo, "Mercedes Benz A250");
                        ctrl = 1;
                        break;

                    case 5:
                        veiculo->op_valor = 385;
                        strcpy(veiculo->op_modelo, "CHEV S-10");
                        ctrl = 1;
                        break;

                    case 6:
                        veiculo->op_valor = 390;
                        strcpy(veiculo->op_modelo, "Toyota SW4");
                        ctrl = 1;
                        break;

                    case 0: // Voltar
                        system("clear");
                        break;

                    default:
                        system("clear");
                        printf("DIGITE UM COMANDO VÁLIDO!!\n");
                        break;

                }
            }
            while ((veiculo->op_carro != 0) && (ctrl != 1));
            break;

        default:
            system("clear");
            printf("DIGITE UM COMANDO VÁLIDO!!\n");
            break;

        }
    } while (ctrl != 1);

    // limpar terminal
    system("cls");
    // imprimir dados e finalizar aluguel
    printf("O modelo selecionado foi: %s\nValor da diaria: R$%d.00\n", veiculo->op_modelo, veiculo->op_valor);

    // perguntar quantas diárias
    printf("Quantas diárias voce deseja? (caso não deseje esse modelo, digite 0 para voltar)\n");
    scanf("%d", &veiculo->diaria);
    if (veiculo->diaria == 0)
    {
        system("cls");
        carros();
    }
    veiculo->op_valor *= veiculo->diaria;

    // mostrar o valor da quantidade de diarias digitadas
    if(veiculo->diaria != 0)
    {
        printf("Com %d diárias, o valor total à pagar é de: R$%d.00\n", veiculo->diaria, veiculo->op_valor);
        sleep(3);
    }

    // liberar a memoria
    free(veiculo);
}
