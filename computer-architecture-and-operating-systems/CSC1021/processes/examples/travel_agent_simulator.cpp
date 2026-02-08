/*
    Example taken from Steve Reilander.
    Program spawns 6 "travel agents" as child process from the main function.
    Children are created with the th fork() function.

    Each process has access to the seats on a flight and can book them.
    The program will protect the seats from other travel agents to avoid
    overbooking problems. This is accomplished using IPCs. The IPCs
    used in this example are pipes.
*/

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int NUMBER_OF_CHILDREN = 6;                       /* number of travel agents */
const int PARENT_CONTROL = (2 - NUMBER_OF_CHILDREN);    /* seats_left = 2 - number of children */
const int INITIAL_NUMBER_OF_SEATS = 100;                /* number of seats */
const int SIZE_OF_INT = sizeof(int);                    /* parameter to send int down a pipe */

void travel_agent(int *child_to_parent, int *parent_to_child, int id);

int main(int argc, char **argv) {
    // create 2 pipes to talk from children to parent and parent to children
    // create an int array of size 2, then declare a pipe with the pip() function
    // using the array as a parameter as so:
    int child_to_parent[2], parent_to_child[2];
    pipe(child_to_parent);
    pipe(parent_to_child);

    // array if 6 pidIDs. used for joining threads at the end of program
    pid_t shut_down[NUMBER_OF_CHILDREN];
    
    // number of seats left
    int seats_left = INITIAL_NUMBER_OF_SEATS;

    int pid;

    for (std::size_t i{}; i < NUMBER_OF_CHILDREN; ++i) {
        pid = fork();

        if (pid < 0) {
            std::cerr << "fork failed!\n";
            return 1;
        } else if (pid == 0) {
            std::cout << "CHILD " << i << " CREATED " << getpid() << '\n';
            // start a travel agent function
            travel_agent(child_to_parent, parent_to_child, i);
            break;
        } else {
            shut_down[i] = pid;
        }
    }

    if (pid > 0) {
        bool loop = 1;
        while (loop) {
            write(parent_to_child[1], &seats_left, SIZE_OF_INT);
            read(child_to_parent[0], &seats_left, SIZE_OF_INT);
            
            if (seats_left > 0) {
                std::cout << "the main just read seats_left: " << seats_left << '\n';
            }
            if (seats_left < PARENT_CONTROL) {
                loop = false;
                std::cout << "[parent process] - exit the loop, PID: " << getpid() << '\n';
            }

            for (std::size_t i{}; i < NUMBER_OF_CHILDREN; ++i) {
                std::cout << "Waiting for PID: " << shut_down[i] << " to finish\n";
                waitpid(shut_down[i], NULL, 0);
                std::cout << "PID: " << shut_down[i] << " has shut down\n";
            }
        }
    }

    std::cout << "Did we all Join? There will be 7 of us if we did. PID: " << getpid() << '\n';
    if (pid > 0) std::cout << "There are no ZOMBIES!\n";

    return 0;
}

void travel_agent(int *child_to_parent, int *parent_to_child, int id) {
    bool loop = true;

    while (loop) {
        int seats_left = 0;
        // wait for parent to write, then process seats left.
        read(parent_to_child[0], &seats_left, SIZE_OF_INT);

        // if there are seats left, write out how many and then 'book' a seat
        // declare thread number, and pid
        if (seats_left > 0) {
            std::cout << "[child process " << id << "] - there are " << seats_left << " seats, booking one! [PID: " << getpid() << "]\n";
            seats_left--;
            // if we book the last seat, stop looping
            loop = seats_left;
            // tell the parent how many seats are left and get off the CPU
            write(child_to_parent[1], &seats_left, SIZE_OF_INT);
            usleep(100);
        } else {
            loop = 0;
            seats_left--;
            write(child_to_parent[1], &seats_left, SIZE_OF_INT);
        }
    }
}

