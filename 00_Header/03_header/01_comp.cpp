// 1 create directory comp
// 2 create directory comp/test
// 3 create duipai.cpp
// add text

#include<bits/stdc++.h>
using namespace std;
int main(){
    int i;
  for (i=1;;i++){
        printf("The result of No. %d Case is:  ",i);
        system("python3 rand.py");
        system("./std < test/data.in > test/std.out");
        system("./my < test/data.in > test/my.out");
        if (system("diff test/std.out test/my.out")){
            printf("Wrong Answer\n");
            return 0;
        }
        else printf("Accepted\n");
    }
    return 0;
}


// 4 create duipai.sh
#!/bin/bash
g++ std.cpp -o std
g++ my.cpp -o my
python3 rand.py
./a.out

// 5 create rand.py
# coding=utf-8
from random import randint, choice, shuffle
# with open("../cmake-build-debug/data.in", "w") as f:
with open("test/data.in", "w") as f:
    n = randint(1, 10)
    m = randint(1, 10)
    f.write(f"{n} {m}")

// 6 terminal: g++ duipai.cpp
// 7 terminal: sudo chmod 777 duipai.sh
// 8 add my.cpp and std.cpp
// 9 ./duipai.sh

