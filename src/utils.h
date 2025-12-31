#ifndef UTILS_H
#define UTILS_H

#define BUFFER_SIZE 4096

void send_404(int client_fd) {
    const char *body = "404 Not Found";
    char response[256];

    snprintf(response, sizeof(response),
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        strlen(body), body
    );

    write(client_fd, response, strlen(response));
}

void serve_file(int client_fd, const char *filepath) {
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        send_404(client_fd);
        return;
    }

    struct stat st;
    fstat(fd, &st);

    char header[256];
    snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n",
        st.st_size
    );

    write(client_fd, header, strlen(header));

    char buffer[BUFFER_SIZE];
    ssize_t bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
        write(client_fd, buffer, bytes);
    }

    close(fd);
}

#endif // UTILS_H