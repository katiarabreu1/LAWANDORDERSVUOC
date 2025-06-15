/*
   	CLIENT SIDE: http://www.professordiovani.com.br/sd/Sockets_cplus.htm
   	
	* Project -> Project Options -> Parameters -> Add library or Object -> 
	"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32/libws2_32.a"
	
	* Tools -> Compiler Options -> Add the following commands when calling the linker ->
	"-lws2_32"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
                    
#define TAM_BUFFER 128 //tamanho do buffer que carregará os dados via socket

int socket_remoto = 0; //handler para o socket remoto
int tam_msg = 0; //tamanho da mensagem a ser enviada
int porta_remota = 0; //porta do socket remoto
char ip_remoto[32]; //endereço ip do socket remoto
char msg[TAM_BUFFER]; //buffer que carregará a mensagem (texto)
struct sockaddr_in end_remoto; //struct para montar o endereço remoto
WSADATA sock_opt; //dados para setar opções via api WinSock do Windows

//Função que imprime uma mensagem de erro.
void erro(char *e)
{
   	printf("Erro - %s", e);
   	system("pause");
   	exit(-1);
}

int main(int argc, char **argv)
{

	WSAStartup(MAKEWORD(2, 0), &sock_opt); //Setando a versão do WinSock para 2.0

   	printf("Insira o IP do servidor: \n");
   	scanf("%s", ip_remoto); //Lendo o ip do computador remoto (usuário local informa o dado)
   	fflush(stdin);

   	printf("Insira a Porta do servidor: \n");
   	scanf("%d", &porta_remota); //Lendo a porta do computador remoto (usuário local informa o dado)
   	fflush(stdin);

   	socket_remoto = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Criando o socket remoto

   	memset(&end_remoto, 0, sizeof(end_remoto)); //Inicializando o endereço do remoto
   	end_remoto.sin_family = AF_INET; //Setando o protocolo IP
   	end_remoto.sin_addr.s_addr = inet_addr(ip_remoto); //Estabelecendo o endereço IP remoto
   	end_remoto.sin_port = htons(porta_remota); //Estabelecendo a porta do endereço remoto

	connect(socket_remoto, (struct sockaddr *) &end_remoto, sizeof(end_remoto)); //Conectando-se ao socket remoto
	printf("Conectado ao endereço remoto - %s:%d.\n", ip_remoto, porta_remota); 

   	printf("Digite seu texto e depois tecle ENTER para enviar.\n");
   	do
   	{
	   	memset(&msg, 0, TAM_BUFFER); //Zerando o buffer

	   	printf("Texto: "); //Informando ao usuário o que deve ser feito
	   	gets(msg); //Lendo os caracteres informado pelo teclado [128]
	   	fflush(stdin); //Limpando o buffer do teclado

	   	tam_msg = strlen(msg); //Contabilizando o número de caracteres digitados pelo usuário

		send(socket_remoto, msg, tam_msg, 0); //enviando a mensagem ao socket remoto

   	}
   	while(strcmp(msg, "/exit")); //Encerra ao enviar o comando "/exit"

   	WSACleanup(); //Limpando as informações de opção de sockets pelo Windows
   	closesocket(socket_remoto); //Finaliza o socket remoto
	printf("O chat foi finalizado.\n");
	
   	system("PAUSE");
  	return 0;
}
