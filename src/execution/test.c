//
// #include "../include/minishell.h"
//
// #define MAX_CMDS 5
// char *cmds[MAX_CMDS][5] = {
//     {"cat", NULL},
//     {"grep", "DIR", NULL},
//     {"wc", "-l", NULL},
// };
// int main(void) {
//     int pipe_fd[2][2];
//     int num_cmds = 3;
//     int i;
//     int infile_fd = open("infile", O_RDONLY);
//     if (infile_fd == -1) {
//         perror("open infile");
//         exit(EXIT_FAILURE);
//     }
//     int outfile_fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (outfile_fd == -1) {
//         perror("open outfile");
//         exit(EXIT_FAILURE);
//     }
//     for (i = 0; i < num_cmds; i++) {
//         int current = i % 2;
//         int previous = (i + 1) % 2;
//         // Create pipe if not last command
//         if (i != num_cmds - 1) {
//             if (pipe(pipe_fd[current]) == -1) {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         pid_t pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//         if (pid == 0) {
//             // CHILD
//             // Redirect stdin
//             if (i == 0) {
//                 dup2(infile_fd, STDIN_FILENO);
//                 close(infile_fd);
//             } else {
//                 dup2(pipe_fd[previous][0], STDIN_FILENO);
//             }
//             // Redirect stdout
//             if (i == num_cmds - 1) {
//                 dup2(outfile_fd, STDOUT_FILENO);
//                 close(outfile_fd);
//             } else {
//                 dup2(pipe_fd[current][1], STDOUT_FILENO);
//             }
//             // Close all pipe ends in child
//             if (i != 0) {
//                 close(pipe_fd[previous][0]);
//                 close(pipe_fd[previous][1]);
//             }
//             if (i != num_cmds - 1) {
//                 close(pipe_fd[current][0]);
//                 close(pipe_fd[current][1]);
//             }
//             // Execute command
//             execvp(cmds[i][0], cmds[i]);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         }
//         // PARENT
//         // Close previous pipe after it's no longer needed
//         if (i != 0) {
//             close(pipe_fd[previous][0]);
//             close(pipe_fd[previous][1]);
//         }
//     }
//     // Close redirection FDs in parent
//     close(infile_fd);
//     close(outfile_fd);
//     // Wait for all children
//     for (i = 0; i < num_cmds; i++) {
//         wait(NULL);
//     }
//     return 0;
// }
