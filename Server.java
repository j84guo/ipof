import java.io.*;
import java.net.*;

public class Server {
  int port;

  public Server(int port) {
    this.port = port;
  }

  public void run() throws IOException {
    try (ServerSocket server = new ServerSocket(8000)) {
      while (true) {
        try (Socket client = server.accept()) {
          System.out.println(client);
        }
      }
    }
  }

  public static void main(String[] args) throws IOException {
    new Server(8000).run();    
  }
}
