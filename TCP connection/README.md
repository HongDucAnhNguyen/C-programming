# Creating TCP connection with C

## Key components

### Client-side

1. define necessary information

- client_socket return value (less than 0 if socket creation failed)
- server_response buffer to hold response from server
- request_data, the message string in the req which client will send
- define struct of the server address
- create the socket
- clear buffers for defined variables

2. Establish communication

- Connect to server
- send request data to server
- receive back response
- close connection

### Server-side

1. define necessary information

- client_socket, server_socket return value
- server_response, the message string as a response which server will send back to client
- client_addr_len for the mem allocated for client request data
- request_data, message string which was sent to server by client
- define struct of the server and client address, s_addr = 0 to denote localhost for server, client address will be used for storing the return of accept()
- create the server_socket
- clear buffers for declared variables

2. Establish communication

- bind a socket to server address
- mark socket as a passive socket with listen(), set backlog
- accept() to start accepting connections from connecting client
- receive request data from client
- send back pre-defined response to client
- close connection
