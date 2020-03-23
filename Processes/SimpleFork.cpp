#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>

using namespace std;

template<typename Cont>
void print(const Cont &container) {
    for (auto &v: container)
        cout << v << ' ';
    cout << endl;
}

int main() {
    cout << "Parrent pid == " << getpid() << endl;
    vector<int> vals = {0, 1, 2, 3, 4, 5};
    pid_t child_pid = fork();
    pid_t my_pid = getpid();
    if (child_pid == 0) {
        // попали в дочерний процесс
        cout << "( in if(child_pid == 0) fork res == " << child_pid << endl;
        for (auto &v: vals)
            v *= 10 + 1;
        cout << "VALS IN CHILD:" << endl;
        print(vals);
        return 100;
    }
    cout << "else fork returned res == " << child_pid << endl;
    int stat; // в стат записывается маска, о состоянии завершеннго процесса
    // был ли он завершен по сигналу, что он вернул в return итд
    pid_t wait_result = wait(&stat); // если все хорошо в результат возвращается pid дочернего процесса
    cout << "wait_result == " << wait_result << " stat == " << stat << endl;
    cout << "VALS IN PARENT PROCESS:" << endl;
    print(vals);
    cout << "child returned == " << WEXITSTATUS(stat) << endl;
    return 0;
}
