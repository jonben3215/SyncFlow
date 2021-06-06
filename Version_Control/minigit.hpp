#include <iostream>
#include <string>
using namespace std;
struct singlyNode
{
    std::string fileName; // Name of the file that is being passed through 
    std::string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
};
struct doublyNode
{
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
};
class Minigit
{

    private:
        doublyNode * repohead;
        doublyNode*currNode;
    public:
        Minigit();
        ~Minigit();
        void Initialize();
        void printrepo();
        void addFile(std::string FileName);//Adding file to the link list (Singlylink list
        void Commit(std::string FileVersion, std::string FileName); // Searches in the single link list
        void removeFile(std::string FileName);//Removes  file from singlelist
        void checkout(int commitNum);//Check out the previous committ number 
};