Part 1:

To compile first part of the program(server) you should write the following in terminal:
	gcc -o server server.c

Then you need to run the executable file in terminal:
	./server
	
Now the webserver is listening to port 8081. To access this webserver you need to go to your browser and type:
 	localhost:8081	
 	
This will display the quokka image and text on the website due to the "Index.html" file that is located in the same folder as the server.c file.

Summary of how the code works:
1. Socket is created and server is waiting for a request
2. Request is made and it checks if there is a file with the same name as the request.
3. If the port number written after "localhost:" is correct, our program will open Index.html
4. If the file is not found it print a error message

-----------------------------------------------------------------------------------------------------------

Part 2:

To compile the second part you should open up two seperate terminals: 

terminal 1:
You should compile the timerserver first, writing the following in terminal:
	gcc -o timeserver timeserver.c
	
Then you will execute the executable file that was created, by writing the following in the terminal:
	sudo ./timeserver

terminal 2:
You should compile the timeclient first, writing the following in terminal:
	gcc -o timeclient timeclient.c
Then you will execute the executable file that was created, by writing the following in the terminal, here you also need to pass the IP adress 127.0.0.1:
	./timeclient 127.0.0.1
