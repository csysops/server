#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "utils.h"

#define PORT 8080
#define WWW_ROOT "./www"


int main() {
    int server_fd;
    struct sockaddr_in addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 10);

    printf("Serving static files on http://localhost:%d\n", PORT);

    // -------- SERVER LOOP --------
    while (1) {
        int client_fd;
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        char buffer[BUFFER_SIZE];

        client_fd = accept(server_fd,
                           (struct sockaddr *)&client_addr,
                           &client_len);

        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        int n = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (n <= 0) {
            close(client_fd);
            continue;
        }

        buffer[n] = '\0';

        char method[8];
        char path[256];
        sscanf(buffer, "%7s %255s", method, path);

        if (strcmp(method, "GET") != 0) {
            send_404(client_fd);
            close(client_fd);
            continue;
        }

        char filepath[512];

        if (strcmp(path, "/") == 0) {
            snprintf(filepath, sizeof(filepath),
                     "%s/index.html", WWW_ROOT);
        } else if (strcmp(path, "/home") == 0) {
            snprintf(filepath, sizeof(filepath),
                     "%s/home.html", WWW_ROOT);
        } else {
            snprintf(filepath, sizeof(filepath),
                     "%s%s", WWW_ROOT, path);
        }

        serve_file(client_fd, filepath);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}

