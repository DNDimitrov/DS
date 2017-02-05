#pragma once
#include <ostream>
#include <iostream>

class RLEString {
    public:
        struct Node {
            char symbol;
            int occurencies;
            Node* next;

            Node(char symbol, int occurencies) {
                this->symbol = symbol;
                this->occurencies = occurencies;
                this->next = NULL;
            }

            Node(Node const & other) {
                this->symbol = other.symbol;
                this->occurencies = other.occurencies;
            }

            void operator=(Node const & other) {
                if (this != &other) {
                    this->symbol = other.symbol;
                    this->occurencies = other.occurencies;
                }
            }

            ~Node() {
                delete this->next;
            }

            bool equals(const Node* other) {
                return this->symbol == other->symbol &&
                    this->occurencies == other->occurencies;
            }
        };

    private:
        Node* start;

    public:
        RLEString() {
            this->start = NULL;
        }

        RLEString(const char* str) {
            this->initNodes(str);
        }

        RLEString(RLEString const & other) {
            this->copyChain(other);
        }

        ~RLEString() {
            this->clear();
        }

        RLEString operator= (RLEString const & other) {
            if (this != &other) {
                this->clear();
                this->copyChain(other);
            }

            return *this;
        }

        Node* getStart() const {
            return this->start;
        }

    private:
        void initNodes(const char* str) {
            int index = 0;
            this->start = createNode(str, index);
            Node* current = start;

            while (str[index] != '\0') {
                current->next = this->createNode(str, index);
                current = current->next;
            }
        }

        Node* createNode(const char* str, int& index) {
            int count = 1;

            while (str[index] != '\0' && str[index] == str[index + 1]) {
                count += 1;
                index += 1;
            }

            index += 1;
            return new Node(str[index - 1], count);
        }

        void clear() {
            delete this->start;
        }

        void copyChain(RLEString const & other) {
            Node* otherCurrent = other.getStart();
            if (otherCurrent == NULL) {
                this->start = NULL;
                return;
            }

            Node* current = new Node(*otherCurrent);
            this->start = current;
            otherCurrent = otherCurrent->next;

            while (otherCurrent != NULL) {
                current->next = new Node(*otherCurrent);
                current = current->next;

                otherCurrent = otherCurrent->next;
            }

        }

        friend std::ostream& operator<< (std::ostream& os, const RLEString& string) {
            auto current = string.start;

            while (current != NULL) {
                for (int i = 0; i < current->occurencies; i += 1) {
                    os << current->symbol;
                }
                
                current = current->next;
            }

            return os;

        }
};
