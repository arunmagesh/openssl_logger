# OpenSSL SSL/TLS Communication Logger

This program captures and logs SSL/TLS communication between a client and server using LD_PRELOAD with OpenSSL. It saves the SSL/TLS data to a log file for analysis.

## Prerequisites

Before you begin, ensure you have the following prerequisites installed on your system:

- [OpenSSL](https://www.openssl.org/): Ensure that OpenSSL is installed on your system by using `sudo apt install openssl-dev`.  You can check if it's available by running `openssl version` in your terminal.
- You can use it to compile for other architecture but you need openssl-dev compiled for that arcitecture and it is easier to use a qemu instance of other architecture to build the binary. 

## How to Use

1. Clone this repository to your local machine:

```
git clone https://github.com/arunmagesh/openssl_logger
```
   
2. Change to the project directory:

```
cd openssl_logger
```
3. Compile the program using the provided Makefile:


```
make
```
4. Set the LD_PRELOAD environment variable to load the shared library before running your target application:

```

LD_PRELOAD=./libssl_log.so ./your_application
or
export LD_PRELOAD=`pwd`/libssl_log.so
```
Replace ./your_application with the actual command used to run your application that uses SSL/TLS or export to collect all the connection.

The SSL/TLS communication between your application and the server will be captured and logged to a file named ssl_traffic.log in the current directory.

## Testing with Google.com

To test the program with a real HTTPS endpoint like Google.com:

Open your terminal.

Use the following command to establish an SSL/TLS connection to Google.com and log the communication:

bash
```
LD_PRELOAD=./libssl_log.so openssl s_client -connect www.google.com:443
```

This command connects to Google's HTTPS endpoint (www.google.com:443) and logs the SSL/TLS communication to the ssl_traffic.log file.

Interact with the Google.com endpoint as needed by sending HTTP requests or other data. The communication will be logged to the file.
```
GET / HTTP/1.1
Host: www.google.com
```


## Analyzing the Log

Simply open the ssl_traffic.log file.

## Cleanup

To clean up generated files:

```
make clean
```
## License

This project is licensed under the MIT License.
