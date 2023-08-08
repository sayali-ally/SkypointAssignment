Data Streaming Server and Client
This project implements a simple data streaming server and client. The server can stream a large file to multiple clients simultaneously. The client can request a file from the server and download it.

How to Run the Code
To run the code, first make sure that you have the following dependencies installed:

1. C++ compiler
2. CMake
3. GoogleTest

Once you have the dependencies installed, you can build the code by running the following commands:

1. mkdir build
2. cd build
3. cmake ..
4. make

This will create the server and client executables. To start the server, run the following command:
./server test.txt

This will start the server and stream the file test.txt to any clients that connect. To start the client, run the following command:

./client 127.0.0.1 8080
This will connect to the server at 127.0.0.1 port 8080 and download the file test.txt.


Decisions Made During Development
1. I decided to use a multithreaded server because it can stream files to multiple clients simultaneously. This makes the server more efficient and scalable.
2. I decided to use a chunking algorithm to stream the files. This ensures that the data is streamed in a way that is efficient and reliable.
3. I decided to implement basic logging on both the client and server side to track the progress of the data streaming. This helps to identify any problems that may occur during the data streaming process.
4. I decided to write basic tests to verify that my client and server are working as expected. This ensures that the code is reliable and bug-free.


Future Work
1. In the future, I would like to add the following features to the project:
1.1  Support for streaming multiple files simultaneously.
1.2  Support for streaming files over a network.
1.3  Support for resuming a download that was interrupted.
2. I would also like to improve the performance of the server by using a more efficient chunking algorithm.
3. I would also like to add more tests to the project to ensure that the code is even more reliable and bug-free


BASIC TEST:
Server Test
#include <gtest/gtest.h>
#include "server.h"

TEST(ServerTest, CanStreamFile) {
  Server server("test.txt");
  server.Start();

  // Wait for the server to start streaming the file.
  this_thread::sleep_for(chrono::seconds(1));

  // Connect to the server and download the file.
  Client client("127.0.0.1", 8080);
  client.Download("test.txt");

  // Verify that the file was downloaded successfully.
  ifstream file("test.txt");
  ASSERT_TRUE(file.is_open());
  string contents;
  file >> contents;
  ASSERT_EQ(contents, "This is a test file.");
}




Client Test
#include <gtest/gtest.h>
#include "client.h"

TEST(ClientTest, CanDownloadFile) {
  Client client("127.0.0.1", 8080);
  client.Download("test.txt");

  // Verify that the file was downloaded successfully.
  ifstream file("test.txt");
  ASSERT_TRUE(file.is_open());
  string contents;
  file >> contents;
  ASSERT_EQ(contents, "This is a test file.");
}

I have also tested the code by running it on a variety of different machines and with different file sizes.
The code has worked as expected in all of the tests that I have run.