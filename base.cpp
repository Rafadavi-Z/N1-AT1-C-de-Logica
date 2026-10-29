#include <stdio.h>
#include <string.h> // biblioteca para poder modificar array de letras (strings) mais para frente no código
#include <locale.h> // biblioteca para poder botar o terminal do vscode em português
#include <windows.h> // bibliotecar para poder botar o terminal do windows em português

// tema será o cadastro de compra de uma loja de brinquedos
// trabalho feito por Rafael Davi e Maria Clara

    char nome[5][20];
    int id_compra[5], quantidade[5], busca, alternativa, total = 0, id_counter = 0, i;
    float custo[5], valor_venda[5], total_lucro = 0;

void cadastrar() {

    if (total >= 5) // caso total chegue no tamanho máximo do array, bloqueie de cadastrar mais coisas
    {
        printf("\nNão há mais espaço, tente novamente mais tarde\n");
    }

    printf("\nDigite o nome do produto\n");
    scanf("%s", nome[total]);

    printf("Qual a quantidade do produto?\n");
    scanf("%d", &quantidade[total]);
    if (quantidade[total] <= 0) // validação para garantir que não seja botado 0 ou números negativos na quantidade
    {
        printf("Erro: Quantidade digitada inválida, tente novamente\n");
        return;
    }

    printf("Qual é o preço do produto?\n");
    scanf("%f", &custo[total]);
    if (custo[total] <= 0) // validação para garantir que não seja botado 0 ou números negativos no preço
    {
        printf("Erro: Preço digitado inválido, tente novamente\n");
        return;
    }

    valor_venda[total] = custo[total] * quantidade[total];
    printf("O valor da venda ficou R$ %.2f\n", valor_venda[total]);

    id_compra[total] = 101 + id_counter; // conta para deixar o id sempre único

    printf("Cadastro Realizado.\n");
    printf("O Identificador Único da compra é %d\n", id_compra[total]);

    id_counter++; // váriavel extra que só serve para incrimentar o número do id, não posso usar "total" para isso pq como o total é decrementado no case 5, 2 produtos iriam ganhar o mesmo id
    total++;

}

void consultar() {

    printf("\nDigite o Identificador Único da compra: ");
    scanf("%d", &busca);

    for (i = 0; i < total; i++) 
    { 
        if (id_compra[i] == busca) 
        {
            printf("\n////-- Compra de ID %d Encontrada --////\n", id_compra[i]);
            printf("Nome: %s\n", nome[i]);
            printf("Quantidade: %d\n", quantidade[i]);
            printf("Preço por Unidade: R$ %.2f\n", custo[i]);
            printf("Valor da Compra: R$ %.2f\n", valor_venda[i]);
            printf("/////////////////////////////////////////\n");
            break;
        }
    }
    if (id_compra[i] != busca) // eu precisei fazer esse if pq caso o printf só estivesse fora do loop, toda vez que ele terminasse ia aparecer a mensagem de que o resgistro não existe, mesmo achando um resultado válido
    {
        printf("\nO registro não existe.\n");
    }

}

void listar() {

    if(total == 0) // caso não tenha nenhum registro válido, dizer que não tem registro e nem rodar o código
    {
        printf("\nNão existem registros\n");
    }
    else
    {
        for (i = 0; i < total; i++)
        { 
            printf("\n=====================================\n");
            printf("ID de compra -> %d\n", id_compra[i]);
            printf("Nome -> %s\n", nome[i]);
            printf("Quantidade -> %d\n", quantidade[i]);
            printf("Preço por Unidade -> R$ %.2f\n", custo[i]);
            printf("Valor da Compra -> R$ %.2f\n", valor_venda[i]);
            printf("=====================================\n");
        }
    }

}

