#ifndef JOB_H
#define JOB_H

class PrintJob {
    int id;
    enum class STATUS { NONE, DONE, INPROGRESS, WAITING };
    STATUS status;
public:
    const std::string filename;
    PrintJob(const std::string &filename) : filename(filename) {}
};

#endif // JOB_H
