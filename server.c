#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>

#define PORT 8081
#define BUF_SIZE 4096
#define S_SIZE 24
#define ZERO 0


int main(int argc, int* argv[]){
    // deklaration
      struct sockaddr_in clientaddr, serveraddr;
      char buf[BUF_SIZE], Failed_response[]= "HTTP/1.1 404 not found \r\n\r\n", Successful_response[]= "HTTP/1.1 200 OK r\n\r\n", *beginning, *end,string[S_SIZE]= "";
      int clientaddrlen, request_sd, sd, file_opener,listen_checker= ZERO, bind_checker=ZERO, bytes=0;
                 
      request_sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // PF_INET, SOCK_STREAM,IPPROTO_TCP are constants
      memset(&serveraddr, ZERO, sizeof(struct sockaddr_in)); 
      serveraddr.sin_family = AF_INET;
      serveraddr.sin_addr.s_addr = INADDR_ANY;
      serveraddr.sin_port = htons(PORT);      

      bind_checker=bind(request_sd,(struct sockaddr*)&serveraddr, sizeof(struct sockaddr_in));
      if(bind_checker < ZERO){
        perror("Bind failed!");
      }else{
      	printf("Socket binded successfully!");
      }
      
      listen_checker= listen(request_sd, SOMAXCONN);      
      if(listen_checker < ZERO) {
        perror("Listen failed!");
      }else{
      	printf("Socket listening!");
      }
      
      clientaddrlen = sizeof(struct sockaddr_in);
      
      do{
             sd = accept(request_sd, (struct sockaddr*)&clientaddr, &clientaddrlen);
             memset(buf, ZERO, BUF_SIZE);
             read(sd, buf, BUF_SIZE); // reads up to n characters, from socket sd and stores them in character array buf
             printf("%s\n", buf);
             beginning = strchr(buf, '/')+1; // searches for the first occurence of character '/'
             end = strchr(beginning, ' '); // searches for the first occurence of character ' '
             strncpy(string, beginning, end - beginning); 

             while(!(strcmp(string, "\0") >  1)){
                    strcpy(string, "Index.html");
             }
             file_opener = open(string, O_RDONLY);

             if(file_opener < ZERO) { 
                    printf("Could not open the file\n");
                    write(sd, Failed_response, strlen(Failed_response)); // writes up to size of Failed_response, from character array Failed response, to socket sd
             }
             else{
                    write(sd,Successful_response, strlen(Successful_response)); // writes up to size of Successful_response, from character array Successful_response, to socket sd
             }
             do{
                    bytes = read(file_opener, buf, BUF_SIZE);
                    if(bytes <= ZERO){
                    break;
                    }
                    write(sd, buf, bytes); // writes up to byte characters, from character array buf, to socket sd          
             }while(1);  
      }while(1);
      close(file_opener);
      close(sd);  
      close(request_sd);
}
