#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

class Server {
public:
  Server(string filename) {
    this->filename = filename;
    this->files_queue = queue<string>();
    this->threads = vector<thread>();
    this->logger = Logger("server");
  }

  void Start() {
    files_queue.push(filename);
    for (int i = 0; i < thread::hardware_concurrency(); i++) {
      threads.push_back(thread(&Server::StreamFile, this));
    }
    for (auto& thread : threads) {
      thread.join();
    }
  }

private:
  void StreamFile() {
    while (true) {
      string filename = files_queue.front();
      files_queue.pop();
      ifstream file(filename);
      if (!file.is_open()) {
        logger.error("Error opening file " + filename);
        return;
      }
      int chunk_size = 1024;
      char buffer[chunk_size];
      int bytes_read = 0;
      long long total_bytes_read = 0;
      while (!file.eof()) {
        file.read(buffer, chunk_size);
        bytes_read = file.gcount();
        if (bytes_read == 0) {
          break;
        }
        total_bytes_read += bytes_read;
        logger.info("Sending chunk of size " + to_string(bytes_read));
        send(buffer, bytes_read);
      }
      logger.info("File " + filename + " streamed successfully");
      logger.info("Total bytes read: " + to_string(total_bytes_read));
    }
  }

  string filename;
  queue<string> files_queue;
  vector<thread> threads;
  Logger logger;
};

int main() {
  Server server("test.txt");
  server.Start();
  return 0;
}