#include "MIT.h"

int main(int argc, char **argv) {

#if 0
    MITPerson *person = new MITPerson(901289, "John Doe", "500 Massachusetts Ave.");
    Student *student = new Student(971232, "James Lee", "32 Vassar St.", 6, 2);
    MITClass *c1 = new MITClass("6.088");
    student->addClassTaken(c1);

    person->displayProfile();
    student->displayProfile();
#endif
#if 0
    MITPerson *person = new MITPerson(901289, "John Doe", "500 Massachusetts Ave.");
    MITPerson *student = new Student(971232, "James Lee", "32 Vassar St.", 6, 2);

    person->displayProfile();
    student->displayProfile();
#endif
#if 1
    MITPerson *student = new Student(971232, "James Lee", "32 Vassar St.", 6, 2);
    MITClass *c1 = new MITClass("6.088");
    // use "dynamic_cast<...>" to downcast the pointer
    Student *student2 = dynamic_cast<Student *>(student);
    student2->addClassTaken(c1);
#endif

    return 0;
}

