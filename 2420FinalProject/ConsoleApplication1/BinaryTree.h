#include <iostream>

#pragma once
using namespace std;

class BinaryTree {

public:
    enum ChallengeType {
    Strength=1,
    Agility=2,
    Intelligence=3
    };

      struct Node {
          int data;
          string challenge;
          ChallengeType challengeType;
          int difficulty;
          Node* left;
          Node* right;

          Node(int data, string challenge,  ChallengeType challengeType, int difficulty) {
              this->data = data;
              this->challenge = challenge;
              this->challengeType = challengeType;
              this->difficulty = difficulty;
              left = right = nullptr;
          }
      };

      Node* root;  // Declare a root node member variable

      BinaryTree() {
          root = nullptr;
      }

      void insert(string challenge, int data, int challengeType, int difficulty) {
          ChallengeType insertion_data = static_cast<ChallengeType>(challengeType);
          insertHelper(root, data, challenge, insertion_data, difficulty);
          root = rebalance(root);
      }

      void inorderTraversal(Node* root) {
          if (root == nullptr) {
              return;
          }

          inorderTraversal(root->left);
          cout << root->data << " ";
          inorderTraversal(root->right);
      }

      void preorderTraversal(Node* root) {
          if (root == nullptr) {
              return;
          }

          cout << root->data << " ";
          preorderTraversal(root->left);
          preorderTraversal(root->right);
      }

      void postorderTraversal(Node* root) {
          if (root == nullptr) {
              return;
          }

          postorderTraversal(root->left);
          postorderTraversal(root->right);
          cout << root->data << " ";
      }

      int FindNearestChallenge(int target) {
          Node* temp_node = FindClosestPTR(root, target);
          return temp_node->data;
      }


      string getChallengeType(int data) {
          Node* node = findNode(root, data);
          if (node) {
              return challengeTypeToString(node->challengeType);
          }
          else {
              throw runtime_error("Node with the specified data not found.");
          }
      }

      int getChallengeStat(int data) {
          Node* node = findNode(root, data);
          if (node) {
              return node->difficulty;
          }
          else {
              throw runtime_error("Node with the specified data not found.");
          }
      }

      string getChallengeName(int data) {
          Node* node = findNode(root, data);
          if (node) {
              return node->challenge;
          }
          else {
              throw runtime_error("Node with the specified data not found.");
          }
      }


      Node* findNode(Node* node, int data) {
          if (!node) {
              return nullptr;
          }
          if (node->data == data) {
              return node;
          }
          else if (data < node->data) {
              return findNode(node->left, data);
          }
          else {
              return findNode(node->right, data);
          }
      }

      string challengeTypeToString(ChallengeType type) {
          switch (type) {
          case Strength: return "Strength";
          case Agility: return "Agility";
          case Intelligence: return "Intelligence";
          default: return "Unknown";
          }
      }



      Node* FindClosestPTR(Node* root, int target) {
          if (root == nullptr) {
              return nullptr;
          }

          if (root->data == target) {
              return root;
          }

          if (target < root->data) {
              if (root->left == nullptr) {
                  return root;
              }
              Node* leftClosest = FindClosestPTR(root->left, target);
              if (abs(leftClosest->data - target) < abs(root->data - target)) {
                  return leftClosest;
              }
              else {
                  return root;
              }
          }
          else {
              if (root->right == nullptr) {
                  return root;
              }
              Node* rightClosest = FindClosestPTR(root->right, target);
              if (abs(rightClosest->data - target) < abs(root->data - target)) {
                  return rightClosest;
              }
              else {
                  return root;
              }
          }

      }

      Node* minValueNode(Node* node) {
          Node* current = node;
          while (current->left != nullptr) {
              current = current->left;
          }
          return current;
      }

      void NodeDeletion(int key) {
          deleteNode(root, key);
      }

      Node* deleteNode(Node* root, int key) {
          if (root == nullptr) {
              return root;
          }

          if (key < root->data) {
              root->left = deleteNode(root->left, key);
          }
          else if (key > root->data) {
              root->right = deleteNode(root->right, key);
          }
          else {
              // node with one or no child
              if (root->left == nullptr) {
                  Node* temp = root->right;
                  delete root;
                  return temp;
              }
              else if (root->right == nullptr) {
                  Node* temp = root->left;
                  delete
                      root;
                  return temp;
              }

              // node with two children : Get the inorder successor(smallest
              // in the right subtree)
              Node* temp = minValueNode(root->right);

              // Copy the inorder successor's content to this node
              root->data = temp->data;

              root->challenge = temp->challenge;
              root->challengeType = temp->challengeType;
              root->difficulty = temp->difficulty;

              // Delete the inorder successor
              root->right = deleteNode(root->right, temp->data);
          }
          root = rebalance(root);
          return root;
      }

      int height(Node* N) {
          if (N == NULL)
              return 0;
          return 1 + max(height(N->left), height(N->right));
      }

      int getBalance(Node* N) {
          if (N == NULL)
              return 0;
          return height(N->left) - height(N->right);
      }

      Node* rightRotate(Node* y) {
          Node* x = y->left;
          Node* T2 = x->right;

          x->right = y;
          y->left = T2;

          return x;
      }

      Node* leftRotate(Node* x) {
          Node* y = x->right;
          Node* T2 = y->left;

          y->left = x;
          x->right = T2;

          return y;
      }

      Node* rebalance(Node* root) {
          int balance = getBalance(root);

          // Left-Left Case
          if (balance > 1 && getBalance(root->left) >= 0)
              return rightRotate(root);

          // Left-Right Case
          if (balance > 1 && getBalance(root->left) < 0) {
              root->left = leftRotate(root->left);
              return rightRotate(root);
          }

          // Right-Right Case
          if (balance < -1 && getBalance(root->right) <= 0)
              return leftRotate(root);

          // Right-Left Case
          if (balance < -1 && getBalance(root->right) > 0) {
              root->right = rightRotate(root->right);
              return leftRotate(root);
          }

          return root;
      }
private:
    void insertHelper(Node*& node, int data, string challenge, ChallengeType challengeType, int difficulty) {
        if (node == nullptr) {
            node = new Node(data, challenge, challengeType, difficulty);
            return;
        }

        if (data < node->data) {
            insertHelper(node->left, data, challenge, challengeType, difficulty);
        }
        else {
            insertHelper(node->right, data, challenge, challengeType, difficulty);
        }
    }
};