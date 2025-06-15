/*
	SERVER SIDE
	
	* Project -> Project Options -> Parameters -> Add library or Object -> 
	"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32/libws2_32.a"
	
	* Tools -> Compiler Options -> Add the following commands when calling the linker ->
	"-lws2_32"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
    
#define FILA_CONN 5 //Número máximo de conexões remotas a serem estabelecidas (fila com 5 posições)
#define TAM_BUFFER 128 //Tamanho da mensagem

int socket_local = 0; //handler para o socket local
int socket_remoto = 0; //hander para o socket remoto
int tam_remoto = 0; //Tamanho 
int tam_msg = 0; //tamanho da mensagem 
int porta_local = 0; //porta do socket local
int porta_remota = 0; //porta do socket remoto
char msg[TAM_BUFFER]; //buffer que receberá a mensagem
struct sockaddr_in end_local; //struct para montar o end. local
struct sockaddr_in end_remoto; //struct para montar o end. remoto

WSADATA sock_opt; //dados para setar opções via api WinSock do Windows

int main(int argc, char **argv)
{
   WSAStartup(MAKEWORD(2, 0), &sock_opt); //Setando a versão do WinSock para 2.0

   socket_local = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Criando socket local (listener)

   printf("Insira a Porta local: "); 
   scanf("%d", &porta_local); //Usuário informa a porta local
   fflush(stdin);

   // zera a estrutura local_address
   memset(&end_local, 0, sizeof(end_local)); //Inicializando o endereço remoto
   end_local.sin_family = AF_INET; //Setando o protocolo IP
   end_local.sin_port = htons(porta_local); //Estabelecendo a porta local
   end_local.sin_addr.s_addr = htonl(INADDR_ANY); //Estabelecendo o end. IP local

   bind(socket_local, (struct sockaddr *) &end_local, sizeof(end_local)); //Vinculando endereço local ao socket local

   listen(socket_local, FILA_CONN); //Ouvindo às tentativas de conexão remotas

   tam_remoto = sizeof(end_remoto); //Tamanho, em bytes, da variável end_remoto

   printf("Esperando por algum cliente...\n");
   socket_remoto = accept(socket_local, (struct sockaddr *) &end_remoto, &tam_remoto); //Aceitando uma conexão remota

   printf("Conectado a %s\n", inet_ntoa(end_remoto.sin_addr));
   
   printf("Mensagens recebidas:\n");
   do
   {
       memset(&msg, 0, TAM_BUFFER); //zerando o buffer
       tam_msg = recv(socket_remoto, msg, TAM_BUFFER, 0); //recebendo uma mensagem
       printf("%s: %s\n", inet_ntoa(end_remoto.sin_addr), msg); //mostra a mensagem recebida
   }
   while(strcmp(msg, "/exit")); // sai quando receber um "#quit" do cliente

   printf("Chat encerrado.\n");
   WSACleanup(); //Limpando as informações de opção de sockets pelo Windows
   closesocket(socket_local); //Finaliza o socket local
   closesocket(socket_remoto); //Finaliza o socket remoto

   system("pause");
   return 0;
}
