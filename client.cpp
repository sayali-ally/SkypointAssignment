#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Client {
public:
  Client(string ip, int port) {
    this->ip = ip;
    this->port = port;
    this->logger = Logger("client");
  }

  void Start() {
    while (true) {
      cout << "Enter the filename to download: ";
      string filename;
      cin >> filename;
      connect(ip, port);
      download(filename);
    }
  }

private:
  void connect(string ip, int port) {
    ifstream socket("socket");
    if (!socket.is_open()) {
      logger.error("Error opening socket");
      return;
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    int connect_result = connect(socket, (struct sockaddr*)&address, sizeof(address));
    if (connect_result == -1) {
      logger.error("Error connecting to server");
      return;
    }
    logger.info("Connected to server");
  }

  void download(string filename) {
    int chunk_size = 1024;
    char buffer[chunk_size];
    while (true) {
      int bytes_received = recv(buffer, chunk_size, 0);
      if (bytes_received == 0) {
        break;
      }
      ofstream file(filename, ios::app);
      file.write(buffer, bytes_received);
      cout << "Received chunk of size " << bytes_received << endl;
    }
    cout << "File " << filename << " downloaded successfully" << endl;
  }

  string ip;
  int port;
};

int main() {
  Client client("127.0.0.1", 8080);
  client.Start();
  return 0;
}