#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
#include "minigit.hpp"
#include <filesystem>
Minigit::Minigit()
{
    repohead = NULL;
}
Minigit::~Minigit()
{
    doublyNode *doublecurr;
    doublyNode *doubleprev; //This goes the dowuble links
    singlyNode *singlecurr; //This goes to the single link list
    singlyNode *singleprev;
    doublecurr = repohead;
    doubleprev = NULL;
    while (doublecurr != NULL)
    {
        singlecurr = doublecurr->head;
        singleprev = NULL;
        while (singlecurr != NULL)
        {
            singleprev = singlecurr;
            singlecurr = singlecurr->next;
            delete singleprev;
        }
        doubleprev = doublecurr;
        doublecurr = doublecurr->next;
        delete doubleprev;
    }
    std::filesystem::remove_all(".minigit");
}
void Minigit::Initialize()
{
    doublyNode *newnode1 = new doublyNode;
    newnode1->commitNumber = 00;
    newnode1->head = NULL;
    newnode1->next = NULL;
    newnode1->previous = NULL;
    repohead = newnode1;
    currNode = repohead;
}

void Minigit::addFile(string FN) //This will insert a file into the link list
{
    singlyNode *temp1 = currNode->head;
    while (temp1 != NULL)
    {
        if (temp1->fileName == FN)
        {
            cout << "This files already exist. Please enter new file." << endl;
            cin >> FN;
            temp1 = currNode->head;
        }
        else
        {
            temp1 = temp1->next;
        }
    }
    singlyNode *Files = new singlyNode;
    Files->fileName = FN;
    Files->fileVersion = FN + '_' + to_string(currNode->commitNumber);
    Files->next = NULL;
    if (currNode->head == NULL)
    {
        currNode->head = Files;
        return;
    }
    singlyNode *temp = currNode->head;
    while (temp->next != NULL)
    {

        temp = temp->next;
    }
    temp->next = Files;

    return;
    //end here for debug
}
void Minigit::printrepo()
{

    doublyNode *temp = repohead;
    while (temp != NULL)
    {

        cout << "Version: " << temp->commitNumber << endl;
        singlyNode *temp1 = temp->head;
        while (temp1 != NULL)
        {

            cout << " " << temp1->fileVersion;
            temp1 = temp1->next;
        }
        cout << endl;
        temp = temp->next;
    }
}
void Minigit::Commit(string FV, string FN)
{
    if (currNode->head == NULL)
    {

        cout << "Nothing" << endl;
        return;
    }
    singlyNode *temp = currNode->head;
    while (temp != NULL)
    {

        if (std::filesystem::exists(".minigit/" + temp->fileVersion))
        {
            ifstream userFile;
            ifstream repoFile;
            userFile.open(temp->fileName);
            repoFile.open(".minigit/" + temp->fileVersion);
            string r;
            string repo;
            string local;
            while (repoFile >> r)
                repo += r;
            while (userFile >> r)

                local += r;
            if (repo.compare(local) != 0)
            {
                int version = currNode->commitNumber;
                ofstream file2(".minigit/" + temp->fileName + "_" + to_string(version));
                file2 << local;
                file2.close();
                temp->fileVersion = temp->fileName + "_" + to_string(version);
            }
            else
            {
                cout << "File does not change." << endl;
            }
        }
        else
        { //if the files does not exist we add it
            cout << "Print" << endl;
            ifstream file;
            file.open(temp->fileName);
            string r;
            string data;
            while (file >> r)
                data += r;
            ofstream file2(".minigit/" + temp->fileVersion);
            file2 << data;
            file2.close();
        }
        temp = temp->next;
    }
    doublyNode *temp1 = new doublyNode;
    temp1->commitNumber = currNode->commitNumber + 1;
    temp1->previous = currNode;
    currNode->next = temp1;
    temp1->next = NULL;
    singlyNode *temp2 = currNode->head;
    singlyNode *prev1 = NULL;
    while (temp2 != NULL)
    {
        singlyNode *newnode = new singlyNode;
        newnode->fileName = temp2->fileName;
        newnode->fileVersion = temp2->fileVersion;
        newnode->next = NULL;
        if (prev1 == NULL)
        {
            temp1->head = newnode;
        }
        else
        {

            prev1->next = newnode;
        }
        prev1 = newnode;
        temp2 = temp2->next;
    }
    currNode = temp1;
    return;
}
void Minigit::removeFile(string FN) //This function should delete a node in the single lik list
{

    singlyNode *SLLFile = currNode->head; //SLLFile to access the head of the Single Link list
    singlyNode *prev;                     //Prev to keep track of the previous node
    if (currNode->head == NULL)           //Check if the head is null
    {
        cout << "List is already empty, can't delete" << endl; //Error message
        return;                                                //Return the break the program
    }
    else if (SLLFile->fileName == FN) //Check if the head is the first thing that needs to be deleted
    {
        singlyNode *temp = currNode->head;
        currNode->head = currNode->head->next; //Set the double link list pointer to point to SLL next node
        delete temp;                           //Delete SLL
        return;                                //Retun to break the file
    }
    else
    {
        while (SLLFile != NULL) //While loop to go through the link list
        {
            if (SLLFile->fileName == FN) //Check if the file name that the program is looking for is in the link list
            {
                prev->next = SLLFile->next; //Setting prev pointer to point to SLL next ndoe
                delete SLLFile;             //delete SLL
                return;                     //Return to break the program
            }
            prev = SLLFile;
            SLLFile = SLLFile->next;
        }
    }
    cout << "This file does not exist" << endl;
}
void Minigit::checkout(int CM)
{

    singlyNode *SLL;
    doublyNode *DLL = repohead;
    fstream SLLFile;
    fstream VCPF;
    string VC;
    string SLLF;
    string VC1;
    string SLLF1;
    SLL = DLL->head;
    //DLL -> commitNumber +=1;
    cout << DLL->commitNumber << endl;
    if (repohead == NULL)
    {
        cout << "List is empty can't checkout" << endl;
        return;
    }
    while (DLL != NULL)
    {

        if (DLL->commitNumber == CM)
        {
            break;
        }
        else
        {

            DLL = DLL->next;
        }
    }
    if (DLL == NULL)
    {

        cout << "Commit Number does not exist" << endl;
        return;
    }
    singlyNode *temp = currNode->head;
    while (temp != NULL)
    {
        cout << temp->fileName << endl;
        std::filesystem::remove(temp->fileName);
        temp = temp->next;
    }
    temp = DLL->head;
    while (temp != NULL)
    {
        ifstream repoFile;
        repoFile.open(".minigit/" + temp->fileVersion);
        string r;
        string repo;
        while (repoFile >> r)
            repo += r;
        ofstream file2(temp->fileName);
         file2 << repo;
        file2.close();
        temp = temp->next;
    }
}