#include "PrintUtil.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Design a data structure that simulates an in-memory file system.

// Implement the FileSystem class:

// FileSystem() Initializes the object of the system.
// List<String> ls(String path)
// If path is a file path, returns a list that only contains this file's name.
// If path is a directory path, returns the list of file and directory names in this directory.
// The answer should in lexicographic order.
// void mkdir(String path) Makes a new directory according to the given path. The given directory path does not exist. If the middle directories in the path do not exist, you should create them as well.
// void addContentToFile(String filePath, String content)
// If filePath does not exist, creates that file containing given content.
// If filePath already exists, appends the given content to original content.
// String readContentFromFile(String filePath) Returns the content in the file at filePath.

class FileSystem {
public:
    FileSystem() {
        root = new FileNode(false);
    }
    
    vector<string> ls(string path) {
        vector<string> ans;
        vector<string> comps = splitPath(path);
        FileNode* curr = root;

        for (auto comp : comps) {
            if (curr->dir.find(comp) != curr->dir.end()) {
                curr = curr->dir[comp];
            } else {
                curr = nullptr;
                break;
            }
        }

        if (curr != nullptr && curr->isFile) {
            ans.push_back(comps.back());
        } else if (curr != nullptr && !curr->isFile) {
            for (auto&[k, v] : curr->dir) {
                ans.push_back(k);
                sort(ans.begin(), ans.end());
            }
        }

        return ans;
    }
    
    void mkdir(string path) {
        if (path.empty()) {
            return;
        }

        vector<string> comps = splitPath(path);
        FileNode* curr = root;
        for (auto comp : comps) {
            if (curr->dir.find(comp) == curr->dir.end()) {
                curr->dir.emplace(comp, new FileNode(false));
            }

            curr = curr->dir[comp];
        }
    }
    
    void addContentToFile(string filePath, string content) {
        if (filePath.empty()) {
            return;
        }

        vector<string> comps = splitPath(filePath);
        FileNode* curr = root;
        for (int i = 0; i < comps.size(); i++) {
            if (curr->dir.find(comps[i]) == curr->dir.end()) {
                curr->dir.emplace(comps[i], new FileNode(i == comps.size() - 1));
            }

            curr = curr->dir[comps[i]];
        }

        curr->isFile = true;
        curr->content.append(content);
    }
    
    string readContentFromFile(string filePath) {
        string content;
        if (filePath.empty()) {
            return content;
        }

        vector<string> comps = splitPath(filePath);
        FileNode* curr = root;
        for (auto comp : comps) {
            if (curr->dir.find(comp) == curr->dir.end()) {
                curr = nullptr;
                break;
            }

            curr = curr->dir[comp];
        }

        return curr->isFile ? curr->content : "";
    }
    
private:
    struct FileNode {
        string content;
        bool isFile;
        unordered_map<string, FileNode* > dir;
        FileNode(bool isFile) : isFile(isFile) {}
    };
    
    FileNode* root;

    vector<string> splitPath(string s) {
        stringstream ss(s);
        vector<string> comps;
        while (ss.good()) {
            string node;
            getline(ss, node, '/');
            if (!node.empty()) {
                // note that "/a/b/c" will cause ss library parse "" at the
                // beginning.
                comps.push_back(node);
            }
        }

        return comps;
    }
};

int main () {
    FileSystem fs;
    PrintUtil::printVectorOf(fs.ls("/"));
    fs.mkdir("/a/b/c");
    fs.addContentToFile("/a/b/c/d", "hello");
    PrintUtil::printVectorOf(fs.ls("/"));
    cout << fs.readContentFromFile("/a/b/c/d") << endl;
}