void alterar() {

    printf("\nDigite o Identificador Único da compra: ");
    scanf("%d", &busca);

    for (i = 0; i < total; i++) 
    {
        if (id_compra[i] == busca)
        {
            // váriaveis temporarias para garantir que caso de erro na alteração, não salve o erro no cadastro principal 
            char nometemp[20];
            int quantidadetemp;
            float custotemp;

            printf("\n////-- Compra de ID %d Encontrada --////\n", id_compra[i]);

            printf("Digite o novo nome do produto\n");
            scanf("%s", nometemp);

            printf("Qual a nova quantidade do produto?\n");
            scanf("%d", &quantidadetemp);
            if (quantidadetemp <= 0) // você já sabe para que isso serve
            {
                printf("Erro: Quantidade digitada inválida, tente novamente\n");
                break;
            }

            printf("Qual é o novo preço do produto?\n");
            scanf("%f", &custotemp);
            if (custotemp <= 0)
            {
                printf("Erro: Preço digitado inválido, tente novamente\n");
                break;
            }

            // se chegou aqui é porque deu tudo certo, já dá para guardar as alterações no cadastro

            strcpy(nome[i], nometemp);
            quantidade[i] = quantidadetemp;
            custo[i] = custotemp;

            valor_venda[i] = custo[i] * quantidade[i];
            printf("O novo valor da venda ficou R$ %.2f\n", valor_venda[i]);

            printf("/////////////////////////////////////////\n");
            break;
        }
    }
    if (id_compra[i] != busca)
    {
        printf("\nO registro não existe.\n");
    }

}

void excluir() {

    printf("\nDigite o Identificador Único da compra: ");
    scanf("%d", &busca);

    for (i = 0; i < total; i++) // 1º loop serve para procurar o Id digitado
    {
        if (id_compra[i] == busca) // caso ache o registro, vai pegar o índice equivalente, exluir o registro e decrementar o total
        {
            for (int j = i; j < (total - 1); j++) // 2º loop serve para mover as compras em uma posição para a esquerda (isso vai agir como uma exclusão, pois uma compra será substituida) aliás se reusasse "i" aqui eu iria perder a posição original do 1º loop por isso criei uma váriavel local só para isso, aliás total precisa ser subtraido 1 para que quet j + 1 não vá além do último cadastro válido
            {
                id_compra[j] = id_compra[j + 1];
                strcpy(nome[j], nome[j + 1]); // aqui o motivo de "string.h" ser nescessária, não dava para fazer isso do jeito normal acho que por "nome" ser um array de array então teve que ser assim
                quantidade[j] = quantidade[j + 1];
                custo[j] = custo[j + 1];
                valor_venda[j] = valor_venda[j + 1];
            }
            total--;

            printf("\nCompra excluída com sucesso!\n");
            break;
        }
    }
    if (i == total) // caso não ache o registro, como i vai sair do "for" com o mesmo valor do total, vamos usar isso para dizer que o registro não foi encontrado 
    {
        printf("\nO registro não existe.\n");
    }

}

int main() {

    setlocale(LC_ALL, ".UTF-8"); // deixa o terminal do vscode em português

    SetConsoleCP(65001);       // permite botar caracteres em português no terminal do windows
    SetConsoleOutputCP(65001); // permite o terminal do windows mostrar caracteres em português

    do 
    {
        printf("\n--- Cadastro de Compra de Brinquedo ---\n");

        printf("1. Cadastrar\n");
        printf("2. Consultar\n");
        printf("3. Listar\n");
        printf("4. Alterar\n");
        printf("5. Excluir\n");
        printf("0. Sair\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &alternativa);

        switch (alternativa) 
        {
            case 1: // cadastrar - como total no começo é igual a zero e dps vai incrementando, dá para usar como índice
                cadastrar();
                break;

            case 2: // consultar
                consultar();
                break;

            case 3: // listar
                listar();
                break;

            case 4: // alterar
                alterar();
                break;

            case 5: // excluir
                excluir();
                break;
                
            case 0: // Sair
                printf("\nSessão encerrada.\n");
                break;

            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
    } while (alternativa != 0);

    for (i = 0; i < total; i++) // calculando os ganhos de todas vendas feitas no dia
    {
        total_lucro += valor_venda[i];
    }

    printf("\n=== Resumo do Dia ===\n");
    printf("Número de vendas feitas hoje: %d\n", total);
    printf("Total de Lucro hoje: R$ %.2f\n\n", total_lucro);

    return 0;
}